/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:01:09 by rhakh             #+#    #+#             */
/*   Updated: 2017/04/01 20:01:11 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			walk_by_way(t_farm *farm, t_path *path)
{
	int			i;
	int			j;

	i = 1;
	while (i < path->sp_room)
	{
		j = 0;
		while (j < farm->ri)
		{
			if ((farm->rooms[j].is_start == 0) &&
				(ft_strcmp(farm->rooms[j].name, path->rooms[i]) == 0))
				farm->rooms[j].is_empty = 0;
			j++;
		}
		i++;
	}
	farm->start->is_empty = 0;
	farm->end->is_empty = 1;
}

void			dewalk_by_way(t_farm *farm, t_path *path)
{
	int			i;
	int			j;

	i = 1;
	while (i < path->sp_room)
	{
		j = 0;
		while (j < farm->ri)
		{
			if ((farm->rooms[j].is_start == 0) &&
				(ft_strcmp(farm->rooms[j].name, path->rooms[i]) == 0))
				farm->rooms[j].is_empty = 1;
			j++;
		}
		i++;
	}
	farm->start->is_empty = 0;
	farm->end->is_empty = 1;
}

int				calc_ways(t_farm *farm, t_lst_way *best_ways)
{
	int			steps;
	t_lst_way	*curr_way;
	int			ants_at_out;

	steps = 1;
	ants_at_out = 0;
	while (ants_at_out < farm->ant_count)
	{
		ants_at_out = 0;
		curr_way = best_ways;
		while (curr_way != NULL)
		{
			ants_at_out += steps - (curr_way->way->sp_room + 1) + 1;
			if (ants_at_out >= farm->ant_count)
				return (steps - 1);
			curr_way = curr_way->next_way;
		}
		steps++;
	}
	return (INT_MAX);
}

void			lst_way_copy(t_lst_way **dst, t_lst_way **src)
{
	t_lst_way	*curr;

	curr = *src;
	del_lst_way(dst);
	while (curr != NULL)
	{
		push_new_back_way(dst, curr->way);
		curr = curr->next_way;
	}
}
