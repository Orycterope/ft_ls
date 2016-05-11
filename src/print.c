/**************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 19:07:54 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/11 23:11:41 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_print_file_long(t_ls_file *file)
{
	ft_printf("%s\t%3d\t%s\t%s\t%8d\t%s\t%s\n",
			file->rights, file->links, file->owner, file->group_owner,
			file->size, file->last_modif_str, file->name);
	free_file_struct(file);
}

void	ls_print_file(t_ls_file *file)
{
	ft_printf("%s\t", file->name);
	free_file_struct(file);
}
