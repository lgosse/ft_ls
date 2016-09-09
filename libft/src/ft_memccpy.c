/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 17:05:50 by lgosse            #+#    #+#             */
/*   Updated: 2015/12/12 13:54:26 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memccpy(void *dst, void const *src, int c, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		*((uint8_t *)(dst + i)) = *((uint8_t *)(src + i));
		if (*(uint8_t *)(dst + i) == (uint8_t)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
