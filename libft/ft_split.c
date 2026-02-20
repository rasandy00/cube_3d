/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:48:51 by andriamr          #+#    #+#             */
/*   Updated: 2025/04/08 11:24:35 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(char const	*s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			count++;
		i++;
	}
	if (s[i - 1] != c)
		count++;
	return (count);
}

static size_t	len_word(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	dest = (char **) ft_calloc(sizeof (char *), (count_word(s, c) + 1));
	if (!dest)
		return (NULL);
	while (j < count_word(s, c))
	{
		while (s[i] == c)
			i++;
		k = 0;
		dest[j] = ft_calloc(sizeof (char), (len_word(&s[i], c) + 1));
		if (!dest[j])
			return (NULL);
		while (s[i] != '\0' && s[i] != c)
			dest[j][k++] = s[i++];
		j++;
	}
	return (dest);
}
/*#include <stdio.h>
int		main(void)
{
	size_t i = 0;
	char **tab;
	char *str;
	str = "    sandy          t\nt mlay elah       ";
	tab = ft_split(str, '\n');
	while (i < count_word(str, '\n'))
	{
		printf("string %ld : %s\n", i+1, tab[i]);
		i++;
	}
	return (0);
}*/
