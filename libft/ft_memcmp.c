/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:39:57 by andriamr          #+#    #+#             */
/*   Updated: 2025/03/19 10:31:52 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*str1;
	const char	*str2;

	str1 = (char *)s1;
	str2 = (char *)s2;
	if (!s1 || !s2)
		return (str1 - str2);
	return (ft_strncmp(str2, str1, n));
}
/*
#include <stdio.h>
#include <string.h>
int main ()
{

	char s[] = {-128, 0, 127, 0};
//	char sCpy[] = {-128, 0, 127, 0};
	char s2[] = {0, 0, 127, 0};
//	char s3[] = {0, 0, 42, 0};

//	s1 = "erhtg";
//	s2 = "dwffg";
	printf("%d\n", ft_memcmp(s,s2, 1));
	printf("%d\n", memcmp(s,s2, 1));
	return (0);
}*/
