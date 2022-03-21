/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:42:23 by tfelwood          #+#    #+#             */
/*   Updated: 2021/12/08 11:42:31 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char const *s)
{
	size_t	length;

	length = 0;
	if (s)
	{
		while (*s++)
			++length;
	}
	return (length);
}

char	*ft_strjoin(char *s1, const t_buffer *buf)
{
	char	*new_str;
	char	*tmp;
	size_t	size;

	new_str = NULL;
	if (buf && buf->data && buf->cur_ptr < buf->break_ptr)
	{
		size = ft_strlen(s1) + (buf->break_ptr - buf->cur_ptr) + 1;
		new_str = (char *) malloc(size * sizeof(char));
		if (new_str)
		{
			tmp = s1;
			while (tmp && *tmp)
				*new_str++ = *tmp++;
			tmp = buf->cur_ptr;
			while (tmp != buf->break_ptr)
				*new_str++ = *tmp++;
			*new_str = 0;
			new_str -= size - 1;
		}
	}
	free(s1);
	return (new_str);
}
