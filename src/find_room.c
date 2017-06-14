/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 19:59:20 by rhakh             #+#    #+#             */
/*   Updated: 2017/04/01 19:59:22 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room		*find_mate_by_name(t_room *room, char *name)
{
	int		i;

	i = 0;
	if (room == NULL)
		return (NULL);
	while (i < room->count_mates)
	{
		if (!ft_strcmp(name, room->mate[i]->name))
			return (room->mate[i]);
		i++;
	}
	return (NULL);
}

t_room		*find_room_by_name(t_farm *farm, char *name)
{
	int		i;

	i = 0;
	while (i < farm->ri)
	{
		if (ft_strcmp(name, farm->rooms[i].name) == 0)
			return (&(farm->rooms[i]));
		i++;
	}
	return (NULL);
}

int			several_se(t_data *data)
{
	int		s;
	int		e;
	int		i;

	i = 0;
	s = 0;
	e = 0;
	while (i < data->i)
	{
		if (!ft_memcmp("##start", data->arr[i], 8))
			s++;
		if (!ft_memcmp("##end", data->arr[i], 6))
			e++;
		i++;
	}
	if (s != 1 || e != 1)
		return (1);
	return (0);
}

int			empty_line(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->i)
	{
		if (ft_strlen(data->arr[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
