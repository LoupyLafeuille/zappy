/*
** game.c for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/src
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Wed Jun 15 19:02:59 2016 Loik Gaonach
** Last update Sun Jun 26 20:14:00 2016 julien
*/

#include <time.h>
#include <pthread.h>
#include "game.h"
#include "map.h"
#include "server.h"
#include "socket.h"
#include "team.h"
#include "time_utils.h"
#include "person_utils.h"

static t_dllc		*kill_person(t_server *srv, t_person *pers,
				     t_team *team, t_dllc *data)
{
  t_socket		*sock;

  team->available++;
  remove_person(srv->map.map[pers->y][pers->x].persons, pers);
  if ((sock = find_person_socket(srv->sockets, pers)))
    {
      dprintf(sock->fd, "mort\n");
      if (sock->person)
	{
	  delete_person(sock->person);
	  sock->person = NULL;
	}
      delete_socket(srv->sockets, sock->fd);
    }
  return (delete_elem_dllc(data));
}

int			loop_persons(t_server *srv, t_team *team)
{
  t_dllc		*tmp;
  t_person		*pers;
  int			nb;

  nb = 0;
  tmp = team->persons->nxt;
  while (tmp != team->persons)
    {
      pers = tmp->data;
      nb = (pers->lvl == MAX_LVL) ? nb + 1 : nb;
      if (diff_time_now(&pers->cycle) >= CYCLE_DELAY(srv->args->delai))
	{
	  if (pers->items[FOOD] - 1 <= 0)
	    tmp = kill_person(srv, pers, team, tmp);
	  else
	    {
	      pers->items[FOOD]--;
	      gettimeofday(&pers->cycle, NULL);
	      tmp = tmp->nxt;
	    }
	}
      else
	tmp = tmp->nxt;
    }
  return (nb);
}

int			game_run(t_server *srv)
{
  static time_t		start = 0;
  t_dllc		*tmp;

  if (start == 0)
    start = time(NULL);
  tmp = srv->team->nxt;
  while (tmp != srv->team)
    {
      if (tmp && loop_persons(srv, tmp->data) == NB_PLAYER_WIN)
	return (1);
      tmp = tmp->nxt;
    }
  if (difftime(time(NULL), start) >= (CYCLE / srv->args->delai) * 5)
    {
      add_food(&srv->map);
      start = time(NULL);
    }
  return (0);
}
