/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 19:59:05 by rhakh             #+#    #+#             */
/*   Updated: 2017/04/01 19:59:07 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			is_number(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] != 0)
	{
		if (str[i] != 0 && !ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void		read_data(t_data **data)
{
	char	*tmp;

	while (get_next_line(0, &tmp) > 0)
	{
		if ((*data)->i + 1 >= (int)(*data)->size)
			realloc_data(data);
		(*data)->arr[(*data)->i] = tmp;
		(*data)->i++;
	}
	if (ft_strcmp(tmp, "") == 0)
		free(tmp);
}

int			is_link(char *str)
{
	int		i;

	i = 0;
	if (str[i] == 'L' || str[i] == '#')
		return (0);
	while (str[i] != 0 && str[i] != '-')
		i++;
	if (str[i] == '-')
		i++;
	else
		return (0);
	if (str[i] == 'L' || str[i] == '#')
		return (0);
	while (str[i] != 0)
		i++;
	return (1);
}

int			is_comment(char *str)
{
	if (str[0] == '#' && str[1] == '#')
		return (1);
	if (str[0] == '#' && str[1] != '#')
		return (1);
	return (0);
}

int			del_split(char ***split)
{
	int		i;

	i = 0;
	if (*split != NULL)
	{
		while ((*split)[i] != NULL)
		{
			free((*split)[i]);
			(*split)[i] = NULL;
			i++;
		}
		free(*split);
		(*split) = NULL;
		split = NULL;
	}
	return (1);
}
