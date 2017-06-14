/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 18:31:58 by rhakh             #+#    #+#             */
/*   Updated: 2017/04/01 20:00:41 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			validate(t_data *data)
{
	if (data->i == 0 || validate_data(data) == 0)
	{
		del_all_data(data);
		write(2, RED"Error: wrong data\n"EOC, 27);
		exit(1);
	}
	if (validate_farm(data) == 0)
	{
		del_all_data(data);
		write(2, RED"Error: wrong data\n"EOC, 27);
		exit(1);
	}
}

int				main(void)
{
	t_data		*data;
	t_lst_way	*best_ways;

	data = NULL;
	data = new_data(100);
	if ((data == NULL) &&
		(write(2, RED"Error: can't allocate memory\n"EOC, 38)))
		exit(1);
	read_data(&data);
	validate(data);
	print_data(data);
	ft_printf("\n");
	best_ways = get_best_way(data);
	walk_by_best_ways(data, best_ways);
	del_lst_way(&best_ways);
	del_all_data(data);
	return (0);
}
