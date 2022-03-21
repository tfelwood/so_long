
#include "so_long.h"

void	ft_putstr_fd(const char *s, int fd)
{
	while (s && *s)
		write(fd, s++, 1);
}

void	*ft_memset(void *b, int c, size_t len)
{
	while (len--)
		((unsigned char *)b)[len] = (unsigned char)c;
	return (b);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	str_size;
	char	*new_str;

	if (s2)
	{
		str_size = ft_strlen(s1) + ft_strlen(s2) + 1;
		new_str = malloc(str_size);
		if (new_str)
		{
			new_str[str_size - 1] = 0;
			while (*s1)
				*new_str++ = *s1++;
			while (*s2)
				*new_str++ = *s2++;
			return (new_str - str_size + 1);
		}
	}
	return (NULL);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
