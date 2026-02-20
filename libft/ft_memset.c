/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:54:41 by andriamr          #+#    #+#             */
/*   Updated: 2025/03/17 18:06:15 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = (char)c;
		i++;
	}
	return (s);
}
/*
int main ()
{
	char s[10] = "sandykely0";
	write(1, &s, 10);
	write(1, "\n", 1);
	ft_memset(s, 'a', 4);
	write(1, &s, 10);
	return (0);
}*/
