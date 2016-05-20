/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 15:30:35 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/20 15:35:18 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <string.h>
#include <errno.h>

extern t_ls_flags	g_ls_flags;

t_ls_file			*get_file_struct(char *full_path, char *name)
{
	t_ls_file	*file_struct;
	struct stat	s;

	file_struct = (t_ls_file *)ft_memalloc(sizeof(t_ls_file));
	if (lstat(full_path, &s))
	{
		ft_printf_fd(2, "ft_ls: %s: %s\n", full_path, strerror(errno));
		errno = 0;
		return (NULL);
	}
	file_struct->path = full_path;
	file_struct->name = name;
	file_struct->last_modif = s.st_mtime;
	get_type(&s, file_struct);
	if (g_ls_flags & LS_FLAG_L_LOWER)
	{
		get_rights(&s, file_struct);
		get_owners(&s, file_struct);
		get_last_modif_str(&s, file_struct);
		file_struct->blocks = s.st_blocks;
		file_struct->links = s.st_nlink;
		file_struct->size = s.st_size;
	}
	return (file_struct);
}

void				free_file_struct(void *f, size_t s)
{
	t_ls_file	*file;

	file = (t_ls_file *)f;
	s += 1;
	free(file->name);
	free(file->path);
	free(file->owner);
	free(file->group_owner);
	free(file->last_modif_str);
	free(file);
}
