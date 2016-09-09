/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 17:46:30 by lgosse            #+#    #+#             */
/*   Updated: 2016/06/08 11:50:00 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_ent		*ft_treat_entry(t_ls *ls, char *path, char *name, LS_STAT *info)
{
	t_ent	*ent;

	if (!(ent = (t_ent *)malloc(sizeof(t_ent))))
		exit(ERRMALLOC);
	*ent = (t_ent){name, path, ft_getdate(ls, info),
		ft_getuname(ls, info), ft_getgroup(ls, info), ft_getmode(info),
		ft_getlnk(info, name, path), ft_itoa(info->st_nlink), NULL, NULL, NULL,
		0, 0};
	if (PARSE->opt & FT_LS_U && ((ent->nsec = info->st_atimespec.tv_nsec) || 1))
		ent->sec = info->st_atimespec.tv_sec;
	else if (PARSE->opt & FT_LS_MU && ((ent->nsec = info->st_ctimespec.tv_nsec)
		|| 1))
		ent->sec = info->st_ctimespec.tv_sec;
	else if ((ent->nsec = info->st_mtimespec.tv_nsec) || 1)
		ent->sec = info->st_mtimespec.tv_sec;
	if (ft_is_to_print(ls, ent))
		ft_getnbytes(ls, info, ent);
	ls->l_date < (long)ft_strlen(ent->date) && ft_is_to_print(ls, ent) ?
		ls->l_date = ft_strlen(ent->date) : 0;
	ls->l_nblinks < (long)ft_strlen(ent->nb_link) && ft_is_to_print(ls, ent) ?
		ls->l_nblinks = ft_strlen(ent->nb_link) : 0;
	ls->l_mode = 11;
	return (ent);
}

static int	ft_treat_args2(t_ls *ls, char *name, t_list **ent, t_dir **dir)
{
	t_list			*newlst;
	t_dir			*new;
	LS_STAT			info;

	if (lstat(name, &info) != -1)
	{
		if (!S_ISDIR(info.st_mode) && !(S_ISLNK(info.st_mode) &&
			!(PARSE->opt & FT_LS_L)))
		{
			if (!(newlst = (t_list *)malloc(sizeof(t_list))))
				return (0);
			newlst->content = ft_treat_entry(ls, NULL, ft_strdup(name), &info);
			newlst->next = NULL;
			ft_lstaddsort(ls, ent, newlst);
		}
		else if ((new = MALLOCDIR) &&
			(new->dir = ft_treat_entry(ls, NULL, ft_strdup(name), &info)))
			ft_diraddsort(ls, dir, new);
		else
			return (0);
		return (1);
	}
	else
		ft_treaterror(name);
	return (1);
}

int			ft_treat_args(t_ls *ls)
{
	t_list	*tmp;
	t_list	*ent;
	t_dir	*dir;

	tmp = PARSE->args;
	ent = NULL;
	dir = NULL;
	if (tmp)
		while (tmp)
		{
			if (!ft_strcmp(".", tmp->content) || !ft_strcmp("..", tmp->content))
				tmp->content = ft_strjoin_n_free(tmp->content, "/");
			if (!ft_treat_args2(ls, tmp->content, &ent, &dir))
				return (ft_printf("Error malloc\n%@", 2));
			tmp = tmp->next;
		}
	else if ((ls->fst = 1) && !ft_treat_args2(ls, ".", &ent, &dir))
		return (ft_printf("Error malloc\n%@", 2));
	PARSE->opt |= FT_LS_ARG;
	ft_read_entries(ls, ent);
	PARSE->opt &= ~FT_LS_ARG;
	ls->doprint = (!ent && dir && !dir->next &&
		ft_strcmp(".", dir->dir->name)) ? 0 : 1;
	(dir && (!ent || ft_printf("\n"))) ? ft_treatdir(ls, dir) : 0;
	return (0);
}
