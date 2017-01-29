/*
** print_data.c for  in /home/tran_9/Cours/B4/SysT/zappy/PSU_2015_zappy/server
**
** Made by Sylviane Tran
** Login   <tran_9@epitech.net>
**
** Started on  Tue Jun 14 16:12:49 2016 Sylviane Tran
** Last update Sun Jun 26 21:44:30 2016 julien
*/

#define _GNU_SOURCE
#include <SDL/SDL.h>
#include <pthread.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include "map.h"

void		aff_text(t_font font, SDL_Surface *win, char *str,
			 SDL_Rect pos)
{
  SDL_Surface	*text;

  if (str != NULL &&
      !(text = TTF_RenderText_Blended(font.font, str, font.dark)))
    return ;
  SDL_BlitSurface(text, NULL, win, &pos);
  SDL_FreeSurface(text);
}

static void	aff_item(const t_case map, t_map maps
			 , SDL_Surface *win)
{
  int		i;
  SDL_Rect	pos;
  char		*str;

  i = 0;
  maps.y = (maps.y > 16) ? 16 : maps.y;
  pos.y = (maps.y * SIZEBLOC) - (SIZEBLOC * 2) + (SIZEBLOC / 2);
  pos.x = maps.x * SIZEBLOC + maps.pos.x;
  while (i < 8)
    {
      asprintf(&str, ": %i", map.items[i]);
      SDL_BlitSurface(maps.items.stones_idx[i], NULL, win, &pos);
      pos.x += 25;
      aff_text(maps.items.font, win, str, pos);
      pos.x += 50;
      free(str);
      i++;
    }
}

static void	aff_stone(t_person *person, t_map maps, int y,
			  SDL_Surface *win)
{
  int		i;
  SDL_Rect	pos;
  char		*str;

  i = 0;
  pos.x = maps.x * SIZEBLOC + 175 + maps.pos.x;
  pos.y = y;
  while (i < 7)
    {
      asprintf(&str, ": %i", person->items[i]);
      SDL_BlitSurface(maps.items.stones_idx[i], NULL, win, &pos);
      pos.x += 25;
      aff_text(maps.items.font, win, str, pos);
      pos.x += 50;
      free(str);
      i++;
    }
}

void		aff_perso(t_case map, t_map maps
			  , SDL_Surface *win)
{
  SDL_Rect	pos;
  t_dllc	*tmp;
  char		*str;

  tmp = map.persons->nxt;
  pos.y = SIZEBLOC;
  while (tmp != map.persons)
    {
      if (tmp->data)
	{
	  pos.x = maps.x * SIZEBLOC;
	  aff_text(maps.items.font, win, ((t_person *)tmp->data)->team, pos);
	  asprintf(&str, "lvl : %i", ((t_person *)tmp->data)->lvl);
	  pos.x += 100;
	  aff_text(maps.items.font, win, str, pos);
	  aff_stone((t_person *)tmp->data, maps, pos.y, win);
	  free(str);
	  pos.y = pos.y + 35;
	}
      tmp = tmp->nxt;
    }
}

void		select_data(t_map map, SDL_Surface *win)
{
  SDL_Rect	pos;

  pos.x = map.press_x * SIZEBLOC;
  pos.y = map.press_y * SIZEBLOC;
  if (map.press_x != -1 && map.press_y != -1)
    {
      map.press_x = map.press_x +
	(((map.pos.x < 0) ? -map.pos.x : map.pos.x) / SIZEBLOC);
      map.press_y = map.press_y +
	(((map.pos.y < 0) ? -map.pos.y : map.pos.y) / SIZEBLOC);
      SDL_BlitSurface(map.items.select, NULL, win, &pos);
      aff_item(map.map[map.press_y][map.press_x], map, win);
    }
}
