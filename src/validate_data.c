/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:00:55 by rhakh             #+#    #+#             */
/*   Updated: 2017/04/01 20:00:56 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			validate_room(t_data *data, int i)
{
	char	**split;
	int		len;

	len = 0;
	split = ft_strsplit(data->arr[i], ' ');
	while (split[len] != 0)
		len++;
	if (len != 3)
	{
		del_split(&split);
		return (0);
	}
	if (is_room(split[0]) == 0)
	{
		del_split(&split);
		return (0);
	}
	if (is_number(split[1]) == 0 || is_number(split[2]) == 0)
	{
		del_split(&split);
		return (0);
	}
	del_split(&split);
	return (1);
}

int			validate_rooms(t_data *data, int *i)
{
	char	**split;

	while (*i < data->i)
	{
		split = ft_strsplit(data->arr[*i], ' ');
		if (!ft_memcmp("##start", split[0], 8) ||
			!ft_memcmp("##end", split[0], 6))
		{
			(!ft_strcmp("##start", split[0])) ? (data->is_end = 1) : 0;
			(!ft_strcmp("##start", split[0])) ? 0 : (data->is_start = 1);
			del_split(&split);
			if ((++(*i)) && !validate_room(data, *i))
				return (0);
		}
		else if (del_split(&split) && !is_link(data->arr[*i])
					&& !is_comment(data->arr[*i]) && !validate_room(data, *i))
			return (0);
		if (del_split(&split) && is_link(data->arr[*i]))
			return (1);
		if (!is_comment(data->arr[*i]) && is_room(data->arr[*i]))
			data->rooms++;
		del_split(&split);
		(*i)++;
	}
	return (1);
}

int			validate_links(t_data *data, int *i)
{
	char	**split;
	int		len;

	while (*i < data->i)
	{
		split = ft_strsplit(data->arr[*i], '-');
		len = 0;
		while (split[len] != 0)
			len++;
		if ((!is_comment(data->arr[*i]))
			&& (len != 2 || !is_room(split[0]) || !is_room(split[1])))
		{
			del_split(&split);
			return (0);
		}
		if (!is_comment(data->arr[*i]) && !ft_strcmp(split[0], split[1]))
		{
			del_split(&split);
			return (0);
		}
		del_split(&split);
		(*i)++;
	}
	return (1);
}

int			validate_data(t_data *data)
{
	int		i;

	i = 1;
	if (several_se(data) || empty_line(data))
		return (0);
	if (!is_number(data->arr[0]))
		return (0);
	if (!validate_rooms(data, &i))
		return (0);
	if (i == data->i)
		return (0);
	if (!validate_links(data, &i))
		return (0);
	(data->is_end == 0 || data->is_start == 0) ? (i = 0) : 0;
	return ((i == data->i) ? 1 : 0);
}

int			is_room(char *str)
{
	if (str[0] == 'L' || str[0] == '#')
		return (0);
	return (1);
}
