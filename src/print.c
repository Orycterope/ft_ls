/**************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 19:07:54 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/19 19:14:28 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
# define BIGGEST(X, Y) X = (X > Y) ? X : Y

extern t_ls_flags	g_ls_flags;
extern int			g_termcolnum;

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

void		ls_print_files(t_list *files, t_dirinfo *d)
{
	int			coltotal;
	int			linestotal;
	t_list		*i;
	int			current_line;
	int			file_total;
	int			n;

	coltotal = 1;
	if (g_termcolnum > 0)
		BIGGEST(coltotal, g_termcolnum / (d->name_max_length + 1));
	file_total = ft_lstlen(files);
	linestotal = file_total / coltotal + (file_total % coltotal != 0);
	coltotal = file_total / linestotal + (file_total % linestotal != 0);
	current_line = 0;
	while (++current_line <= linestotal)
	{
		i = files;
		n = 1;
		while (i)
		{
			if (n % linestotal == (current_line % linestotal))
				ft_printf("%-*s ", (int)d->name_max_length,
						((t_ls_file*)i->content)->name);
			i = i->next;
			n++;
		}
		ft_putchar('\n');
	}
}

void		print_file_list(t_list *lst, t_dirinfo *d)
{
	t_list	*next;

	if (!(g_ls_flags & LS_FLAG_l))
		ls_print_files(lst, d);
	else
	{
		ft_printf("total %d\n", d->total_blocks);
		while (lst)
		{
			next = lst->next; //not used anymore
			ls_print_file_long((t_ls_file*)(lst->content), d);
			lst = next;
		}
	}
}
