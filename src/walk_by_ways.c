/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk_by_ways.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:01:03 by rhakh             #+#    #+#             */
/*   Updated: 2017/04/01 20:01:04 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				calc_ants_per_ways(t_farm *farm, t_lst_way *best_ways)
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
			if (steps - (curr_way->way->sp_room + 1) + 1 >= 1)
				curr_way->ants_at_way++;
			if (ants_at_out >= farm->ant_count)
				return (steps - 1);
			curr_way = curr_way->next_way;
		}
		steps++;
	}
	return (INT_MAX);
}

void			walk_by_way_final(t_farm *farm, t_lst_way *way, int *ant_num)
{
	t_room		*room1;
	t_room		*room2;
	int			i;

	i = way->way->sp_room;
	while (i >= 1)
	{
		room2 = find_room_by_name(farm, way->way->rooms[i]);
		room1 = find_room_by_name(farm, way->way->rooms[i - 1]);
		if (room2->is_end == 1 && room1->is_start == 1
			&& way->ants_at_way > 0 && ((*ant_num) < farm->ant_count))
			end_start(way, ant_num, room2);
		else if (room2->is_end == 1 && room1->is_empty == 0)
			end_room(room1, room2);
		else if (room2->is_empty == 1 && room1->is_empty == 0)
			room_room(room1, room2);
		else if (room1->is_start == 1 && room2->is_empty == 1
				&& way->ants_at_way > 0 && ((*ant_num) < farm->ant_count))
			start_room(way, ant_num, room2);
		i--;
	}
}

void			walk_by_best_ways(t_data *data, t_lst_way *ways)
{
	t_farm		*farm;
	t_lst_way	*curr;
	int			ant_num;

	if ((farm = init_farm(data)) == NULL)
		return ;
	curr = ways;
	calc_ants_per_ways(farm, ways);
	ant_num = 0;
	while (farm->end->ant_count < farm->ant_count)
	{
		if (curr == NULL && farm->end->ant_count < farm->ant_count)
		{
			curr = ways;
			ft_printf("\n");
		}
		if (farm->end->ant_count < farm->ant_count)
			walk_by_way_final(farm, curr, &ant_num);
		curr = curr->next_way;
	}
	if (farm->ant_count != 0)
		ft_printf("\n");
	del_all_farm(farm, data);
}
