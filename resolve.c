/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 13:19:33 by magouin           #+#    #+#             */
/*   Updated: 2016/04/28 18:54:22 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_check2(t_res **res, t_res **p, t_tube *tube)
{
	t_salle *prev;

	p[0] = (*res)->next;
	prev = (*res)->s;
	while (p[0] != p[1])
	{
		while (tube->prev)
			tube = tube->prev;
		while (tube)
		{
			if ((tube->s1 == prev && tube->s2 == (p[0])->s)
					|| (tube->s1 == (p[0])->s && tube->s2 == prev))
			{
				tube->s1->end = 0;
				break ;
			}
			if (tube->next)
				tube = tube->next;
			else
				break ;
		}
		prev = (p[0])->s;
		p[0] = (p[0])->next;
		free((p[0])->prev);
	}
}

void		ft_check(t_res **res, t_tube *tube)
{
	t_res	*p[2];

	while ((*res)->prev)
		*res = (*res)->prev;
	while ((*res)->next)
	{
		p[1] = (*res)->next;
		while (p[1])
		{
			if ((*res)->s == (p[1])->s ||
(diff((*res)->s, (p[1])->s, tube) && (*res)->next->s != (p[1])->s))
			{
				ft_check2(res, p, tube);
				(*res)->s == (p[1])->s ? 0 : ((*res)->next = p[1]);
				(*res)->s == (p[1])->s ? (*res)->next = (p[1])->next : 0;
				(*res)->s == (p[1])->s ? ((p[1])->next)->prev = *res : 0;
				(*res)->s == (p[1])->s ? free(p[0]) : ((p[1])->prev = *res);
				p[1] = (*res)->next;
			}
			else
				p[1] = (p[1])->next;
		}
		(*res)->next ? *res = (*res)->next : 0;
	}
}

void		startend2(t_env *e, int *max, t_res **res)
{
	e->x = 0;
	while (e->x < *max + 1)
	{
		res[e->x] = NULL;
		(e->x)++;
	}
	e->x = 0;
	while (e->tube->prev)
		e->tube = e->tube->prev;
}

void		startend3(t_env *e, t_salle **end, t_res **res)
{
	if ((e->tube->s1 == end[1] && e->tube->s2 == end[0])
			|| (e->tube->s2 == end[1] && e->tube->s1 == end[0]))
	{
		res[e->x] = edit_res(res[e->x], end[0]);
		res[e->x] = edit_res(res[e->x], end[1]);
	}
	else if (e->tube->s1 == end[1])
		backtrack(e->tube->s2, end[0], e->tube, &(res[e->x]))
			? edit_res(res[e->x], end[1]) : 0;
	else if (e->tube->s2 == end[1])
		backtrack(e->tube->s1, end[0], e->tube, &(res[e->x]))
			? edit_res(res[e->x], end[1]) : 0;
	if (res[e->x])
	{
		ft_check(&(res[e->x]), e->tube);
		(e->x)++;
	}
}

void		startend(t_env *e)
{
	t_salle	*end[2];
	t_res	**res;
	int		max;

	max = maxway(e);
	res = malloc(sizeof(t_res*) * (max + 1));
	while ((e->salle)->prev)
		e->salle = (e->salle)->prev;
	while (e->salle)
	{
		((e->salle)->end) ? end[0] = e->salle : 0;
		((e->salle)->start) ? end[1] = e->salle : 0;
		if (!(e->salle)->next)
			break ;
		e->salle = (e->salle)->next;
	}
	startend2(e, &max, res);
	while (e->tube)
	{
		startend3(e, end, res);
		(e->tube->next && e->x < max) ? e->tube = e->tube->next : 0;
		if (!(e->tube->next && e->x < max))
			break ;
	}
	res[0] ? finish(res, e) : ft_err(NULL, NULL, 42);
}
