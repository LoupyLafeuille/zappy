/*
** person_utils.h for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/include
** 
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
** 
** Started on  Thu Jun 23 20:03:10 2016 Loik Gaonach
** Last update Thu Jun 23 20:03:10 2016 Loik Gaonach
*/

#ifndef PERS_UTILS
# define PERS_UTILS

void		broadcast_to_person(t_server *srv, t_dllc *list, char *msg);
void		remove_person(t_dllc *list, t_person *person);
void		destroy_person(t_server *srv, int fd);

#endif /* !PERS_UTILS */
