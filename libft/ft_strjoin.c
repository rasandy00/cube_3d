/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:53:24 by andriamr          #+#    #+#             */
/*   Updated: 2026/02/20 16:18:02 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*char	*ft_strcat(const char *dest,const char *src)
{
	int	i;
	int	j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)dest;
	while(dest[i])
		i++;
	while(src[i])
	{
		str[i] = (char)src[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = (char)s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = (char)s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
