/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_turn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 19:58:49 by rhakh             #+#    #+#             */
/*   Updated: 2017/04/01 19:58:50 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			end_start(t_lst_way *way, int *ant_num, t_room *room2)
{
	way->ants_at_way--;
	(*ant_num)++;
	room2->ant_count++;
	ft_printf("L%d-%s ", (*ant_num), room2->name);
}

void			end_room(t_room *room1, t_room *room2)
{
	room2->ant_count++;
	room1->is_empty = 1;
	ft_printf("L%d-%s ", room1->ant_nbr, room2->name);
	room1->ant_nbr = 0;
}

void			room_room(t_room *room1, t_room *room2)
{
	room2->ant_nbr = room1->ant_nbr;
	room1->ant_nbr = 0;
	room1->is_empty = 1;
	room2->is_empty = 0;
	ft_printf("L%d-%s ", room2->ant_nbr, room2->name);
}

void			start_room(t_lst_way *way, int *ant_num, t_room *room2)
{
	way->ants_at_way--;
	(*ant_num)++;
	room2->ant_nbr = (*ant_num);
	room2->is_empty = 0;
	ft_printf("L%d-%s ", room2->ant_nbr, room2->name);
}
