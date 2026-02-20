/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:47:55 by andriamr          #+#    #+#             */
/*   Updated: 2025/03/19 13:38:29 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && ((n - 1) > i))
		i++;
	return (s1[i] - s2[i]);
}
/*
int main ()
{
	const char *s1;
	const char *s2;

	s1 = "sandy ";
	s2 = "sandy satra";
	printf("%d\n", ft_strncmp(s1,s2, 4));
	return (0);
}*/
