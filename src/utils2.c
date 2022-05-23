/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:32:34 by tfelwood          #+#    #+#             */
/*   Updated: 2022/05/22 20:32:37 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

static size_t	ft_num_length(long long num)
{
	size_t	size;

	size = 1;
	while (num / 10 != 0)
	{
		num /= 10;
		++size;
	}
	return (size);
}

static void	ft_put_digit(long long n, size_t idx, char *str)
{
	if (n / 10)
		ft_put_digit (n / 10, idx - 1, str);
	str[idx] = '0' + (char)(n % 10);
}

char	*ft_itoa(int n)
{
	size_t		len;
	char		*str;
	char		is_neg;
	long long	_n;

	_n = n;
	is_neg = 0;
	if (_n < 0)
	{
		_n = -_n;
		is_neg = 1;
	}
	len = ft_num_length(_n) + is_neg;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = 0;
	if (is_neg)
		str[0] = '-';
	ft_put_digit(_n, len - 1, str);
	return (str);
}

static void	ft_rec_putnbr(long long n, int fd)
{
	char	s;

	if (n / 10)
		ft_rec_putnbr (n / 10, fd);
	s = '0' + (char)(n % 10);
	write(fd, &s, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	_nbr;

	_nbr = n;
	if (_nbr < 0)
	{
		write(fd, "-", 1);
		_nbr = -_nbr;
	}
	ft_rec_putnbr(_nbr, fd);
}
