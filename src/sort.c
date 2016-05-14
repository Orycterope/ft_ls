/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 15:45:09 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/14 19:55:49 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

extern t_ls_flags			g_ls_flags;

static inline int			is_sort_alpha(void *a, void *b)
{
	return (ft_strcmp(((t_ls_file *)a)->name, ((t_ls_file *)b)->name));
}

static inline int			is_sort_date(void *a, void *b)
{
	if (((t_ls_file *)a)->last_modif != ((t_ls_file *)b)->last_modif)
		return (((t_ls_file *)b)->last_modif - ((t_ls_file *)a)->last_modif);
	else
		return (is_sort_alpha(a, b));
}

static inline int			is_sort_revert(void *a, void *b)
{
	if (g_ls_flags & LS_FLAG_t)
		return (is_sort_date(a, b));
	else
		return (is_sort_alpha(a, b));
}

static int					is_sort_param(void *a, void *b)
{
	t_ls_file	*x;
	t_ls_file	*y;

	x = (t_ls_file *)a;
	y = (t_ls_file *)b;
	if (x->rights[0] == 'd' ^ y->rights[0] == 'd')
		return ((x->rights[0] == 'd'));
	else if (g_ls_flags & LS_FLAG_r)
		return (is_sort_revert(a, b));
	else if (g_ls_flags & LS_FLAG_t)
		return (is_sort_date(a, b));
	else
		return (is_sort_alpha(a, b));
}

void						sort_file_lst(t_list *lst, int is_param_lst)
{
	if (is_param_lst)
		ft_lstsort(lst, is_sort_param);
	else if (g_ls_flags & LS_FLAG_r)
		ft_lstsort(lst, is_sort_revert);
	else if (g_ls_flags & LS_FLAG_t)
		ft_lstsort(lst, is_sort_date);
	else
		ft_lstsort(lst, is_sort_alpha);
}
