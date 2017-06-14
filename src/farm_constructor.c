/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farm_constructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 19:59:12 by rhakh             #+#    #+#             */
/*   Updated: 2017/04/01 19:59:14 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			new_farm_help(t_data *data, t_farm *farm)
{
	int		i;

	i = 0;
	while (i < data->rooms)
	{
		farm->rooms[i].count_mates = 0;
		farm->rooms[i].is_end = 0;
		farm->rooms[i].is_start = 0;
		farm->rooms[i].is_empty = 1;
		farm->rooms[i].name = 0;
		farm->rooms[i].weight = 0;
		if ((farm->rooms[i].mate = (t_room **)
				malloc(sizeof(t_room *) * data->rooms)) == NULL)
			return (0);
		ft_bzero(farm->rooms[i].mate, sizeof(t_room *) * data->rooms);
		i++;
	}
	return (1);
}

t_farm		*new_farm(t_data *data)
{
	t_farm	*farm;

	farm = NULL;
	if ((farm = (t_farm *)malloc(sizeof(t_farm))) != NULL)
		if ((farm->rooms = (t_room *)
				malloc(sizeof(t_room) * data->rooms + 1)) == NULL)
			return (NULL);
	ft_bzero(farm->rooms, sizeof(t_room) * data->rooms + 1);
	if (new_farm_help(data, farm) == 0)
		return (NULL);
	farm->ant_count = ft_atoi(data->arr[0]);
	farm->ri = 0;
	farm->link_count = 0;
	return (farm);
}

void		del_all_farm(t_farm *farm, t_data *data)
{
	int		i;

	i = 0;
	if (farm != NULL)
	{
		while (i < data->rooms)
		{
			if (farm->rooms[i].mate != NULL)
				free(farm->rooms[i].mate);
			if (farm->rooms[i].name != NULL)
				free(farm->rooms[i].name);
			i++;
		}
		if (farm->rooms != NULL)
			free(farm->rooms);
		free(farm);
	}
}
