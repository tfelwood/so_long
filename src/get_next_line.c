/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:41:44 by tfelwood          #+#    #+#             */
/*   Updated: 2021/12/08 11:41:58 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_find_eofline(t_buffer *buf)
{
	char	*tmp;

	if (buf->data)
	{
		tmp = buf->cur_ptr;
		while (tmp < buf->data + buf->amount)
		{
			if (*tmp == '\n')
				return (buf->break_ptr = tmp + 1);
			++tmp;
		}
		return (buf->break_ptr = buf->data + buf->amount);
	}
	return (NULL);
}

static void	ft_buf_free(t_buffer *buf)
{
	free(buf->data);
	buf->data = NULL;
}

static char	*ft_buf_update(t_buffer *buf, int fd)
{
	if (!buf->data || buf->break_ptr == buf->data + buf->amount)
	{
		if (!buf->data)
			buf->data = (char *)malloc(BUFFER_SIZE * sizeof(char));
		if (buf->data)
		{
			buf->amount = read(fd, buf->data, BUFFER_SIZE);
			if (buf->amount <= 0)
				return (NULL);
			buf->cur_ptr = buf->data;
			buf->break_ptr = ft_find_eofline(buf);
		}
	}
	else
	{
		buf->cur_ptr = buf->break_ptr;
		buf->break_ptr = ft_find_eofline(buf);
	}
	return (buf->data);
}

char	*get_next_line(int fd)
{
	char			*new_line;
	static t_buffer	buf;
	char			is_str;

	new_line = NULL;
	is_str = 0;
	if (BUFFER_SIZE > 0 && fd >= 0)
	{
		while (!is_str)
		{
			if (!ft_buf_update(&buf, fd))
				break ;
			new_line = ft_strjoin(new_line, &buf);
			if (!new_line || *(buf.break_ptr - 1) == '\n')
				is_str = 1;
		}
	}
	if (!new_line || (buf.data && (buf.break_ptr
				== buf.data + buf.amount || buf.amount <= 0)))
		ft_buf_free(&buf);
	return (new_line);
}
