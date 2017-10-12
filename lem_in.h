/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:59:18 by magouin           #+#    #+#             */
/*   Updated: 2016/04/28 11:17:56 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <stdlib.h>
# include <stdio.h>
# include "get_next_line/get_next_line.h"
# include "ft_printf/includes/ft_printf.h"

typedef struct		s_salle
{
	int				x;
	int				y;
	char			*name;
	int				start;
	int				end;
	struct s_salle	*next;
	struct s_salle	*prev;
}					t_salle;

typedef struct		s_tube
{
	int				x;
	int				y;
	t_salle			*s1;
	t_salle			*s2;
	struct s_tube	*next;
	struct s_tube	*prev;
}					t_tube;

typedef struct		s_env
{
	int				fourmie;
	int				x;
	t_salle			*salle;
	t_tube			*tube;
	int				size;
}					t_env;

typedef struct		s_res
{
	int				size;
	int				end;
	int				place;
	t_salle			*s;
	int				fourmie;
	struct s_res	*next;
	struct s_res	*prev;
}					t_res;
void				print_solve4(t_res **r, t_env *e, int ma, int mx);
void				free_salle(t_salle *tube);
int					setouche(t_tube *tube, t_salle *s, t_salle *end);
t_res				*edit_res(t_res *sl, t_salle *s);
int					backtrack(t_salle *s, t_salle *d, t_tube *t, t_res **r);
void				print_res(t_res **res);
int					diff(t_salle *s, t_salle *p, t_tube *tube);
int					backtrack2(t_salle *s, t_salle *e, t_tube *t, t_res **r);
int					maxway(t_env *e);
void				free_tube(t_tube *tube);
void				print_solve5(t_res **res, int max, int *y, int x);
void				print_solve(t_res **res, t_env *e, int max);
void				expres(t_res *res, t_env *e);
int					sort(int **min, int max);
void				print_solve1(t_res **res, int x, int y, int *max);
void				print_solve2(t_res **res, int max, int *y, t_env *e);
void				print_solve3(t_res **res, t_env *e, int *y, int max);
t_salle				*edit_sl(t_salle *sl);
t_tube				*edit_tb(t_tube *sl);
void				integer(char *split);
void				print_salle(t_salle *sl);
void				print_tube(t_tube *sl);
void				comment2(char **split, t_env *e);
int					comment(t_env *e, char **line);
void				check(t_salle *sl);
void				tubes2(t_env *e, char **split, int *dim);
void				print_res(t_res **res);
int					backtrack2(t_salle *s, t_salle *e, t_tube *t, t_res **r);
void				finish(t_res **res, t_env *e);
void				ft_err(t_env *e, int *i, int x);
void				startend(t_env *e);
#endif
