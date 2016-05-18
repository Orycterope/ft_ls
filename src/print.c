/**************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 19:07:54 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/18 17:18:52 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

extern t_ls_flags	g_ls_flags;

static void	ls_print_file_long(t_ls_file *file, t_dirinfo *d)
{
	if (file->rights[0] == 'c' || file->rights[0] == 'b')
		ft_printf("%-11s %*d %-*s  %-*s   %*d, %*d %s %s\n",
			file->rights,
			d->links_max_length, file->links,
			d->owner_max_length, file->owner,
			d->group_max_length, file->group_owner,
			d->major_max_length, file->major,
			d->minor_max_length, file->minor,
			file->last_modif_str, file->name);
	else if (1)
		ft_printf("%-11s %*d %-*s  %-*s %*s%*d %s %s\n",
			file->rights,
			d->links_max_length, file->links,
			d->owner_max_length, file->owner,
			d->group_max_length, file->group_owner,
			(d->major_max_length + d->minor_max_length + 2)
				- (d->size_max_length - 1), " ",
			d->size_max_length, file->size,
			file->last_modif_str, file->name);
}

void		ls_print_file(t_ls_file *file)
{
	ft_printf("%s\t", file->name);
}

void		print_file_list(t_list *lst, t_dirinfo *d)
{
	t_list	*next;

	if (g_ls_flags & LS_FLAG_l)
		ft_printf("total %d\n", d->total_blocks);
	while (lst)
	{
		next = lst->next;
		if (g_ls_flags & LS_FLAG_l)
			ls_print_file_long((t_ls_file*)(lst->content), d);
		else
			ls_print_file((t_ls_file*)(lst->content));
		lst = next;
	}
}
