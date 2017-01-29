/*
** move.c for zappy in /home/loupy/Rendu/PSU_2015_zappy/server/src
**
** Made by
** Login   <loupy@epitech.net>
**
** Started on  Tue Jun 14 16:29:21 2016
** Last update Sun Jun 26 21:51:27 2016 julien
*/

#include <pthread.h>
#include "server.h"
#include "dllc.h"
#include "tab_command.h"
#include "person_utils.h"

void		move_up(const t_map *map, t_person *pers)
{
  if (pers->y == 0)
    {
      put_bot_dllc(map->map[map->y - 1][pers->x].persons, pers);
      pers->y = map->y - 1;
    }
  else
    {
      put_bot_dllc(map->map[pers->y - 1][pers->x].persons, pers);
      pers->y -= 1;
    }
}

void		move_down(const t_map *map, t_person *pers)
{
  if (pers->y == map->y - 1)
    {
      put_bot_dllc(map->map[0][pers->x].persons, pers);
      pers->y = 0;
    }
  else
    {
      put_bot_dllc(map->map[pers->y + 1][pers->x].persons, pers);
      pers->y = pers->y + 1;
    }
}

void		move_left(const t_map *map, t_person *pers)
{
  if (pers->x == 0)
    {
      put_bot_dllc(map->map[pers->y][map->x - 1].persons, pers);
      pers->x = map->x - 1;
    }
  else
    {
      put_bot_dllc(map->map[pers->y][pers->x - 1].persons, pers);
      pers->x = pers->x - 1;
    }
}

void		move_right(const t_map *map, t_person *pers)
{
  if (pers->x == map->x - 1)
    {
      put_bot_dllc(map->map[pers->y][0].persons, pers);
      pers->x = 0;
    }
  else
    {
      put_bot_dllc(map->map[pers->y][pers->x + 1].persons, pers);
      pers->x = pers->x + 1;
    }
}

int		avance_cmd(t_server *srv, int fd)
{
  t_person	*person;
  int		i;

  i = 0;
  person = srv->sockets[fd].person;
  remove_person(srv->map.map[person->y][person->x].persons, person);
  while (g_move[i].fct != NULL)
    {
      if (g_move[i].dir == person->orientation)
	g_move[i].fct(&(srv->map), person);
      ++i;
    }
  add_responce(srv->sockets[fd].write_buff, "ok\n");
  return (0);
}
