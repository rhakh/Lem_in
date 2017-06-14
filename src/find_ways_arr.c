/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 19:59:29 by rhakh             #+#    #+#             */
/*   Updated: 2017/04/01 19:59:31 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			all_ways(t_farm *farm, t_room *room,
				t_lst_way **head, t_path *path)
{
	int			i;
	t_room		*near;

	i = 0;
	if (room->is_end == 1)
	{
		push_new_back_way(head, path);
		return ;
	}
	while (i < room->count_mates)
	{
		near = room->mate[i];
		if (near->is_empty == 1)
		{
			near->is_empty = 0;
			add_path(farm, &path, near->name);
			all_ways(farm, near, head, path);
			del_last_path(&path);
			if (near->is_start == 0)
				near->is_empty = 1;
		}
		i++;
	}
}

t_lst_way		*find_ways_lst(t_farm *farm)
{
	t_lst_way	*head;
	t_path		*path;

	head = NULL;
	path = NULL;
	add_path(farm, &path, farm->start->name);
	farm->start->is_empty = 0;
	all_ways(farm, farm->start, &head, path);
	del_path(&path);
	return (head);
}
