/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 19:59:59 by rhakh             #+#    #+#             */
/*   Updated: 2017/04/01 20:00:01 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../new_libft/srcs/libft.h"

typedef struct			s_data
{
	char				**arr;
	int					i;
	size_t				size;
	int					is_start;
	int					is_end;
	int					rooms;
}						t_data;

typedef struct			s_room
{
	char				*name;
	int					is_empty;
	int					is_start;
	int					is_end;
	int					ant_nbr;
	int					ant_count;
	int					weight;
	int					count_mates;
	struct s_room		**mate;
}						t_room;

typedef struct			s_farm
{
	int					ant_count;
	t_room				*rooms;
	int					ri;
	int					link_count;
	t_room				*start;
	t_room				*end;
}						t_farm;

typedef struct			s_path
{
	int					sp_room;
	int					length;
	char				**rooms;
}						t_path;

typedef struct			s_lst_way
{
	t_path				*way;
	int					ants_at_way;
	int					curr_ant_num;
	struct s_lst_way	*next_way;
}						t_lst_way;

/*
** algo.c
*/
int						exist_in_lst_ways(t_lst_way **best_ways, t_path *path);
int						n_c_less(t_lst_way *best_ways, t_lst_way *min_ways);
void					backtracking(t_farm *farm, t_lst_way **best_ways,
						int *min_length, t_lst_way **min_ways);
t_lst_way				*get_best_way(t_data *data);

/*
** calc_turn.c
*/
void					end_start(t_lst_way *way, int *ant_num, t_room *room2);
void					end_room(t_room *room1, t_room *room2);
void					room_room(t_room *room1, t_room *room2);
void					start_room(t_lst_way *way, int *ant_num, t_room *room2);

/*
** data_constructor.c
*/
void					realloc_data(t_data **src);
void					del_all_data(t_data *data);
void					del_data(t_data *data);
t_data					*new_data(size_t size);
void					print_data(t_data *data);

/*
** data_func.c
*/
int						is_number(char *str);
void					read_data(t_data **data);
int						is_link(char *str);
int						is_comment(char *str);
int						del_split(char ***split);

/*
** farm_constructor.c
*/
int						new_farm_help(t_data *data, t_farm *farm);
t_farm					*new_farm(t_data *data);
void					del_all_farm(t_farm *farm, t_data *data);

/*
** find_room.c
*/
t_room					*find_mate_by_name(t_room *room, char *name);
t_room					*find_room_by_name(t_farm *farm, char *name);
int						several_se(t_data *data);
int						empty_line(t_data *data);

/*
** find_ways_arr.c
*/
void					all_ways(t_farm *farm, t_room *room,
						t_lst_way **head, t_path *path);
t_lst_way				*find_ways_lst(t_farm *farm);

/*
** init_farm.c
*/
int						find_nodes(t_farm *farm, char *str1, char *str2);
int						make_link(t_farm *farm, char *str);
int						init_links(int i, t_farm *farm, t_data *data);
void					init_rooms(t_data *data, int *i, t_farm *farm);
t_farm					*init_farm(t_data *data);

/*
** init_farm_help.c
*/
void					init_room(t_room *room, char *str_room);
int						exist_way(t_room *room);
int						validate_farm(t_data *data);

/*
** lst_way.c
*/
t_lst_way				*new_lst_way_s(t_path *src);
void					del_lst_way(t_lst_way **way);
void					del_last_lst_way(t_lst_way **way);
void					push_new_back_way(t_lst_way **head, t_path *src);

/*
** main.c
*/
void					validate(t_data *data);

/*
** path_constructor.c
*/
void					del_path(t_path **path);
t_path					*new_path(int room_count);
void					add_path(t_farm *farm, t_path **path, char *str);
void					del_last_path(t_path **path);

/*
** validate_data.c
*/
int						validate_room(t_data *data, int i);
int						validate_rooms(t_data *data, int *i);
int						validate_links(t_data *data, int *i);
int						validate_data(t_data *data);
int						is_room(char *str);

/*
** walk_by_ways.c
*/
int						calc_ants_per_ways(t_farm *farm, t_lst_way *best_ways);
void					walk_by_way_final(t_farm *farm, t_lst_way *way,
						int *ant_num);
void					walk_by_best_ways(t_data *data, t_lst_way *ways);

/*
** way_func.c
*/
void					walk_by_way(t_farm *farm, t_path *path);
void					dewalk_by_way(t_farm *farm, t_path *path);
int						calc_ways(t_farm *farm, t_lst_way *best_ways);
void					lst_way_copy(t_lst_way **dst, t_lst_way **src);

void					print_way_lst(t_lst_way *ways);

#endif
