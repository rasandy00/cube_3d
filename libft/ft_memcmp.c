/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:39:57 by andriamr          #+#    #+#             */
/*   Updated: 2026/02/20 16:17:46 by andriamr         ###   ########.fr       */
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
