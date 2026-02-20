/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:16:42 by andriamr          #+#    #+#             */
/*   Updated: 2025/03/19 13:55:29 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*str;
	int				len;
	unsigned char	j;

	len = ft_strlen(s);
	j = (unsigned char)c;
	str = (char *)s;
	if (j == 0)
		return (&str[len]);
	while (len >= 0)
	{
		if (s[len] == j)
			return (&str[len]);
		len--;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
int  main ()
{
	const char *str;
	str = "sandy kely mlay be";
	printf("chaine : %s\n",str);
	printf("result original: %s\n",strrchr(str, 'y'));
	printf("result : %s\n",ft_strrchr(str, 'y'));
	printf("result original: %s\n",strrchr(str, 'y'));
	return (0);
}*/
