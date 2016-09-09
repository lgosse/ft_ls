/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 18:56:05 by lgosse            #+#    #+#             */
/*   Updated: 2015/12/10 17:23:30 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(uint8_t *)(s1 + i) != *(uint8_t *)(s2 + i))
			return (*(uint8_t *)(s1 + i) - *(uint8_t *)(s2 + i));
		i++;
	}
	return (0);
}
