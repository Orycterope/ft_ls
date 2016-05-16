/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 14:45:29 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/16 16:47:01 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <errno.h>
#include <dirent.h>
#include <string.h>

extern t_ls_flags	g_ls_flags;

static int		should_filter_out(char *s)
{
	char	*dir_sep;

	dir_sep = s;
	while (*s)
		if (*s++ == '/')
			dir_sep = s;
	return (*dir_sep == '.');
}

static t_list	*create_file_lst_from_folder(char *dir_name)
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
		if ((g_ls_flags & LS_FLAG_a) || !should_filter_out(entry->d_name))
			ft_lstadd(&lst,
				ft_lstnew(get_file_struct(entry->d_name), sizeof(t_ls_file)));
	}
	return (lst);
}

void			parse_directory(char *dir_name, int print_name)
{
	t_list	*lst;

	lst = create_file_lst_from_folder(dir_name);
	if (lst == NULL)
		return ;
	sort_file_lst(lst, 0);
	if (print_name)
		ft_printf("\n%s:\n", dir_name);
	print_file_list(lst);
}
