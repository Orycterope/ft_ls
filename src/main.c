/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 20:00:02 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/16 17:20:59 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <errno.h>

t_ls_flags			g_ls_flags = 0;

void		add_file_to_list(char *file_name, t_list **lst)
{
	t_ls_file	*s;

	s = get_file_struct(file_name);
	if (s)
		ft_lstadd(lst, ft_lstnew(s, sizeof(t_ls_file)));
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
	t_list		*arguments;
	//t_ls_file	*file;

	read_flags(&ac, &av);
	arguments = NULL;
	ft_putendl("offset"); //
	if (ac == 0)
		add_file_to_list(".", &arguments);
	while (ac--)
		add_file_to_list(*av++, &arguments);
	sort_file_lst(arguments, 1);
	while (arguments)
	{
		if (((t_ls_file *)arguments->content)->rights[0] == 'd')
			parse_directory(((t_ls_file *)arguments->content)->name, 1);
		else
			ls_print_file(arguments->content);
		arguments = arguments->next;
	}
	return (0);
}
