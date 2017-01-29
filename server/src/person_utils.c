/*
** person_utils.c for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/src
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Wed Jun 15 01:56:16 2016 Loik Gaonach
** Last update Sun Jun 26 13:57:19 2016 Sylviane Tran
*/

#include <stdio.h>
#include <pthread.h>
#include "server.h"
#include "person.h"
#include "team.h"

void			remove_person(t_dllc *list, t_person *person)
{
  t_dllc		*tmp;

  tmp = list->nxt;
  while (tmp != list)
    {
      if (tmp->data == person)
	{
	  delete_elem_dllc(tmp);
	  return ;
	}
      tmp = tmp->nxt;
    }
}

void			broadcast_to_person(t_server *srv, t_dllc *list,
					    char *msg)
{
  t_dllc		*tmp;
  t_person		*pers;

  tmp = list->nxt;
  while (tmp != list)
    {
      pers = tmp->data;
      add_responce(srv->sockets[pers->fd].write_buff, msg);
      tmp = tmp->nxt;
    }
}

void			destroy_person(t_server *srv, int fd)
{
  t_person		*pers;
  t_team		*team;

  pers = srv->sockets[fd].person;
  if (pers && (team = find_team(srv->team, pers->team)))
    {
      team->available++;
      remove_person(team->persons, pers);
      remove_person(srv->map.map[pers->y][pers->x].persons, pers);
      delete_person(pers);
      srv->sockets[fd].person = NULL;
    }
  delete_socket(srv->sockets, fd);
}
