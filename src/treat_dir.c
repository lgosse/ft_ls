/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 11:15:48 by lgosse            #+#    #+#             */
/*   Updated: 2016/06/08 11:47:42 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void		ft_setrecall(t_ls *ls, t_dir *dir)
{
	t_dir	*c_dir;
	char	*tmp;

	if (!dir)
		return ;
	c_dir = dir->l_dir;
	while (c_dir)
	{
		tmp = c_dir->dir->name;
		*(c_dir->dir) = (t_ent){ft_strjoin(dir->path, tmp), NULL, NULL, NULL,
			NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0};
		FT_MEMDEL(tmp);
		(void)ls;
		c_dir = c_dir->next;
	}
	c_dir = dir->l_dir;
	ft_treatdir(ls, c_dir);
}

static int	ft_adddir(t_ls *ls, t_dir **dir, t_ent *newlst, LS_STAT *info)
{
	t_dir *new;

	if (PARSE->opt & FT_LS_MR && (S_ISDIR(info->st_mode) ||
		(S_ISLNK(info->st_mode) && !(PARSE->opt & FT_LS_L))))
	{
		if (!(new = (t_dir *)malloc(sizeof(t_dir))))
			return (0);
		new->dir = ft_dirdup(newlst);
		if (ft_diraddsort(ls, &((*dir)->l_dir), new) == 0)
			FT_MEMDEL(new);
	}
	return (1);
}

static int	ft_treatdir2(t_ls *ls, char *path, char *name, t_dir **dir)
{
	char			*join;
	t_list			*newlst;
	LS_STAT			info;

	join = ft_strjoin(path, name);
	if (lstat(join, &info) != -1)
	{
		FT_MEMDEL(join);
		if (!(newlst = (t_list *)malloc(sizeof(t_list))))
			return (0);
		newlst->content = ft_treat_entry(ls, path, name, &info);
		if (ft_lstaddsort(ls, &(*dir)->l_ent, newlst) == 0)
		{
			ft_free_ent((t_ent**)&(newlst->content));
			FT_MEMDEL(newlst);
			return (1);
		}
		if (!ft_adddir(ls, dir, newlst->content, &info))
			return (0);
	}
	else if (ft_is_error_to_treat(ls, name))
		return (ft_treaterror(name));
	else
		return (-1);
	return (1);
}

static int	ft_treatdirnext(t_ls *ls, t_dir *tmp, DIR *sdir)
{
	char			*name;
	struct dirent	*dirent;
	int				ret;

	ret = 1;
	if (ft_strcmp(".", tmp->dir->name) &&
		ft_is_to_print(ls, tmp->dir) + 1 && (ls->doprint || !(ls->doprint = 1)))
	{
		*(tmp->dir->name) != '.' && !PARSE->args ? ft_printf("./") : 0;
		ft_printf("%s:\n", tmp->dir->name);
	}
	while ((dirent = readdir(sdir)))
	{
		name = ft_strndup(dirent->d_name, dirent->d_namlen);
		if (!(ret = ft_treatdir2(ls, tmp->path, name, &tmp)) && ERRMALLOC)
			return (0);
	}
	ft_read_entries(ls, tmp->l_ent);
	closedir(sdir);
	if (PARSE->opt & FT_LS_MR)
		ft_setrecall(ls, tmp);
	return (ret);
}

void		ft_treatdir(t_ls *ls, t_dir *dir)
{
	int				ret;
	t_dir			*tmp;
	DIR				*sdir;

	tmp = dir;
	while (tmp)
	{
		*ls = (t_ls){ls->parse, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ls->begin,
			ls->doprint};
		tmp->l_dir = NULL;
		tmp->l_ent = NULL;
		tmp->path = ft_joinpath(tmp->dir->name);
		if ((sdir = opendir(tmp->path)))
		{
			(ls->begin != 1 || (ls->begin = 0)) ? ft_printf("\n") : 0;
			if (!(ret = ft_treatdirnext(ls, tmp, sdir)))
				return ;
			if (ret == -1)
				ft_treaterror(tmp->dir->name);
		}
		else if (ft_printf("\n%s:\n", tmp->path))
			ft_treaterror(tmp->dir->name);
		tmp = ft_free_dir(tmp);
	}
}
