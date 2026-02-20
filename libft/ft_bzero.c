/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:59:57 by andriamr          #+#    #+#             */
/*   Updated: 2025/03/13 18:16:18 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}
/*
int main()
{
	unsigned char str[11] = "sandykely00";
	write(1, &str[0] , 11);
	write(1 , "\n", 1);
	ft_bzero(str , 5);
	write(1, &str[0], 11);
	return (0);
}*/
