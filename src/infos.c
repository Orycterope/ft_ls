/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 22:44:22 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/13 17:26:26 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <string.h>
#include <time.h>

static void			retrieve_link_content(t_ls_file *f)
{
	char		link_name[2048];
	int			name_size;
	char		*new_path;

	name_size = readlink(f->name, link_name, 2048);
	if (name_size == -1)
	{
		ft_printf("ft_ls : Error while reading link : %s\n", strerror(errno));
		errno = 0;
	}
	else
	{
		link_name[name_size] = '\0';
		new_path = ft_strjoin(" -> ", link_name);
		f->name = ft_strjoin_free(f->name, new_path);
	}
}

static inline void	get_owners(struct stat *s, t_ls_file *f)
{
	struct passwd	*pwd;
	struct group	*grp;

	errno = 0;
	pwd = getpwuid(s->st_uid);
	if (pwd == NULL)
	{
		if (errno)
			ft_printf("Error when retrieving owner: %s\n", strerror(errno));
		f->owner = ft_itoa(s->st_uid);
	}
	else
		f->owner = ft_strdup(pwd->pw_name); // strdup ?
	errno = 0;
	grp = getgrgid(s->st_gid);
	if (grp == NULL)
	{
		if (errno)
			ft_printf("Error when retrieving group: %s\n", strerror(errno));
		f->group_owner = ft_itoa(s->st_gid);
	}
	else
		f->group_owner = ft_strdup(grp->gr_name); // strdup ?
}

static inline void	get_type(struct stat *s, t_ls_file *f)
{
	if (s->st_mode & S_IFDIR)
		f->rights[0] = 'd';
	else if ((s->st_mode & S_IFLNK) == S_IFLNK)
		f->rights[0] = 'l';
	else if (s->st_mode & S_IFCHR)
		f->rights[0] = 'c';
	else if (s->st_mode & S_IFIFO)
		f->rights[0] = 'p';
	else if ((s->st_mode & S_IFBLK) == S_IFBLK)
		f->rights[0] = 'b';
	else if ((s->st_mode & S_IFSOCK) == S_IFSOCK)
		f->rights[0] = 's';
	else if (s->st_mode & S_IFREG)
		f->rights[0] = '-';
}

static inline void	get_rights(struct stat *s, t_ls_file *f)
{
	f->rights[1] = (s->st_mode & S_IRUSR) ? 'r' : '-';
	f->rights[2] = (s->st_mode & S_IWUSR) ? 'w' : '-';
	f->rights[3] = (s->st_mode & S_IXUSR) ? 'x' : '-';
	f->rights[4] = (s->st_mode & S_IRGRP) ? 'r' : '-';
	f->rights[5] = (s->st_mode & S_IWGRP) ? 'w' : '-';
	f->rights[6] = (s->st_mode & S_IXGRP) ? 'x' : '-';
	f->rights[7] = (s->st_mode & S_IROTH) ? 'r' : '-';
	f->rights[8] = (s->st_mode & S_IWOTH) ? 'w' : '-';
	f->rights[9] = (s->st_mode & S_IXOTH) ? 'x' : '-';
	if (s->st_mode & S_ISUID)
		f->rights[3] = (s->st_mode & S_IXUSR) ? 's' : 'S';
	if (s->st_mode & S_ISGID)
		f->rights[6] = (s->st_mode & S_IXGRP) ? 's' : 'S';
}

static inline void	get_last_modif_str(struct stat *s, t_ls_file *f)
{
	time_t	elapsed;
	time_t	t;

	if (time(&t) == (time_t)-1)
	{
		ft_printf("Error while retrieving current time\n");
		return ;
	}
	f->last_modif = s->st_mtimespec.tv_sec;
	f->last_modif_str = ctime(&s->st_mtimespec.tv_sec) + 4; //ft_strdup ?
	elapsed = t - s->st_mtimespec.tv_sec;
	if (elapsed > 15778800 || elapsed < -15778800)
		ft_strncpy(f->last_modif_str + 11, f->last_modif_str + 19, 5);
	f->last_modif_str[16] = '\0';
}

t_ls_file			*get_file_struct(char *filename, int l_flag)
{
	t_ls_file	*file_struct;
	struct stat	s;

	file_struct = (t_ls_file *)ft_memalloc(sizeof(t_ls_file));
	if (lstat(filename, &s))
	{
		ft_printf("Error for file %s : %s\n", filename, strerror(errno));
		return (NULL);
	}
	file_struct->name = ft_strdup(filename);
	if (l_flag)
	{
		get_type(&s, file_struct);
		get_rights(&s, file_struct);
		get_owners(&s, file_struct);
		get_last_modif_str(&s, file_struct);
		file_struct->size = s.st_size;
		file_struct->links = s.st_nlink;
		if (file_struct->rights[0] == 'l')
			retrieve_link_content(file_struct);
	}
	return (file_struct);
}

void				free_file_struct(t_ls_file *file)
{
	free(file->name);
	free(file->owner);
	free(file->group_owner);
	//free(file->last_modif_str);
	free(file);
}
