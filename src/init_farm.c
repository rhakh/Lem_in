/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_farm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 19:59:42 by rhakh             #+#    #+#             */
/*   Updated: 2017/04/01 19:59:44 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			find_nodes(t_farm *farm, char *str1, char *str2)
{
	t_room	*room1;
	t_room	*room2;
	t_room	*mate1;
	t_room	*mate2;

	room1 = NULL;
	room2 = NULL;
	room1 = find_room_by_name(farm, str1);
	room2 = find_room_by_name(farm, str2);
	mate1 = find_mate_by_name(room1, str2);
	mate2 = find_mate_by_name(room2, str1);
	if (mate1 && mate2)
		return (1);
	if (room1 && room2)
	{
		room1->mate[room1->count_mates] = room2;
		room1->count_mates++;
		room2->mate[room2->count_mates] = room1;
		room2->count_mates++;
	}
	else
		return (0);
	return (1);
}

int			make_link(t_farm *farm, char *str)
{
	char	*str1;
	char	*str2;
	int		i;

	i = -1;
	if ((str1 = ft_strnew(ft_strlen(str))) == NULL ||
		(str2 = ft_strnew(ft_strlen(str))) == NULL)
		return (0);
	while (*str != '\0' && *str != '-' && (++i) >= 0)
	{
		str1[i] = *str;
		str++;
	}
	str++;
	i = -1;
	while (*str != '\0' && *str != '-' && (++i) >= 0)
	{
		str2[i] = *str;
		str++;
	}
	i = find_nodes(farm, str1, str2);
	free(str1);
	free(str2);
	return (i);
}

int			init_links(int i, t_farm *farm, t_data *data)
{
	while (i < data->i)
	{
		if (is_link(data->arr[i]) && !is_comment(data->arr[i]))
			if (make_link(farm, data->arr[i]) == 0)
				return (0);
		i++;
	}
	return (1);
}

void		init_rooms(t_data *data, int *i, t_farm *farm)
{
	char	**split;

	while (farm->ri < data->rooms)
	{
		split = ft_strsplit(data->arr[*i], ' ');
		if (!ft_strcmp("##start", split[0]) || !ft_strcmp("##end", split[0]))
		{
			(*i)++;
			init_room(farm->rooms + farm->ri, data->arr[*i]);
			(!ft_strcmp("##end", data->arr[*i - 1]))
			? (farm->rooms[farm->ri].is_end = 1)
			: (farm->rooms[farm->ri].is_start = 1);
			(farm->rooms[farm->ri].is_start)
			? (farm->rooms[farm->ri].ant_nbr = farm->ant_count) : 0;
			(!ft_strcmp("##end", data->arr[*i - 1]))
			? (farm->end = farm->rooms + farm->ri) : 0;
			(!ft_strcmp("##start", data->arr[*i - 1]))
			? (farm->start = farm->rooms + farm->ri) : 0;
		}
		else if (is_room(data->arr[*i]) && !is_comment(data->arr[*i]))
			init_room(farm->rooms + farm->ri, data->arr[*i]);
		(is_room(data->arr[*i]) && !is_comment(data->arr[*i]))
		? (farm->ri++) : 0;
		((*i)++ >= 0) ? (del_split(&split)) : 0;
	}
}

t_farm		*init_farm(t_data *data)
{
	t_farm	*farm;
	int		i;

	i = 1;
	if ((farm = new_farm(data)) == NULL)
		return (NULL);
	farm->ant_count = ft_atoi(data->arr[0]);
	init_rooms(data, &i, farm);
	if (init_links(i, farm, data) == 0)
	{
		del_all_farm(farm, data);
		return (NULL);
	}
	return (farm);
}
