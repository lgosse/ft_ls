/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 16:09:53 by lgosse            #+#    #+#             */
/*   Updated: 2016/06/08 11:43:28 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <libft.h>
# include <libc.h>
# include <pwd.h>
# include <grp.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>

# define FT_LS_OPT	parse->opt
# define PARSE		ls->parse
# define ATIME		info->st_atimespec.tv_sec
# define CTIME		info->st_ctimespec.tv_sec
# define MTIME		info->st_mtimespec.tv_sec
# define MONTHS		0xED4E00
# define LS_STAT	struct stat
# define LS_MODE	info->st_mode
# define MALLOCDIR	(t_dir *)malloc(sizeof(t_dir))

# define FT_LS_L	0x1
# define FT_LS_R	0x2
# define FT_LS_A	0x4
# define FT_LS_MR	0x8
# define FT_LS_T	0x10
# define FT_LS_U	0x20
# define FT_LS_MU	0x40
# define FT_LS_MA	0x80
# define FT_LS_F	0x100
# define FT_LS_MG	0x200
# define FT_LS_ARG	0x1000

typedef struct		s_ent
{
	char			*name;
	char			*path;
	char			*date;
	char			*uname;
	char			*grname;
	char			*mode;
	char			*lnk;
	char			*nb_link;
	char			*nb_bytes;
	char			*major;
	char			*minor;
	long			sec;
	long			nsec;
}					t_ent;

typedef struct		s_ls
{
	t_parse			*parse;
	int				total;
	int				l_mode;
	int				l_nblinks;
	int				l_user;
	int				l_group;
	int				l_nbytes;
	int				l_date;
	int				l_major;
	int				l_minor;
	int				fst;
	int				begin;
	int				doprint;
}					t_ls;

typedef struct		s_dir
{
	t_ent			*dir;
	size_t			content_size;
	struct s_dir	*next;
	t_list			*l_ent;
	struct s_dir	*l_dir;
	char			*path;
}					t_dir;

int					ft_is_to_print(t_ls *ls, t_ent *ent);
void				ft_treatdir(t_ls *ls, t_dir *dir);
int					ft_treat_args(t_ls *ls);
t_ent				*ft_treat_entry(t_ls *ls, char *path, char *name,
	LS_STAT *info);
int					ft_diraddsort(t_ls *ls, t_dir **list, t_dir *elem);
int					ft_lstaddsort(t_ls *ls, t_list **list, t_list *elem);
int					ft_sort(t_ls *ls, t_ent *ent1, t_ent *ent2);
char				*ft_getdate(t_ls *ls, LS_STAT *info);
char				*ft_getuname(t_ls *ls, LS_STAT *info);
char				*ft_getgroup(t_ls *ls, LS_STAT *info);
char				*ft_getmode(LS_STAT *info);
char				*ft_getlnk(LS_STAT *info, char *name, char *path);
void				ft_getnbytes(t_ls *ls, LS_STAT *info, t_ent *ent);
void				ft_read_entries(t_ls *ls, t_list *ent);
t_dir				*ft_free_dir(t_dir *dir);
void				ft_free_ent(t_ent **truc);
t_ent				*ft_dirdup(t_ent *ent);
int					ft_treaterror(char *name);
int					ft_is_error_to_treat(t_ls *ls, char *name);
char				*ft_joinpath(char *name);

#endif
