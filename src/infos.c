/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 22:44:22 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/12 00:14:16 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

static inline char	*get_name(const char *filename)
{
	char	*ptr;
	int		i;

	ptr = filename;
	i = 0;
	while (filename[i])
	{
		if (filename[i] == '/')
			ptr = filename + i + 1;
		i++;
	}
	return (ft_strdup(ptr));
}

static inline void	get_type(struct stat s, t_ls_file *f)
{
	if (s->st_mode & S_IFREG)
		f->rights[0] = '-';
	else if (s->st_mode & S_IFDIR)
		f->rights[0] = 'd';
	else if (s->st_mode & S_IFLNK)
		f->rights[0] = 'l';
	else if (s->st_mode & S_IFCHR)
		f->rights[0] = 'c';
	else if (s->st_mode & S_IFIFO)
		f->rights[0] = 'p';
	else if (s->st_mode & S_IFBLK)
		f->rights[0] = 'b';
	else if (s->st_mode & S_IFSOCK)
		f->rights[0] = 's';
}

static inline void	get_rights(struct stat s, t_ls_file *f)
{
	f->rights[1] = (s->rights & S_IRUSR) ? 'r' : '-';
	f->rights[2] = (s->rights & S_IWUSR) ? 'w' : '-';
	f->rights[3] = (s->rights & S_IXUSR) ? 'x' : '-';
	f->rights[4] = (s->rights & S_IRGRP) ? 'r' : '-';
	f->rights[5] = (s->rights & S_IWGRP) ? 'w' : '-';
	f->rights[6] = (s->rights & S_IXGRP) ? 'x' : '-';
	f->rights[7] = (s->rights & S_IROTH) ? 'r' : '-';
	f->rights[8] = (s->rights & S_IWOTH) ? 'w' : '-';
	f->rights[9] = (s->rights & S_IXOTH) ? 'x' : '-';
	if (s->mode && S_ISUID)
		f->rights[3] = (s->rights & S_IXUSR) ? 's' : 'S';
	if (s->mode && S_ISGID)
		f->rights[3] = (s->rights & S_IXGRP) ? 's' : 'S';
}

t_ls_file			*get_file_struct(char *filename, int l_flag)
{
	t_ls_file	*file_struct;
	struct stat	s;

	file_struct = (t_ls_file *)ft_memalloc(sizeof(t_ls_file));
	if (stat(filename, &s))
	{
		ft_printf("Error for file %s : %s\n", filename, strerror(errno));
		return (NULL);
	}
	file_struct->name = get_name(filename); //must duplicate string from last /
	if (l_flag)
	{
		get_type(s, file_struct);
		get_rights(s, file_struct);
		get_owners(s, file_struct);
		get_modif_str(s, file_struct);
		file_struct->size = s->st_size;
	}
	return (file_struct);
}

void				free_file_struct(t_ls_file *file)
{
	free(file->name);
	free(file->owner);
	free(file->group_owner);
	free(file->last_modif_str);
	free(file);
}
