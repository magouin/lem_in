/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 13:00:40 by magouin           #+#    #+#             */
/*   Updated: 2016/04/29 13:00:41 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_tube(t_tube *tube)
{
	while (tube->next)
		tube = tube->next;
	while (tube->prev)
	{
		tube = tube->prev;
		free(tube->next);
	}
	free(tube);
}

void	free_salle(t_salle *tube)
{
	while (tube->next)
		tube = tube->next;
	while (tube->prev)
	{
		tube = tube->prev;
		free((tube->next)->name);
		free(tube->next);
	}
	free(tube->name);
	free(tube);
}

void	print_solve4(t_res **res, t_env *e, int maxfourmie, int max)
{
	int y;
	int x;

	print_solve3(res, e, &y, max);
	while (y > 0)
	{
		x = -1;
		while (++x < max)
			if (res[x]->place == y)
			{
				while (res[x]->next)
					res[x] = res[x]->next;
				if (e->fourmie != 0)
				{
					res[x]->prev->fourmie = maxfourmie - e->fourmie + 1;
					ft_putstr("L");
					ft_putnbr(res[x]->prev->fourmie);
					ft_putstr("-");
					ft_putstr(res[x]->prev->s->name);
					y != 1 ? ft_putchar(' ') : 0;
					e->fourmie == 0 ? 0 : (e->fourmie)--;
				}
			}
		y--;
	}
}

void	print_solve5(t_res **res, int max, int *y, int x)
{
	while (x < max)
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
				(*y)++;
			}
			if (!(res[x]->next))
				break ;
			res[x] = res[x]->next;
		}
		x++;
	}
}

void	print_solve(t_res **res, t_env *e, int max)
{
	int y;
	int maxfourmie;

	print_solve1(res, 0, 0, &max);
	maxfourmie = e->fourmie;
	while (e->fourmie)
	{
		print_solve4(res, e, maxfourmie, max);
		ft_putchar('\n');
	}
	y = 1;
	while (y)
	{
		y = 0;
		print_solve5(res, max, &y, 0);
		y ? ft_putstr("\n") : 0;
	}
}
