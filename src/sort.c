/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 13:39:15 by lgosse            #+#    #+#             */
/*   Updated: 2016/06/08 11:31:28 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static int	ft_insert(t_list **list, t_list *prev, t_list *tmp, t_list *elem)
{
	if (prev)
		prev->next = elem;
	else
		*list = elem;
	elem->next = tmp;
	return (1);
}

int			ft_lstaddsort(t_ls *ls, t_list **list, t_list *elem)
{
	t_list	*prev;
	t_list	*tmp;

	elem->next = NULL;
	if (ft_is_to_print(ls, elem->content) == 0)
		return (0);
	if (*list == NULL && (*list = elem))
		return (1);
	prev = NULL;
	tmp = *list;
	while (tmp)
	{
		if (ft_sort(ls, tmp->content, elem->content) > 0 &&
			ft_insert(list, prev, tmp, elem))
			return (1);
		prev = tmp;
		tmp = tmp->next;
	}
	ft_insert(list, prev, tmp, elem);
	return (1);
}

static int	ft_insertdir(t_dir **list, t_dir *prev, t_dir *tmp, t_dir *elem)
{
	if (prev)
		prev->next = elem;
	else
		*list = elem;
	elem->next = tmp;
	return (1);
}

int			ft_diraddsort(t_ls *ls, t_dir **list, t_dir *elem)
{
	t_dir	*prev;
	t_dir	*tmp;

	elem->next = NULL;
	if ((ft_is_to_print(ls, elem->dir) == 0 ||
		(ft_strcmp(".", elem->dir->name) == 0 ||
		ft_strcmp("..", elem->dir->name) == 0)) && !(ls->fst && !(ls->fst = 0)))
		return (0);
	if (*list == NULL && (*list = elem))
		return (1);
	prev = NULL;
	tmp = *list;
	while (tmp)
	{
		if (ft_sort(ls, tmp->dir, elem->dir) > 0 &&
			ft_insertdir(list, prev, tmp, elem))
			return (1);
		prev = tmp;
		tmp = tmp->next;
	}
	ft_insertdir(list, prev, tmp, elem);
	return (1);
}
