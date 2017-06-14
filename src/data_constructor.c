/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_constructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 19:58:57 by rhakh             #+#    #+#             */
/*   Updated: 2017/04/01 19:58:59 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		realloc_data(t_data **src)
{
	t_data	*dst;
	int		i;

	i = 0;
	dst = new_data((*src)->size * 2);
	while (i < (*src)->i)
	{
		dst->arr[i] = (*src)->arr[i];
		i++;
	}
	dst->i = (*src)->i;
	dst->rooms = (*src)->rooms;
	dst->size = (*src)->size * 2;
	del_data(*src);
	*src = dst;
}

void		del_all_data(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->i)
	{
		free(data->arr[i]);
		i++;
	}
	del_data(data);
}

void		del_data(t_data *data)
{
	data->i = 0;
	data->size = 0;
	free(data->arr);
	free(data);
}

t_data		*new_data(size_t size)
{
	t_data	*data;

	if ((data = (t_data *)malloc(sizeof(t_data))) == NULL)
		return (NULL);
	if ((data->arr = (char **)malloc(sizeof(char *) * size)) == NULL)
	{
		free(data);
		return (NULL);
	}
	ft_bzero(data->arr, sizeof(char *) * size);
	data->size = size;
	data->i = 0;
	data->rooms = 0;
	data->is_start = 0;
	data->is_end = 0;
	return (data);
}

void		print_data(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->i)
	{
		ft_printf("%s\n", data->arr[i]);
		i++;
	}
}
