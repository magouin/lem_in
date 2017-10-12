/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 13:00:48 by magouin           #+#    #+#             */
/*   Updated: 2016/04/29 13:35:28 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	expres(t_res *res, t_env *e)
{
	int x;

	x = 1;
	while (x < e->fourmie + 1)
	{
		ft_putstr("L");
		ft_putnbr(x);
		ft_putstr("-");
		ft_putstr(res->next->s->name);
		x == e->fourmie ? ft_putstr("\n") : ft_putstr(" ");
		x++;
	}
}

int		sort(int **min, int max)
{
	int x;

	x = 1;
	while (x < max)
	{
		if ((min[x][1] < min[x - 1][1] && min[x][0] > min[x - 1][0])
				|| (min[x][1] > min[x - 1][1] && min[x][0] < min[x - 1][0]))
			return (1);
		x++;
	}
	return (0);
}

void	print_solve1(t_res **res, int x, int y, int *max)
{
	int r;
	int min;

	while (res[x]->end)
		x++;
	min = res[x]->size;
	while (y < *max)
	{
		x = 0;
		while (res[x]->end)
			x++;
		min = res[x]->size;
		x = -1;
		while (++x < *max)
		{
			while (res[x]->next)
				res[x] = res[x]->next;
			res[x]->size <= min && res[x]->end == 0 ? min = res[x]->size : 0;
			res[x]->size <= min && res[x]->end == 0 ? r = x : 0;
		}
		res[r]->end = 1;
		res[r]->place = ++y;
	}
}

void	print_solve2(t_res **res, int max, int *y, t_env *e)
{
	int min;
	int r;
	int x;

	x = -1;
	*y = 1;
	min = 0;
	r = 0;
	while (++x < max)
	{
		res[x]->place == *y ? r = res[x]->size : 0;
		res[x]->place == *y + 1 ? min = res[x]->size : 0;
	}
	while (((e->fourmie / *y) + r - 1 > ((e->fourmie
						/ (*y + 1)) + (min) - 1)) && *y < max)
	{
		(*y)++;
		x = 0;
		while (x < max)
		{
			res[x]->place == *y ? r = res[x]->size : 0;
			res[x]->place == *y + 1 ? min = res[x]->size : 0;
			x++;
		}
	}
}

void	print_solve3(t_res **res, t_env *e, int *y, int max)
{
	int x;

	print_solve2(res, max, y, e);
	x = -1;
	while (++x < max)
	{
		while (res[x]->prev)
			res[x] = res[x]->prev;
		while (res[x])
		{
			if (res[x]->fourmie && res[x]->prev)
			{
				ft_putstr("L");
				ft_putnbr(res[x]->fourmie);
				ft_putstr("-");
				ft_putstr(res[x]->prev->s->name);
				ft_putstr(" ");
				res[x]->prev->fourmie = res[x]->fourmie;
				res[x]->fourmie = 0;
			}
			if (!(res[x]->next))
				break ;
			res[x] = res[x]->next;
		}
	}
}
