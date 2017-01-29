/*
** free_item.c for  in /home/tran_9/Cours/B4/SysT/zappy/PSU_2015_zappy/server
**
** Made by Sylviane Tran
** Login   <tran_9@epitech.net>
**
** Started on  Thu Jun 23 18:34:37 2016 Sylviane Tran
** Last update Fri Jun 24 18:38:55 2016 Sylviane Tran
*/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdlib.h>
#include "map.h"

static void		free_load(SDL_Surface **img)
{
  int			i;

  i = 0;
  while (img && img[i])
    SDL_FreeSurface(img[i++]);
  if (img)
    free(img);
}

static void		free_img(t_item items)
{
  int			i;

  i = 0;
  if (items.grass)
    SDL_FreeSurface(items.grass);
  if (items.grass_ele)
    SDL_FreeSurface(items.grass_ele);
  if (items.select)
    SDL_FreeSurface(items.select);
  if (items.bg != NULL)
    SDL_FreeSurface(items.bg);
  free_load(items.stones_map);
  free_load(items.stones_idx);
  while (items.persons && i < 8)
    free_load(items.persons[i++]);
  if (items.persons)
    free(items.persons);
  if (items.font.font)
    TTF_CloseFont(items.font.font);
}

void			free_item(t_item items, SDL_Surface *win)
{
  if (win != NULL)
    SDL_FreeSurface(win);
  free_img(items);
  if (items.incant)
    Mix_FreeMusic(items.incant);
  if (items.stone)
    Mix_FreeMusic(items.stone);
  Mix_CloseAudio();
  TTF_Quit();
  SDL_Quit();
}
