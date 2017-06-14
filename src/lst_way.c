/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_way.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:00:11 by rhakh             #+#    #+#             */
/*   Updated: 2017/04/01 20:00:13 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lst_way		*new_lst_way_s(t_path *src)
{
	t_lst_way	*new;
	t_path		*way;
	int			i;

	i = 0;
	if ((new = (t_lst_way *)malloc(sizeof(t_lst_way))) == NULL)
		return (NULL);
	if ((new->way = new_path(src->length)) == NULL)
	{
		free(new);
		return (NULL);
	}
	way = new->way;
	while (i <= src->sp_room)
	{
		way->rooms[i] = ft_strdup(src->rooms[i]);
		i++;
	}
	way->sp_room = src->sp_room;
	way->length = src->length;
	new->next_way = NULL;
	return (new);
}

void			del_lst_way(t_lst_way **way)
{
	while (*way != NULL)
		del_last_lst_way(way);
}

void			del_last_lst_way(t_lst_way **way)
{
	t_lst_way	**curr;

	if (way != NULL && *way != NULL)
	{
		curr = way;
		while ((*curr)->next_way != NULL)
			curr = &(*curr)->next_way;
		del_path(&(*curr)->way);
		free((*curr));
		*curr = NULL;
	}
}

void			push_new_back_way(t_lst_way **head, t_path *src)
{
	t_lst_way	*curr;

	if (!*head)
	{
		*head = new_lst_way_s(src);
		(*head)->ants_at_way = 0;
		(*head)->curr_ant_num = 0;
	}
	else
	{
		curr = *head;
		while (curr->next_way)
			curr = curr->next_way;
		curr->next_way = new_lst_way_s(src);
		curr->ants_at_way = 0;
		curr->curr_ant_num = 0;
	}
}

void			print_way_lst(t_lst_way *ways)
{
	t_lst_way	*curr;
	int			i;
	int			col;

	curr = ways;
	col = 1;
	while (curr)
	{
		i = 0;
		ft_printf("way[%d]: ", col);
		while (i <= curr->way->sp_room)
		{
			ft_printf("%s -> ", curr->way->rooms[i]);
			i++;
		}
		ft_printf("\n");
		curr = curr->next_way;
		col++;
	}
}