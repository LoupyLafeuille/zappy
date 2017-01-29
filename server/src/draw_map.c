/*
** draw_map.c for  in /home/tran_9/Cours/B4/SysT/zappy/PSU_2015_zappy/server/src
**
** Made by Sylviane Tran
** Login   <tran_9@epitech.net>
**
** Started on  Thu Jun  9 12:37:52 2016 Sylviane Tran
** Last update Sun Jun 26 00:32:34 2016 Sylviane Tran
*/

#include <pthread.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include "map.h"

static void		draw_item(SDL_Surface *win, const t_case map,
				  SDL_Rect pos, SDL_Surface **stones)
{
  int			i;

  i = 0;
  while (i < 8)
    {
      if (map.items[i] > 0)
	SDL_BlitSurface(stones[i], NULL, win, &pos);
      i++;
    }
}

static void		draw_persons(SDL_Surface *win, t_case map,
				     SDL_Rect pos, SDL_Surface ***persons)
{
  t_person		*person;

  if (len_dllc(map.persons))
    {
      person = (t_person *)map.persons->nxt->data;
      if ((person->lvl - 1) >= 0)
	SDL_BlitSurface(persons[person->lvl - 1][person->orientation], NULL,
			win, &pos);
    }
}

static void		stone_sound(t_map *map, SDL_Surface *win)
{
  SDL_Rect		pos;

  pos.x = 0;
  pos.y = 0;
  SDL_FillRect(map->items.bg, NULL,
	       SDL_MapRGB(win->format, 175, 202, 151));
  SDL_BlitSurface(map->items.bg, NULL, win, &pos);
 if (map->take_stone)
    {
      map->take_stone = 0;
      Mix_PlayMusic(map->items.stone, 1);
    }
}

void			update(SDL_Surface *win, t_map *map)
{
  int			y;
  int			x;
  SDL_Rect		pos;

  y = -1 + (((map->pos.y < 0) ? -map->pos.y : map->pos.y) / SIZEBLOC);
  stone_sound(map, win);
  while (++y < map->y)
    {
      x = -1 + (((map->pos.x < 0) ? -map->pos.x : map->pos.x) / SIZEBLOC);
      pos.y = y * SIZEBLOC + map->pos.y;
      while (++x < map->x)
	{
	  pos.x = x * SIZEBLOC + map->pos.x;
	  SDL_BlitSurface(map->items.grass, NULL, win, &pos);
	  draw_item(win, map->map[y][x], pos, map->items.stones_map);
	  if (map->map[y][x].incant == 0)
	    draw_persons(win, map->map[y][x], pos, map->items.persons);
	  else
	    {
	      Mix_PlayMusic(map->items.incant, 1);
	      SDL_BlitSurface(map->items.grass_ele, NULL, win, &pos);
	    }
	}
    }
}
