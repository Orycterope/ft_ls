/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/12 18:09:28 by jriallan          #+#    #+#             */
/*   Updated: 2016/01/14 12:11:31 by jriallan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define BUFF_SIZE 2048

typedef struct		s_file
{
	int				fd;
	char			*text;
	int				size_text;
	struct s_file	*next;
}					t_file;

int					get_next_line(int const fd, char **line);

#endif
