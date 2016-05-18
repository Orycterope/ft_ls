/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 14:45:29 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/18 16:34:10 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <errno.h>
#include <dirent.h>
#include <string.h>
# define BIGGEST(X, Y) X = (X > Y) ? X : Y

extern t_ls_flags	g_ls_flags;

static void			get_dir_infos(t_dirinfo *d, t_list *lst)
{
	t_ls_file	*f;

	ft_memset(d, 0, sizeof(t_dirinfo));
	while (lst)
	{
		d->file_number++;
		f = ((t_ls_file*)lst->content);
		if (g_ls_flags & LS_FLAG_l)
		{
			d->total_blocks += f->blocks;
			BIGGEST(d->links_max_length, ft_numlength(f->links));
			BIGGEST(d->owner_max_length, ft_strlen(f->owner));
			BIGGEST(d->group_max_length, ft_strlen(f->group_owner));
			if (f->rights[0] == 'c' || f->rights[0] == 'b')
			{
				BIGGEST(d->major_max_length, ft_numlength(f->major));
				BIGGEST(d->minor_max_length, ft_numlength(f->minor));
			}
			else
				BIGGEST(d->size_max_length, ft_numlength(f->size));
		}
		else
			BIGGEST(d->name_max_length, ft_strlen(f->name));
		lst = lst->next;
	}
}

static t_list		*create_file_lst_from_folder(char *dir_name)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*lst;

	dir = opendir(dir_name);
	if (dir == NULL)
	{
		ft_printf("ft_ls : error while opening folder %s : %s\n", dir_name, strerror(errno));
		errno = 0;
		return NULL;
	}
	lst = NULL;
	while ((entry = readdir(dir)))
	{
		if (errno)
		{
			ft_printf("ft_ls : error while retriving from folder %s : %s\n", dir_name, strerror(errno));
			errno = 0;
			continue ;
		}
		if ((g_ls_flags & LS_FLAG_a) || entry->d_name[0] != '.')
			add_file_to_list(dir_name, entry->d_name, &lst);
	}
	closedir(dir);
	return (lst);
}

void				parse_directory(char *dir_name, int print_name)
{
	t_list		*lst;
	t_list		*i;
	t_dirinfo	d;

	lst = create_file_lst_from_folder(dir_name);
	if (lst == NULL)
		return ;
	sort_file_lst(lst, 0);
	get_dir_infos(&d, lst);
	if (print_name)
		ft_printf("\n%s:\n", dir_name);
	print_file_list(lst, &d);
	if (g_ls_flags & LS_FLAG_R)
	{
		i = lst;
		while (i)
		{
			if (((t_ls_file*)i->content)->rights[0] == 'd')
				parse_directory(((t_ls_file*)i->content)->path, 1);
			i = i->next;
		}
	}
	ft_lstdel(&lst, free_file_struct);
}

void				add_file_to_list(char *dir_name, char *file_name, t_list **lst)
{
	t_ls_file	*s;
	char		*intermidiate;
	char		*full_path;

	s = NULL;
	intermidiate = NULL;
	if (dir_name)
	{
		intermidiate = ft_strjoin(dir_name, "/");
		full_path = ft_strjoin(intermidiate, file_name);
		free(intermidiate);
	}
	else
		full_path = ft_strdup(file_name);
	if (full_path == NULL)
		return ;
	s = get_file_struct(full_path, ft_strdup(file_name));
	if (s == NULL)
		return ;
	ft_lstadd(lst, ft_lstnew_nocpy(s, sizeof(t_ls_file)));
}
