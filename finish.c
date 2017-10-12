/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 17:04:53 by magouin           #+#    #+#             */
/*   Updated: 2016/04/29 12:52:37 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_res(t_res **res)
{
	int x;

	x = 0;
	while (res[x] != NULL)
	{
		while ((res[x])->next)
			res[x] = (res[x])->next;
		while (res[x])
		{
			ft_putstr((res[x])->s->name);
			if (res[x]->prev)
			{
				ft_putchar('-');
				res[x] = res[x]->prev;
			}
			else
				break ;
		}
		ft_putchar('\n');
		x++;
	}
}

int		diff(t_salle *s, t_salle *p, t_tube *tube)
{
	while (tube->next)
		tube = tube->next;
	while (tube)
	{
		if ((tube->s1 == s && tube->s2 == p)
				|| (tube->s2 == s && tube->s1 == p))
			return (1);
		tube = tube->prev;
	}
	return (0);
}

void	size(t_res **res)
{
	int x;
	int nb;

	x = 0;
	while (res[x])
	{
		nb = 0;
		while (res[x]->next)
			res[x] = res[x]->next;
		while (res[x]->prev)
		{
			nb++;
			res[x] = res[x]->prev;
		}
		while (res[x]->next)
		{
			res[x]->size = nb;
			res[x] = res[x]->next;
		}
		res[x]->size = nb;
		x++;
	}
}

void	free_res(t_res **res)
{
	int x;

	x = 0;
	while (res[x])
	{
		while (res[x]->next)
			res[x] = res[x]->next;
		while (res[x]->prev)
		{
			res[x] = res[x]->prev;
			free(res[x]->next);
		}
		free(res[x]);
		x++;
	}
	free(res);
}

void	finish(t_res **res, t_env *e)
{
	int fourmie;
	int x;

	x = 0;
	fourmie = e->fourmie;
	ft_putstr("\n");
	while (res[x])
	{
		while (res[x]->prev)
			res[x] = res[x]->prev;
		if ((res[x]->s->end && res[x]->next->s->start)
				|| (res[x]->s->start && res[x]->next->s->end))
		{
			expres(res[x], e);
			return ;
		}
		x++;
	}
	size(res);
	print_solve(res, e, x);
	free_res(res);
}
