/*
** see_cmd.c for zappy in /home/loupy/Rendu/PSU_2015_zappy/server/src
**
** Made by
** Login   <loupy@epitech.net>
**
** Started on  Tue Jun 14 16:24:18 2016
** Last update Sun Jun 26 21:50:26 2016 julien
*/

#include <stdio.h>
#include <math.h>
#include "server.h"
#include "dllc.h"
#include "tab_command.h"
#include "map.h"

static void	check_person(const t_map *map, int x, int y, char **buff)
{
  int		len;

  len = len_dllc(map->map[y][x].persons);
  if (len == 0)
    return ;
  while (len)
    {
      strcat(*buff, " joueur");
      --len;
    }
}

static void	write_message(const t_map *map,
			      int x, int y, char **buff, int *first)
{
  int		i;
  int		i2;

  i = 0;
  while (i < 7)
    {
      i2 = 0;
      while (i2 < map->map[y][x].items[i])
	{
	  if (*first != 0)
	    strcat(*buff, " ");
	  else
	    *first = 1;
	  strcat(*buff, get_obj(i));
	  ++i2;
	}
      ++i;
    }
  check_person(map, x, y, buff);
  strcat(*buff, ",");
}

static void	what_in_case(const t_pos *pos, const t_person *person,
			     const t_map *map, char **buff)
{
  static int	first = 0;
  float		x;
  float		y;

  x = 0;
  y = 0;
  x = cos(person->orientation * M_PI / 2) * (pos->x - pos->xc)
    - sin(person->orientation * M_PI / 2) * (pos->y - pos->yc) + pos->xc;
  y = sin(person->orientation * M_PI / 2) * (pos->x - pos->xc)
    + cos(person->orientation * M_PI / 2) * (pos->y - pos->yc) + pos->yc;
  if (x < 0)
    x = (int)(x + (map->x * (((int)((-x - 1) / map->x)) + 1))) % map->x;
  else if (x >= map->x)
    x = (int)x % map->x;
  if (y < 0)
    y = (int)(y + (map->y * ((((int)((-y - 1) / map->y)) + 1)))) % map->y;
  else if (y >= map->y)
    y = (int)y % map->y;
  write_message(map, x, y, buff, &first);
  first = 0;
}

static void	search_item(const t_server *srv,
			    const t_person *person, t_pos *pos, char **buff)
{
  int		i;
  int		j;
  int		lvl;
  int		tmp;

  i = 0;
  tmp = 0;
  lvl = person->lvl + 1;
  while (i < lvl)
    {
      j = 0;
      tmp = (2 * i + 1);
      while (j < tmp)
	{
	  pos->x = person->x;
	  pos->y = person->y;
	  pos->x -= i - j;
	  pos->y -= i;
	  what_in_case(pos, person, &(srv->map), buff);
	  ++j;
	}
      ++i;
    }
}

int		voir_cmd(t_server *srv, int fd)
{
  t_pos		pos;
  char		*buff;

  if ((buff = malloc(sizeof(char) * MAX_SIZE_INVENTAIRE)) == NULL)
    return (-1);
  memset(buff, 0 , 3);
  buff[0] = '{';
  pos.xc = (srv->sockets[fd].person)->x;
  pos.yc = (srv->sockets[fd].person)->y;
  search_item(srv, srv->sockets[fd].person, &pos, &buff);
  if ((buff = realloc(buff, strlen(buff) + 3)) == NULL)
    return (-1);
  buff[strlen(buff) - 1] = '}';
  strcat(buff, "\n");
  add_responce(srv->sockets[fd].write_buff, buff);
  free(buff);
  return (0);
}
