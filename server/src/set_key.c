/*
** set_key.c for  in /home/tran_9/Cours/B4/SysT/zappy/PSU_2015_zappy/server
**
** Made by Sylviane Tran
** Login   <tran_9@epitech.net>
**
** Started on  Thu Jun 23 15:35:58 2016 Sylviane Tran
** Last update Sat Jun 25 14:49:09 2016 Sylviane Tran
*/

#include <stdio.h>
#include "map.h"

void			init_struct(t_map *map)
{
  map->items.grass = NULL;
  map->items.grass_ele = NULL;
  map->items.bg = NULL;
  map->items.stones_map = NULL;
  map->items.stones_idx = NULL;
  map->items.persons = NULL;
  map->items.font.font = NULL;
  map->items.stone = NULL;
  map->items.incant = NULL;
  map->items.select = NULL;
  map->take_stone = 0;
  map->pos.x = 0;
  map->pos.y = 0;
}

void			set_key(t_map *map, int x, int y)
{
  if ((x / SIZEBLOC) < map->x)
    {
      map->press_x = (x / SIZEBLOC) % map->x;
      map->press_y = (y / SIZEBLOC) % map->y;
    }
  else
    {
      map->press_x = -1;
      map->press_y = -1;
    }
}
