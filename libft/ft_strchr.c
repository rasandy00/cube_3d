/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:56:56 by andriamr          #+#    #+#             */
/*   Updated: 2025/04/06 10:31:44 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*str;
	int				i;
	unsigned char	j;

	i = 0;
	j = (unsigned char)c;
	str = (char *)s;
	if (j == '\0')
		return (&(str[ft_strlen(s)]));
	while (str[i])
	{
		if (str[i] == j)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
/*
#include <string.h>
#include <stdio.h>
int main ()
{
	char *str;
	str = "sandy milay";
	printf("%s\n", str);
	printf("result: %s\n", ft_strchr(str, 't' + 256));
	printf("result dt: %s\n", strchr(str, 't' + 256));
	return (0);
}
*/
