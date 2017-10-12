/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 14:13:14 by magouin           #+#    #+#             */
/*   Updated: 2016/04/29 13:43:54 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		tubes(char **line, t_env *e)
{
	char	**split;
	int		dim[2];

	while (*line[0] == '#')
		if (get_next_line(0, line) == 0)
			return (0);
	e->tube = edit_tb(e->tube);
	split = ft_strsplit(*line, '-');
	split[0] == NULL || split[1] == NULL
		|| split[2] != NULL ? ft_err(NULL, NULL, 8) : 0;
	while ((e->salle)->prev != NULL)
		e->salle = (e->salle)->prev;
	while (e->salle != NULL && ft_strcmp((e->salle)->name, split[0]))
		e->salle = e->salle->next;
	e->salle != NULL ? (e->tube)->s1 = e->salle : ft_err(NULL, NULL, 9);
	dim[0] = (e->salle)->x;
	dim[1] = (e->salle)->y;
	tubes2(e, split, dim);
	if (get_next_line(0, line) == 0)
		return (0);
	return (1);
}

void	salles(t_env *e, char **line)
{
	int		x;
	t_salle	*pt;

	x = comment(e, line);
	while (x)
		x = comment(e, line);
	while ((e->salle)->next)
		e->salle = (e->salle)->next;
	(e->salle)->prev ? ((e->salle)->prev)->next = NULL : 0;
	pt = (e->salle)->prev;
	free(e->salle);
	e->salle = pt;
	e->salle ? 0 : ft_err(NULL, NULL, 10);
	while ((e->salle)->prev)
		e->salle = (e->salle)->prev;
	check(e->salle);
}

void	main2(t_env e, int x, char *line, int poulet)
{
	salles(&e, &line);
	x = 1;
	while (x)
		x = tubes(&line, &e);
	poulet == 0 ? startend(&e) : 0;
	free_salle(e.salle);
	free_tube(e.tube);
	free(line);
}

int		main(int argc, char **argv)
{
	char	*line;
	t_env	e;
	int		x;
	int		poulet;

	argv = NULL;
	argc = 0;
	line = NULL;
	e.salle = NULL;
	e.tube = NULL;
	poulet = 0;
	e.size = 1;
	x = -1;
	if (get_next_line(0, &line) == 1)
		while (line[0] == '#' || !(ft_strcmp(line, "")))
			get_next_line(0, &line);
	while (line[++x] != '\0')
		line[x] > '9' || line[x] < '0' ? ft_err(NULL, NULL, 11) : 0;
	(line[0] != '\0' && ft_atoi(line) != 0) ?
		(e.fourmie = ft_atoi(line)) : ft_err(NULL, NULL, 12);
	main2(e, x, line, poulet);
	return (0);
}
