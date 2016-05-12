/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 20:00:02 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/12 21:30:47 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <errno.h>

t_ls_flags			g_ls_flags = 0;

static void	add_argument(t_ls_argument **lst, char *path)
{
	t_ls_argument	*new;

	new = (t_ls_argument *)ft_memalloc(sizeof(t_ls_argument));
	new->next = *lst;
	new->path = path;
	new->file_struct = get_file_struct(path, g_ls_flags & LS_FLAG_l);
	*lst = new;
}

static void	activate_flag(char flag)
{
	if (flag == 'l')
		g_ls_flags |= LS_FLAG_l;
	else if (flag == 'R')
		g_ls_flags |= LS_FLAG_R;
	else if (flag == 'a')
		g_ls_flags |= LS_FLAG_a;
	else if (flag == 'r')
		g_ls_flags |= LS_FLAG_r;
	else if (flag == 't')
		g_ls_flags |= LS_FLAG_t;
	else
	{
		ft_printf("ft_ls : illegal option -- %c\n"
				"usage: ls [-lRart] [file ...]\n", flag);
			exit(EINVAL);
	}
}

static void	read_flags(int *ac, char ***av)
{
	*ac -= 1;
	*av += 1;
	while (*ac > 0 && ***av == '-')
	{
		while (*(++**av))
			activate_flag(***av);
		*ac -= 1;
		*av += 1;
	}
}

int			main(int ac, char **av)
{
	t_ls_argument	*arguments;

	read_flags(&ac, &av);
	arguments = NULL;
	ft_printf("l flag: %d\n"
			"R flag: %d\n"
			"a flag: %d\n"
			"r flag: %d\n"
			"t flag: %d\n"
			"first arg: %s\n",
			g_ls_flags & LS_FLAG_l, g_ls_flags & LS_FLAG_R, g_ls_flags & LS_FLAG_a,
			g_ls_flags & LS_FLAG_r, g_ls_flags & LS_FLAG_t,
			(ac > 0) ? *av : "none");
	if (ac == 0)
		add_argument(&arguments, ".");
	while (ac--)
		add_argument(&arguments, *av++);
	//sort_arguments(
	while (arguments)
	{
		ls_print_file(arguments->file_struct, g_ls_flags & LS_FLAG_l);
		arguments = arguments->next;
	}
	return (0);
}
