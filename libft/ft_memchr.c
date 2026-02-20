/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:15:14 by andriamr          #+#    #+#             */
/*   Updated: 2025/03/19 10:25:35 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	j;

	j = (unsigned char)c;
	str = (unsigned char *)s;
	i = 0;
	if (!n || !s)
		return (NULL);
	while (n > i || str[i])
	{
		if (str[i] == j)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
/*
int main ()
{
	char *s1;
	s1 = "sandy kely mlay be 0123456789";
	printf("%s\n", ft_memchr(s1, 'm', 20));
	return (0);
}*/
