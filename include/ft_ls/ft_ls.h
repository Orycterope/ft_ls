/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 18:50:22 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/16 16:59:40 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <time.h>
# include "libft.h"
# define LS_FLAG_l 1
# define LS_FLAG_R 2
# define LS_FLAG_a 4
# define LS_FLAG_r 8
# define LS_FLAG_t 16

typedef	char				t_ls_flags;

typedef struct				s_ls_file
{
	char					*name;
	char					rights[12]; // d-w--w--w-@\0
	unsigned int			links;
	char					*owner;
	char					*group_owner;
	long long				size;
	time_t					last_modif;
	char					*last_modif_str;
	int						minor;
	int						major;
}							t_ls_file;

typedef struct				s_ls_argument
{
	char					*path;
	t_ls_file				*file_struct;
	struct s_ls_argument	*next;
}							t_ls_argument;

void						free_file_struct(t_ls_file *file);
t_ls_file					*get_file_struct(char *filename);
void						ls_print_file(t_ls_file *file);
void						sort_file_lst(t_list *lst, int is_param_lst);
void						print_file_list(t_list *lst);
void						parse_directory(char *dir_name, int print_name);

#endif
