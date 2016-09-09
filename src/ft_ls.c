/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 16:08:42 by lgosse            #+#    #+#             */
/*   Updated: 2016/06/08 11:43:31 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		main(int ac, char **av)
{
	t_ls	*ls;

	if (!(ls = (t_ls *)malloc(sizeof(t_ls))))
		return (ft_printf("Error malloc\n%@", 2));
	*ls = (t_ls){ft_parse(ac, av, "lraRtuUAfG1"),
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
	if (!ls->parse)
		return (-1);
	if (PARSE->opt & 0x800)
		PARSE->opt &= ~FT_LS_L;
	ft_treat_args(ls);
	ft_free_parse(PARSE);
	free(ls);
	return (1);
}
