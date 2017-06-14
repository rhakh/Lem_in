/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_farm_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 19:59:49 by rhakh             #+#    #+#             */
/*   Updated: 2017/04/01 19:59:50 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		init_room(t_room *room, char *str_room)
{
	int		i;

	i = 0;
	if ((room->name = ft_strnew(ft_strlen(str_room))) == NULL)
		return ;
	while (str_room[i] != '\0' && str_room[i] != ' ')
	{
		room->name[i] = str_room[i];
		room->ant_nbr = 0;
		room->ant_count = 0;
		i++;
	}
}

int			exist_way(t_room *room)
{
	int		i;
	t_room	*near;

	i = 0;
	if (room->is_end == 1)
		return (1);
	while (i < room->count_mates)
	{
		near = room->mate[i];
		if (near->is_empty == 1)
		{
			near->is_empty = 0;
			if (exist_way(near) == 1)
				return (1);
			if (near->is_start == 0)
				near->is_empty = 1;
		}
		i++;
	}
	return (0);
}

int			validate_farm(t_data *data)
{
	t_farm	*farm;

	farm = init_farm(data);
	if (farm == NULL)
		return (0);
	if (exist_way(farm->start) == 0)
	{
		del_all_farm(farm, data);
		return (0);
	}
	del_all_farm(farm, data);
	return (1);
}
