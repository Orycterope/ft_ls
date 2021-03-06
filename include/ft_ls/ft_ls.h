/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 18:50:22 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/20 15:51:36 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <time.h>
# include <sys/stat.h>
# include "libft.h"
# define LS_FLAG_L_LOWER 1
# define LS_FLAG_R_UPPER 2
# define LS_FLAG_R_LOWER 4
# define LS_FLAG_T_LOWER 8
# define LS_FLAG_A_UPPER 16
# define LS_FLAG_A_LOWER 32
# define LS_FLAG_1 64

typedef	char				t_ls_flags;

typedef struct				s_ls_file
{
	char					*name;
	char					*path;
	char					rights[12];
	unsigned int			links;
	char					*owner;
	char					*group_owner;
	long long				size;
	time_t					last_modif;
	char					*last_modif_str;
	int						minor;
	int						major;
	long long				blocks;
}							t_ls_file;

typedef struct
{
	int						file_number;
	long long				total_blocks;
	int						name_max_length;
	int						links_max_length;
	size_t					owner_max_length;
	size_t					group_max_length;
	int						size_max_length;
	int						minor_max_length;
	int						major_max_length;
	int						columns;
	int						lines;
}							t_dirinfo;

void						free_file_struct(void *f, size_t s);
t_ls_file					*get_file_struct(char *full_path, char *name);
void						ls_print_file(t_ls_file *file);
void						sort_file_lst(t_list *lst, int is_param_lst);
void						print_file_list(t_list *lst, t_dirinfo *d);
void						parse_directory(char *dir_name, int print_name);
void						get_dir_infos(t_dirinfo *d, t_list *lst);
void						add_file_to_list(char *d, char *f, t_list **lst);
void						retrieve_link_content(t_ls_file *f);
void						get_owners(struct stat *s, t_ls_file *f);
void						get_type(struct stat *s, t_ls_file *f);
void						get_rights(struct stat *s, t_ls_file *f);
void						get_last_modif_str(struct stat *s, t_ls_file *f);

#endif
