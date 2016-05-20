/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 20:00:02 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/20 14:26:41 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <errno.h>
#include <sys/ioctl.h>

t_ls_flags			g_ls_flags = 0;
int					g_termcolnum = 0;

static void	split_parameters(t_list **files, t_list **dirs)
{
	t_list	*previous;
	t_list	*i;

	previous = NULL;
	i = *files;
	while (i && ((t_ls_file*)i->content)->rights[0] != 'd')
	{
		previous = i;
		i = i->next;
	}
	*dirs = i;
	if (previous == NULL)
		*files = NULL;
	else
		previous->next = NULL;
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
	else if (flag == 'A')
		g_ls_flags |= LS_FLAG_A;
	else if (flag == '1')
		g_ls_flags |= LS_FLAG_1;
	else
	{
		ft_printf_fd(2, "ft_ls: illegal option -- %c\n"
				"usage: ft_ls [-1lRaArt] [file ...]\n", flag);
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
	t_dirinfo	d;

	if (files)
	{
		get_dir_infos(&d, files);
		print_file_list(files, &d);
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
	t_list		*dir_args;
	struct		winsize ws;


	read_flags(&ac, &av);
	if ((g_ls_flags & LS_FLAG_l) == 0)
	{
		ioctl(0, TIOCGWINSZ, &ws);
		g_termcolnum = ws.ws_col;
	}
	arguments = NULL;
	if (ac == 0)
		add_file_to_list(NULL, ".", &arguments);
	several_args = (ac > 1) ? 1 : 0;
	while (ac--)
		add_file_to_list(NULL, *av++, &arguments);
	sort_file_lst(arguments, 1);
	split_parameters(&arguments, &dir_args);
	print_parameters(arguments, dir_args, several_args);
	ft_lstdel(&arguments, free_file_struct);
	ft_lstdel(&dir_args, free_file_struct);
	return (0);
}
