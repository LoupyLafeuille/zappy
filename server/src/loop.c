/*
** loop.c for myirc in /home/pumpkin/Epitech/PSU_2015_zappy/server/src
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Thu Jun 09 14:41:01 2016 Loik Gaonach
** Last update Sun Jun 26 01:35:29 2016 Sylviane Tran
*/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "server.h"

void			print_help(t_map map, SDL_Surface *win)
{
  int			i;
  SDL_Rect		pos;

  i = 0;
  map.y = (map.y > 16) ? 16 : map.y;
  pos.x = map.x * SIZEBLOC + map.pos.x;
  pos.y = (map.y - 1) * SIZEBLOC;
  while (i < 8)
    {
      SDL_BlitSurface(map.items.stones_idx[i], NULL, win, &pos);
      pos.x += 25;
      aff_text(map.items.font, win, " : ", pos);
      pos.x += 20;
      aff_text(map.items.font, win, get_obj(i), pos);
      pos.x += 130;
      i++;
      if (i == 4)
	{
	  pos.x = map.x * SIZEBLOC + map.pos.x;
	  pos.y += 30;
	}
    }
}

static SDL_Surface	*size_win(t_server *srv)
{
  int			x;
  int			y;

  if (srv->map.x > 19)
    x = 19 * SIZEBLOC + DATA;
  else
    x = srv->map.x * SIZEBLOC + DATA;
  if (srv->map.y > 16)
    y = 16 * SIZEBLOC;
  else

    y = srv->map.y * SIZEBLOC;
  if (!(srv->map.items.bg =
	SDL_CreateRGBSurface(SDL_HWSURFACE, x, y,
			     32, 0, 0, 0, 0)))
    return (NULL);
  return (SDL_SetVideoMode(x, y, 32, SDL_HWSURFACE));
}

static SDL_Surface	*init_win(t_server *srv)
{
  SDL_Surface		*win;
  SDL_Rect		pos;

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  init_struct(&srv->map);
  if (!(win = size_win(srv)))
    return (NULL);
  SDL_FillRect(win, NULL, SDL_MapRGB(win->format, 175, 202, 151));
  pos.x = srv->map.x * SIZEBLOC;
  pos.y = 0;
  SDL_FillRect(srv->map.items.bg, NULL,
	       SDL_MapRGB(win->format, 175, 202, 151));
  SDL_BlitSurface(srv->map.items.bg, NULL, win, &pos);
  if (!init_img(&srv->map) || !init_sound(&srv->map.items))
    return (NULL);
  srv->map.items.frameLimit = SDL_GetTicks() + FRAME;
  return (win);
}

static void		scroll_win(SDL_Event event, t_server *srv)
{
  int			x;
  int			y;

  x = (srv->map.x > 19) ? 19 : srv->map.x;
  y = (srv->map.y > 16) ? 16 : srv->map.y;
  if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == SDLK_DOWN
	  && (y * SIZEBLOC + (-srv->map.pos.y)) < (srv->map.y * SIZEBLOC))
	srv->map.pos.y = (srv->map.pos.y - SIZEBLOC) % (y * SIZEBLOC);
      if (event.key.keysym.sym == SDLK_UP && srv->map.pos.y)
	srv->map.pos.y = (srv->map.pos.y + SIZEBLOC) % (y * SIZEBLOC);
      if (event.key.keysym.sym == SDLK_RIGHT && srv->map.pos.x)
	srv->map.pos.x = (srv->map.pos.x + SIZEBLOC) % (x * SIZEBLOC + DATA);
      if (event.key.keysym.sym == SDLK_LEFT
	  && (x * SIZEBLOC + DATA + (-srv->map.pos.x))
	  < (srv->map.x * SIZEBLOC + DATA))
	srv->map.pos.x = (srv->map.pos.x - SIZEBLOC) % (x * SIZEBLOC + DATA);
    }
}

void			*loop(void *args)
{
  int			flag;
  t_server		*srv;
  SDL_Surface		*win;
  SDL_Event		event;

  flag = 1;
  srv = args;
  win = init_win(srv);
  while (win != NULL && flag)
    {
      update(win, &srv->map);
      SDL_PollEvent(&event);
      if ((event.type == SDL_QUIT || (event.type == SDL_KEYDOWN
				      && event.key.keysym.sym == SDLK_ESCAPE)))
	flag = 0;
      if (event.type == SDL_MOUSEBUTTONDOWN)
	set_key(&srv->map, event.button.x, event.button.y);
      scroll_win(event, srv);
      select_data(srv->map, win);
      print_help(srv->map, win);
      delay(srv->map.items.frameLimit, win);
    }
  free_item(srv->map.items, win);
  return (NULL);
}
