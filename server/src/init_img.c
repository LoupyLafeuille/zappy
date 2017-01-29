/*
** init_img.c for  in /home/tran_9/Cours/B4/SysT/zappy/PSU_2015_zappy/server/src
**
** Made by Sylviane Tran
** Login   <tran_9@epitech.net>
**
** Started on  Sat Jun 18 15:42:48 2016 Sylviane Tran
** Last update Sun Jun 26 11:55:52 2016 Sylviane Tran
*/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include "person.h"
#include "map.h"

void			*init_font(t_map *map)
{
  TTF_Init();
  if (!(map->items.font.font = TTF_OpenFont("mytype.ttf", 20)))
    {
      printf("Cannot Load Font \n");
      return (NULL);
    }
  map->items.font.dark.r = 0;
  map->items.font.dark.g = 0;
  map->items.font.dark.b = 0;
  return (map);
}

void			*check_load(SDL_Surface **img, int idx)
{
  int			i;

  i = 0;
  while (i < idx)
    {
      if (img[i] == NULL)
	return (NULL);
      i++;
    }
  return (img);
}

void			*init_stones(t_map *map)
{
  if ((map->items.stones_map = malloc(sizeof(SDL_Surface *) * 9)) == NULL)
    return (NULL);
  map->items.stones_map[0] = IMG_Load("./img/linemate64x64.png");
  map->items.stones_map[1] = IMG_Load("./img/deraumere64x64.png");
  map->items.stones_map[2] = IMG_Load("./img/sibur64x64.png");
  map->items.stones_map[3] = IMG_Load("./img/mendiane64x64.png");
  map->items.stones_map[4] = IMG_Load("./img/phiras64x64.png");
  map->items.stones_map[5] = IMG_Load("./img/thystame64x64.png");
  map->items.stones_map[6] = IMG_Load("./img/bucket64x64.png");
  map->items.stones_map[7] = IMG_Load("./img/egg64x64.png");
  map->items.stones_map[8] = NULL;
  if ((map->items.stones_idx = malloc(sizeof(SDL_Surface *) * 9)) == NULL)
    return (NULL);
  map->items.stones_idx[0] = IMG_Load("./img/linemate.png");
  map->items.stones_idx[1] = IMG_Load("./img/deraumere.png");
  map->items.stones_idx[2] = IMG_Load("./img/sibur.png");
  map->items.stones_idx[3] = IMG_Load("./img/mendiane.png");
  map->items.stones_idx[4] = IMG_Load("./img/phiras.png");
  map->items.stones_idx[5] = IMG_Load("./img/thystame.png");
  map->items.stones_idx[6] = IMG_Load("./img/bucket.png");
  map->items.stones_idx[7] = IMG_Load("./img/egg.png");
  map->items.stones_idx[8] = NULL;
  return (map);
}

void			*init_img(t_map *map)
{
  if (!init_stones(map) || !init_font(map))
    return (NULL);
  map->items.grass = IMG_Load("./img/herbe.jpg");
  map->items.grass_ele = IMG_Load("./img/incant.png");
  map->items.select = IMG_Load("./img/select.png");
  if (!check_load(map->items.stones_map, 8)
      || !check_load(map->items.stones_idx, 8) || !map->items.grass_ele
      || !init_perso(map) || !map->items.grass || !map->items.select)
    {
      printf("Cannot Load Image \n");
      return (NULL);
    }
  return (map);
}

void			delay(unsigned int frameLimit, SDL_Surface *win)
{
  unsigned int		ticks;

  SDL_Flip(win);
  ticks = SDL_GetTicks();
  if (frameLimit < ticks)
    return ;
  if (frameLimit > (ticks + FRAME))
    SDL_Delay(FRAME);
  else
    SDL_Delay(frameLimit - ticks);
}
