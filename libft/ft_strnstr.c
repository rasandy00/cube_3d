/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:53:34 by andriamr          #+#    #+#             */
/*   Updated: 2025/03/19 14:47:59 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	len_little;

	i = 0;
	len_little = ft_strlen (little);
	if (little[i] == '\0' || (ft_strncmp(&big[i], little, len_little) == 0))
		return ((char *)big);
	if (len == 0)
		return (0);
	while (big[i] && len - 1 > i)
	{
		if (ft_strncmp(&big[i], little, len_little) == 0)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
int main ()
{
	char	*big;
	char	*little;
	big = "sandy kely milay be lotra";
	little = "kely";
	printf("my :%s\n", ft_strnstr(big, little, 1));
	printf("pc :%s\n", ft_strnstr(big, little, 1));
	return (0);
}*/
