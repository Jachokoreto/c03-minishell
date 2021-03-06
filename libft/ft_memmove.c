/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 16:30:07 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/30 12:33:05 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			index;
	unsigned char	*dest;
	unsigned char	*sorce;

	dest = (unsigned char *)dst;
	sorce = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	index = 0;
	if (sorce < dest)
	{
		index = len;
		while (index > 0)
		{
			dest[index - 1] = sorce[index - 1];
			index--;
		}
	}
	else
	{
		dest = ft_memcpy(dst, src, len);
	}
	return (dest);
}
