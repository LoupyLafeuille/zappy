/*
** map.c for zappy in /home/loupy/Rendu/PSU_2015_zappy/server/src
**
** Made by
** Login   <loupy@epitech.net>
**
** Started on  Wed Jun  8 18:02:01 2016
** Last update Sun Jun 26 18:05:56 2016 ClaireGizard
*/

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include "map.h"
#include "args.h"
#include "dllc.h"

void		add_food(t_map *map)
{
  int		x;
  int		y;

  y = 0;
  while (y < map->y)
    {
      x = 0;
      while (x < map->x)
	{
	  if (map->map[y][x].items[FOOD] == 0)
	    map->map[y][x].items[FOOD] += rand() % 2;
	  ++x;
	}
      ++y;
    }
}

void		delete_map(t_map *map)
{
  int		i;

  i = 0;
  while (i < map->x)
    {
      free(map->map[i]);
      ++i;
    }
  free(map->map);
}

static t_case	create_cell(void)
{
  t_case	cell;
  int		i;

  i = 0;
  cell.persons = create_dllc();
  while (i < 7)
    {
      cell.items[i] = rand() % 3;
      ++i;
    }
  cell.items[7] = 0;
  cell.incant = 0;
  return (cell);
}

t_map		*create_map(const t_param *param, t_map *map)
{
  int		x;
  int		y;

  x = 0;
  y = 0;
  map->x = param->x;
  map->y = param->y;
  map->press_x = -1;
  map->press_y = -1;
  srand(time(NULL));
  if ((map->map = malloc(sizeof(t_case *) * param->y)) == NULL)
    return (NULL);
  while (y < param->y)
    {
      if ((map->map[y] = malloc(sizeof(t_case) * param->x)) == NULL)
	return (NULL);
      x = 0;
      while (x < param->x)
	{
	  map->map[y][x] = create_cell();
	  ++x;
	}
      ++y;
    }
  return (map);
}
