/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 19:58:41 by rhakh             #+#    #+#             */
/*   Updated: 2017/04/01 19:58:44 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				exist_in_lst_ways(t_lst_way **best_ways, t_path *path)
{
	int			i;
	t_lst_way	*curr_way;

	curr_way = *best_ways;
	if (curr_way == NULL)
		return (0);
	while (curr_way != NULL)
	{
		i = 0;
		while (i < curr_way->way->sp_room + 1 && i < path->sp_room + 1)
		{
			if (ft_strcmp(curr_way->way->rooms[i], path->rooms[i]) != 0)
				break ;
			i++;
		}
		if ((i == curr_way->way->sp_room + 1) && (i == path->sp_room + 1))
			return (1);
		curr_way = curr_way->next_way;
	}
	return (0);
}

int				n_c_less(t_lst_way *best_ways, t_lst_way *min_ways)
{
	int			best_count;
	int			min_count;
	t_lst_way	*b_curr;
	t_lst_way	*m_curr;

	best_count = 0;
	min_count = 0;
	b_curr = best_ways;
	m_curr = min_ways;
	while (b_curr != NULL)
	{
		b_curr = b_curr->next_way;
		best_count++;
	}
	while (m_curr != NULL)
	{
		m_curr = m_curr->next_way;
		min_count++;
	}
	if (min_ways == NULL)
		return (1);
	if (best_count <= min_count)
		return (1);
	return (0);
}

void			backtracking(t_farm *farm, t_lst_way **best_ways,
				int *min_length, t_lst_way **min_ways)
{
	t_lst_way	*all_ways;
	t_lst_way	*curr_way;
	int			calc_curr_way;

	calc_curr_way = 0;
	all_ways = find_ways_lst(farm);
	curr_way = all_ways;
	while (curr_way != NULL)
	{
		if (exist_in_lst_ways(best_ways, curr_way->way) == 0)
		{
			push_new_back_way(best_ways, curr_way->way);
			calc_curr_way = calc_ways(farm, *best_ways);
			if ((*min_length > calc_curr_way) || ((*min_length == calc_curr_way) && n_c_less(*best_ways, *min_ways)))
			{
				*min_length = calc_curr_way;
				lst_way_copy(min_ways, best_ways);
			}
			walk_by_way(farm, curr_way->way);
			backtracking(farm, best_ways, min_length, min_ways);
			dewalk_by_way(farm, curr_way->way);
			del_last_lst_way(best_ways);
		}
		curr_way = curr_way->next_way;
	}
	del_lst_way(&all_ways);
}

t_lst_way		*get_best_way(t_data *data)
{
	t_lst_way	*best_ways;
	t_lst_way	*min_ways;
	t_farm		*farm;
	int			min_length;

	min_length = INT_MAX;
	farm = init_farm(data);
	farm->start->is_empty = 0;
	best_ways = NULL;
	min_ways = NULL;
	backtracking(farm, &best_ways, &min_length, &min_ways);
	del_all_farm(farm, data);
	del_lst_way(&best_ways);
	return (min_ways);
}
