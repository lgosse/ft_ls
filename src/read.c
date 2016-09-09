/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 13:53:31 by lgosse            #+#    #+#             */
/*   Updated: 2016/06/08 10:27:06 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int			ft_is_to_print(t_ls *ls, t_ent *ent)
{
	t_list	*tmp;

	tmp = PARSE->args;
	while (tmp)
	{
		if (!ft_strcmp(tmp->content, ent->name))
			return (2);
		tmp = tmp->next;
	}
	if ((*ent->name) != '.')
		return (1);
	else if ((ft_strcmp(".", ent->name) && ft_strcmp("..", ent->name)) &&
		PARSE->opt & FT_LS_MA)
		return (1);
	else if (PARSE->opt & FT_LS_A)
		return (1);
	return (0);
}

static void	ft_print_name(t_ent *ent)
{
	if ((ent->mode[3] == 's' || ent->mode[3] == 'S') &&
		ft_strchr("x-", ent->mode[6]) && ft_strchr("x-", ent->mode[9]))
		ft_printf("%[\\r, d]T%s%[0]T", ent->name);
	if ((ent->mode[6] == 's' || ent->mode[6] == 'S') &&
		ft_strchr("x-", ent->mode[3]) && ft_strchr("x-", ent->mode[9]))
		ft_printf("%[\\c, d]T%s%[0]T", ent->name);
	else if ((ent->mode[9] == 't' || ent->mode[9] == 'T') &&
		ft_strchr("x-", ent->mode[6]) && ft_strchr("x-", ent->mode[3]))
		ft_printf("%[\\g, d]T%s%[0]T", ent->name);
	else if (*(ent->mode) == 'd')
		ft_printf("%[c,B]T%s%[0]T", ent->name);
	else if (*(ent->mode) == 'l')
		ft_printf("%[m]T%s%[0]T", ent->name);
	else if (*(ent->mode) == 'c')
		ft_printf("%[\\y, b]T%s%[0]T", ent->name);
	else if (*(ent->mode) == 'b')
		ft_printf("%[\\c, b]T%s%[0]T", ent->name);
	else if (ent->mode[3] == 's')
		ft_printf("%[\\r, d]T%s%[0]T", ent->name);
	else if (ent->mode[9] == 't')
		ft_printf("%[\\g, d]T%s%[0]T", ent->name);
	else if (ent->mode[3] == 'x')
		ft_printf("%[r]T%s%[0]T", ent->name);
	else
		ft_printf("%s", ent->name);
}

void		ft_readlfmt(t_ls *ls, t_ent *ent)
{
	if (PARSE->opt & FT_LS_L)
	{
		ft_printf("%-*s%*s %-*s%-*s", ls->l_mode + 1, ent->mode,
			ls->l_nblinks, ent->nb_link, ls->l_user + 2, ent->uname,
			ls->l_group + 1, ent->grname);
		if (ent->nb_bytes)
		{
			ls->l_major + ls->l_minor + 1 < ls->l_nbytes ?
			ft_printf("%*s", ls->l_nbytes + 1, ent->nb_bytes) :
			ft_printf("%*s", ls->l_major + ls->l_minor + 4, ent->nb_bytes);
		}
		else
		{
			ft_printf("%*s,%*s", ls->l_major + 2, ent->major,
				ls->l_minor + 1, ent->minor);
		}
		ft_printf("%*s ", ls->l_date + 1, ent->date);
	}
	if (PARSE->opt & FT_LS_MG)
		ft_print_name(ent);
	else
		ft_printf("%s", ent->name);
	PARSE->opt & FT_LS_L && ent->lnk ? ft_printf("%s\n", ent->lnk) :
		ft_printf("\n");
}

void		ft_read_entries(t_ls *ls, t_list *ents)
{
	t_list	*tmp2;
	t_list	*tmp;
	t_ent	*ent;

	tmp = ents;
	if (PARSE->opt & FT_LS_L && ents && !(PARSE->opt & FT_LS_ARG))
		ft_printf("total %d\n", ls->total);
	while (tmp)
	{
		ent = tmp->content;
		if (ft_is_to_print(ls, ent))
			ft_readlfmt(ls, ent);
		ft_free_ent(&ent);
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
}
