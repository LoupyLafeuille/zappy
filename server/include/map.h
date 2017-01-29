/*
** map.h for  in /home/clairegizard/PSU/PSU_2015_zappy/server/include
**
** Made by ClaireGizard
** Login   <gizard_a@epitech.net>
**
** Started on  Wed Jun  8 17:06:33 2016 ClaireGizard
** Last update Sun Jun 26 19:28:29 2016 Sylviane Tran
** Last update Sat Jun 25 15:24:15 2016
*/

# ifndef MAP_H_
# define MAP_H_

# define SIZEBLOC	64
# define DATA		700
# define FRAME		60

# include <SDL/SDL.h>
# include <SDL/SDL_mixer.h>
# include <SDL/SDL_ttf.h>
# include "args.h"
# include "dllc.h"
# include "socket.h"

enum		ITEM
  {
    LINEMATE = 0,
    DERAUMERE,
    SIBUR,
    MEDIANE,
    PHIRAS,
    THYSTANE,
    FOOD,
    EGGS
  };

typedef struct	s_case
{
  t_dllc	*persons;
  int		items[8];
  char		incant;
}		t_case;

typedef struct	s_font
{
  SDL_Color	dark;
  TTF_Font	*font;
}		t_font;

typedef struct	s_item
{
  unsigned int	frameLimit;
  SDL_Surface	*grass;
  SDL_Surface	*grass_ele;
  SDL_Surface	*select;
  SDL_Surface	*bg;
  SDL_Surface	**stones_map;
  SDL_Surface	**stones_idx;
  SDL_Surface	***persons;
  Mix_Music	*incant;
  Mix_Music	*stone;
  t_font	font;
}		t_item;

typedef struct	s_map
{
  int		x;
  int		y;
  int		press_x;
  int		press_y;
  char		take_stone;
  SDL_Rect	pos;
  t_item	items;
  t_case	**map;
}		t_map;

char		*get_obj(int i);

t_map		*create_map(const t_param *, t_map *);

int		pos_perso(t_socket *, t_map *);

void		add_food(t_map *map);
void		aff_text(t_font font, SDL_Surface *win, char *str, SDL_Rect pos);
void		update(SDL_Surface *, t_map *);
void		free_item(t_item items, SDL_Surface *win);
void		select_data(t_map, SDL_Surface *);
void		*init_img(t_map *);
void		*init_perso(t_map *map);
void		*init_sound(t_item *item);
void		*check_load(SDL_Surface **img, int idx);
void		delete_map(t_map *map);
void		delay(unsigned int frameLimit, SDL_Surface *win);
void		set_key(t_map *map, int x, int y);
void		init_struct(t_map *map);

#endif /* MAP_H_ */
