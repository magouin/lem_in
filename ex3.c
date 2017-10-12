/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 13:00:34 by magouin           #+#    #+#             */
/*   Updated: 2016/04/29 13:00:36 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_salle	*edit_sl(t_salle *sl)
{
	t_salle *s2;

	s2 = malloc(sizeof(t_salle));
	if (sl)
		sl->next = s2;
	s2->prev = sl;
	s2->next = NULL;
	s2->start = 0;
	s2->end = 0;
	return (s2);
}

t_tube	*edit_tb(t_tube *sl)
{
	t_tube *s2;

	s2 = malloc(sizeof(t_tube));
	if (sl)
		sl->next = s2;
	s2->prev = sl;
	s2->next = NULL;
	return (s2);
}

void	ft_err(t_env *e, int *i, int t)
{
	t = 0;
	if (i == NULL)
	{
		ft_putstr("ERROR\n");
		exit(EXIT_FAILURE);
	}
	(*i)++;
	startend(e);
}

void	integer(char *split)
{
	int		x;
	long	f;
	int		len;
	long	pow;

	len = 0;
	x = -1;
	f = 0;
	split[0] == '-' ? x++ : 0;
	while (split[++x] != '\0')
	{
		split[x] > '9' || split[x] < '0' ? ft_err(NULL, NULL, 1) : 0;
		len = ft_strlen(split) - x;
		pow = 1;
		while (--len)
			pow *= 10;
		f += pow * (split[x] - 48);
	}
	split[0] == '-' ? f *= -1 : 0;
	f < (long)(-2147483648) || f > (long)(2147483647) ?
		ft_err(NULL, NULL, 2) : 0;
}

void	print_salle(t_salle *sl)
{
	while (sl)
	{
		ft_putstr("salle ");
		ft_putendl(sl->name);
		ft_putstr("x = ");
		ft_putnbr(sl->x);
		ft_putendl("");
		ft_putstr("y = ");
		ft_putnbr(sl->y);
		ft_putendl("");
		if (sl->start)
			ft_printf("start\n\n");
		else if (sl->end)
			ft_printf("end\n\n");
		else
			ft_putchar('\n');
		sl = sl->next;
	}
}
