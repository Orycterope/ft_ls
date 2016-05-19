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

static int should_split_lst(void *content)
{
	t_ls_file *file;

	file = (t_ls_file *)content;
	if (file->rights[0] == 'd')
		return (1);
	else
		return (0);
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

static void	print_parameters(t_list *files, t_list *dirs, int several_args)
{
	while (files)
	{
		ls_print_file(files->content);
		files = files->next;
	}
	while (dirs)
	{
		parse_directory(((t_ls_file *)dirs->content)->name, several_args);
		dirs = dirs->next;
	}
}

int			main(int ac, char **av)
{
	t_list		*arguments;
	int			several_args;
	t_list		*file_args;
	t_list		*dir_args;


	read_flags(&ac, &av);
	arguments = NULL;
	if (ac == 0)
		add_file_to_list(NULL, ".", &arguments);
	several_args = (ac > 1)? 1 : 0;
	while (ac--)
		add_file_to_list(NULL, *av++, &arguments);
	sort_file_lst(arguments, 1);
	arguments = ft_lstsplit(arguments, should_split_lst);
	file_args = (t_list *)arguments->content;
	dir_args = (arguments->next) ? (t_list *)arguments->next->content : NULL;
	print_parameters(file_args, dir_args, several_args);
	ft_lstdel(&file_args, free_file_struct);
	ft_lstdel(&dir_args, free_file_struct);
	ft_lstdel(&arguments, NULL);
	return (0);
}
