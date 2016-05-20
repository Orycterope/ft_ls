/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 19:07:54 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/20 15:53:18 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#define BIGGEST(X, Y) X = (X > Y) ? X : Y

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

static void	calc_display(t_list *files, t_dirinfo *d)
{
	int			file_number;

	d->columns = 1;
	if (g_termcolnum > 0)
		BIGGEST(d->columns, g_termcolnum / (d->name_max_length + 1));
	file_number = ft_lstlen(files);
	d->lines = file_number / d->columns + (file_number % d->columns != 0);
	d->columns = file_number / d->lines + (file_number % d->lines != 0);
}

void		ls_print_files(t_list *files, t_dirinfo *d)
{
	t_list		*i;
	int			current_line;
	int			n;

	calc_display(files, d);
	current_line = 0;
	while (++current_line <= d->lines)
	{
		i = files;
		n = 1;
		while (i)
		{
			if (n % d->lines == (current_line % d->lines))
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
	if (!(g_ls_flags & LS_FLAG_L_LOWER) && !(g_ls_flags & LS_FLAG_1))
		ls_print_files(lst, d);
	else
	{
		if (g_ls_flags & LS_FLAG_L_LOWER)
			ft_printf("total %d\n", d->total_blocks);
		while (lst)
		{
			if (g_ls_flags & LS_FLAG_L_LOWER)
				ls_print_file_long((t_ls_file*)(lst->content), d);
			else
				ft_printf("%s\n", ((t_ls_file*)(lst->content))->name);
			lst = lst->next;
		}
	}
}
