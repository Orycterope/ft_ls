/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 20:00:02 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/16 15:52:50 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <errno.h>

t_ls_flags			g_ls_flags = 0;

/*static void	add_argument(t_ls_argument **lst, char *path)
{
	t_ls_argument	*new;

	new = (t_ls_argument *)ft_memalloc(sizeof(t_ls_argument));
	new->next = *lst;
	new->path = path;
	new->file_struct = get_file_struct(path, g_ls_flags & LS_FLAG_l);
	*lst = new;
}*/

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
	t_list	*arguments;

	read_flags(&ac, &av);
	arguments = NULL;
	ft_putendl("offset"); //
	if (ac == 0)
		ft_lstadd(&arguments,
				ft_lstnew(get_file_struct("."), sizeof(t_ls_file)));
	while (ac--)
		ft_lstadd(&arguments,
				ft_lstnew(get_file_struct(*av++), sizeof(t_ls_file)));
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
