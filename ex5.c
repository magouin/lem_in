/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 13:21:24 by magouin           #+#    #+#             */
/*   Updated: 2016/04/29 13:51:45 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			setouche(t_tube *tube, t_salle *s, t_salle *end)
{
	while (tube->prev)
		tube = tube->prev;
	while (tube)
	{
		if (((s == tube->s1 && end == tube->s2) ||
					(s == tube->s2 && end == tube->s1)))
		{
			tube->s1->end = 1;
			tube->s2->end = 1;
			return (1);
		}
		tube = tube->next;
	}
	return (0);
}

t_res		*edit_res(t_res *sl, t_salle *s)
{
	t_res *s2;

	s2 = malloc(sizeof(t_res));
	if (sl)
		sl->next = s2;
	s2->prev = sl;
	s2->size = 0;
	s2->end = 0;
	s2->fourmie = 0;
	s2->s = s;
	s2->next = NULL;
	return (s2);
}

int			backtrack(t_salle *s, t_salle *end, t_tube *tube, t_res **res)
{
	if (setouche(tube, s, end))
	{
		*res = edit_res(*res, end);
		*res = edit_res(*res, s);
		return (1);
	}
	else
	{
		while (tube->prev)
			tube = tube->prev;
		while (tube)
		{
			if (backtrack2(s, end, tube, res))
				return (1);
			if (tube->next)
				tube = tube->next;
			else
				break ;
		}
	}
	return (0);
}

int			backtrack2(t_salle *s, t_salle *end, t_tube *tube, t_res **res)
{
	if (s == tube->s1 && !(tube->s2->end)
			&& !(tube->s1->start || tube->s2->start))
	{
		tube->s2->end && (tube->s1 == end) ? 0 : (tube->s2->end = 1);
		tube->s1->end && (tube->s1 == end) ? 0 : (tube->s1->end = 1);
		if (backtrack(tube->s2, end, tube, res))
		{
			*res = edit_res(*res, s);
			return (1);
		}
	}
	else if (s == tube->s2 && !(tube->s1->end)
			&& !(tube->s1->start || tube->s2->start))
	{
		tube->s1->end ? 0 : (tube->s1->end = 1);
		if (backtrack(tube->s1, end, tube, res))
		{
			*res = edit_res(*res, s);
			return (1);
		}
	}
	return (0);
}

int			maxway(t_env *e)
{
	int start;
	int end;

	start = 0;
	end = 0;
	while ((e->tube)->prev)
		e->tube = (e->tube)->prev;
	while (e->tube)
	{
		(((e->tube)->s1)->start || ((e->tube)->s2)->start) ? start++ : 0;
		if (e->tube->next)
			(e->tube) = (e->tube)->next;
		else
			break ;
	}
	while (e->tube)
	{
		if (((e->tube)->s1)->end || ((e->tube)->s2)->end)
			end++;
		if (e->tube->prev)
			(e->tube) = (e->tube)->prev;
		else
			break ;
	}
	return (start < end ? start : end);
}
