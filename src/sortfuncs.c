/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortfuncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 15:21:55 by lgosse            #+#    #+#             */
/*   Updated: 2016/06/08 11:34:59 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		ft_sort(t_ls *ls, t_ent *ent1, t_ent *ent2)
{
	long		res;

	if (PARSE->opt & FT_LS_F)
		return (0);
	if (PARSE->opt & FT_LS_T)
	{
		res = PARSE->opt & FT_LS_R ? ent1->sec - ent2->sec :
			ent2->sec - ent1->sec;
		if (res == 0)
			res = PARSE->opt & FT_LS_R ? ent1->nsec - ent2->nsec :
			ent2->nsec - ent1->nsec;
		if (res == 0)
		{
			return (PARSE->opt & FT_LS_R ? ft_strcmp(ent2->name, ent1->name) :
				ft_strcmp(ent1->name, ent2->name));
		}
		return (res);
	}
	else
	{
		return (PARSE->opt & FT_LS_R ? ft_strcmp(ent2->name, ent1->name) :
			ft_strcmp(ent1->name, ent2->name));
	}
}
