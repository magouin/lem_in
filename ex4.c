/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex4.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 13:00:29 by magouin           #+#    #+#             */
/*   Updated: 2016/04/29 13:00:31 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_tube(t_tube *sl)
{
	while (sl->prev)
		sl = sl->prev;
	while (sl)
	{
		ft_printf("salle1  : %s\nsalle2 : %s\nx = %d\ny =%d\n\n"
				, sl->s1->name, sl->s2->name, sl->x, sl->y);
		sl = sl->next;
	}
}

void	comment2(char **split, t_env *e)
{
	split[0][0] == 'L' || !((e->salle)->name =
	(char*)malloc(sizeof(char) * (ft_strlen(split[0]) + 1)))
		? ft_err(NULL, NULL, 3) : 0;
	ft_strcpy((e->salle)->name, split[0]);
	integer(split[1]);
	integer(split[2]);
	(e->salle)->x = ft_atoi(split[1]);
	(e->salle)->y = ft_atoi(split[2]);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split);
}

int		comment(t_env *e, char **line)
{
	char		**split;

	get_next_line(0, line);
	e->salle = edit_sl(e->salle);
	while ((*line)[0] == '#')
	{
		!(ft_strcmp(*line, "##start")) ? (e->salle)->start = 1 : 0;
		!(ft_strcmp(*line, "##end")) ? (e->salle)->end = 1 : 0;
		get_next_line(0, line);
	}
	split = ft_strsplit(*line, ' ');
	split[0] == NULL ? ft_err(NULL, NULL, 4) : 0;
	if (split[1] == NULL || split[2] == NULL || split[3] != NULL)
	{
		free(split[0]);
		free(split);
		return (0);
	}
	comment2(split, e);
	return (1);
}

void	check(t_salle *sl)
{
	t_salle	*p;
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (sl->prev)
		sl = sl->prev;
	while (sl)
	{
		p = sl->next;
		while (p)
			(p->name == sl->name) ? ft_err(NULL, NULL, 5) : (p = p->next);
		sl->start ? start++ : 0;
		sl->end ? end++ : 0;
		sl = sl->next;
	}
	start != 1 || end != 1 ? ft_err(NULL, NULL, 6) : 0;
}

void	tubes2(t_env *e, char **split, int *dim)
{
	while ((e->salle)->prev != NULL)
		e->salle = (e->salle)->prev;
	while (e->salle != NULL && ft_strcmp((e->salle)->name, split[1]))
		e->salle = (e->salle)->next;
	e->salle != NULL ? (e->tube)->s2 = e->salle : ft_err(NULL, NULL, 7);
	(e->tube)->x = dim[0] - (e->salle)->x;
	(e->tube)->y = dim[1] - (e->salle)->y;
	free(split[0]);
	free(split[1]);
	free(split);
}
