/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_calloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:35:54 by andriamr          #+#    #+#             */
/*   Updated: 2025/03/13 20:46:30 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
void	*ft_calloc(size_t nmemb, size_t size)//size = sizeof
{
	void	*str;

	str = malloc (nmemb * size)
	if (!str)
		return (NULL);
	ft_bzero (str, nmemb * size);
	return (str);
}