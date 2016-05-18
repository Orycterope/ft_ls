/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 20:00:02 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/18 19:26:58 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <errno.h>

t_ls_flags			g_ls_flags = 0;

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
		ft_printf_fd(2, "ft_ls: illegal option -- %c\n"
				"usage: ft_ls [-lRart] [file ...]\n", flag);
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
	t_list		*arguments;
	t_list		*first_arg;


	read_flags(&ac, &av);
	arguments = NULL;
	if (ac == 0)
		add_file_to_list(NULL, ".", &arguments);
	while (ac--)
		add_file_to_list(NULL, *av++, &arguments);
	sort_file_lst(arguments, 1);
	first_arg = arguments;
	while (arguments)
	{
		if (((t_ls_file *)arguments->content)->rights[0] == 'd')
			parse_directory(((t_ls_file *)arguments->content)->name,
					first_arg->next != 0);
		else
			ls_print_file(arguments->content);
		arguments = arguments->next;
	}
	ft_lstdel(&first_arg, free_file_struct);
	return (0);
}
