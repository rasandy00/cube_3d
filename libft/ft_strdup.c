/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:47:03 by andriamr          #+#    #+#             */
/*   Updated: 2025/03/19 15:01:01 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	i;

	i = ft_strlen(s) + 1;
	str = malloc(sizeof(char) * i);
	if (!str)
		return (NULL);
	ft_strcpy(str, (char *)s);
	return (str);
}
/*
int main ()
{
	char *str;
	str = ft_strdup("sandy");
	printf("%s\n", str);
	free (str);
	return (0);
}*/
