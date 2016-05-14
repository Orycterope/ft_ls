/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 17:07:33 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/14 18:25:02 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern t_ls_flags	g_ls_flags;

int					filter_chooser(t_ls_file *f)
{
	if (f->name[0] == '.' && !(g_ls_flags & LS_FLAG_a))
		return (1);
	return (0);
}
