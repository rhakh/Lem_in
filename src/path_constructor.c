/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_constructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:00:47 by rhakh             #+#    #+#             */
/*   Updated: 2017/04/01 20:00:49 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		del_path(t_path **path)
{
	int		i;

	i = 0;
	if (path != NULL && *path != NULL)
	{
		while (i <= (*path)->sp_room)
		{
			if ((*path)->rooms[i] != NULL)
				free((*path)->rooms[i]);
			(*path)->rooms[i] = NULL;
			i++;
		}
		free((*path)->rooms);
		(*path)->rooms = NULL;
		free((*path));
		*path = NULL;
	}
}

t_path		*new_path(int room_count)
{
	t_path	*way;

	if ((way = (t_path *)malloc(sizeof(t_path))) != NULL)
		if ((way->rooms = (char **)malloc(sizeof(char *) * room_count)) == NULL)
			return (NULL);
	ft_bzero(way->rooms, sizeof(char *) * room_count);
	way->length = room_count;
	way->sp_room = -1;
	return (way);
}

void		add_path(t_farm *farm, t_path **path, char *str)
{
	if (path != NULL && *path == NULL)
	{
		*path = new_path(farm->ri);
		(*path)->sp_room++;
		(*path)->rooms[(*path)->sp_room] = ft_strdup(str);
	}
	else if (path != NULL)
	{
		(*path)->sp_room++;
		(*path)->rooms[(*path)->sp_room] = ft_strdup(str);
	}
}

void		del_last_path(t_path **path)
{
	if (path != NULL && *path != NULL)
	{
		if ((*path)->sp_room >= 0)
		{
			if ((*path)->rooms[(*path)->sp_room] != NULL)
				free((*path)->rooms[(*path)->sp_room]);
			(*path)->rooms[(*path)->sp_room] = NULL;
			(*path)->sp_room--;
		}
	}
}
