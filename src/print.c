/**************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 19:07:54 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/16 15:31:58 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

extern t_ls_flags	g_ls_flags;

static void	ls_print_file_long(t_ls_file *file)
{
	if (file->rights[0] == 'c' || file->rights[0] == 'b')
		ft_printf("%.11s\t%3d\t%s\t%s\t%d,\t%d\t%s\t%s\n",
			file->rights, file->links, file->owner, file->group_owner,
			file->major, file->minor, file->last_modif_str, file->name);
	else
		ft_printf("%.11s\t%3d\t%s\t%s\t%8d\t%s\t%s\n",
			file->rights, file->links, file->owner, file->group_owner,
			file->size, file->last_modif_str, file->name);
}

void		ls_print_file(t_ls_file *file)
{
	ft_printf("%s\t", file->name);
}

void		print_file_list(t_list *lst)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		if (g_ls_flags & LS_FLAG_l)
			ls_print_file_long((t_ls_file*)(lst->content));
		else
			ls_print_file((t_ls_file*)(lst->content));
		free_file_struct((t_ls_file*)(lst->content));
		free(lst);
		lst = next;
	}
}
