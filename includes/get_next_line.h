/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:42:06 by tfelwood          #+#    #+#             */
/*   Updated: 2021/12/08 11:42:15 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_buffer
{
	char		*data;
	char		*cur_ptr;
	char		*break_ptr;
	long long	amount;
}	t_buffer;

char	*ft_strjoiner(char *s1, const t_buffer *buf);
char	*get_next_line(int fd);
#endif
