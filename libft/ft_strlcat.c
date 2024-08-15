/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:13:58 by tkurukay          #+#    #+#             */
/*   Updated: 2024/08/15 03:38:07 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	ssize;
	size_t	i;

	i = 0;
	ssize = ft_strlen(src);
	while (*dest && size > 0)
	{
		dest++;
		i++;
		size--;
	}
	while (*src && size > 1)
	{
		*dest++ = *src++;
		size--;
	}
	if (size == 1 || *src == '\0')
		*dest = '\0';
	return (ssize + i);
}
