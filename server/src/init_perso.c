/*
** init_perso.c for init_perso in /home/tran_9/Cours/B4/SysT/zappy/PSU_2015_zappy/server
**
** Made by Sylviane Tran
** Login   <tran_9@epitech.net>
**
** Started on  Sun Jun 19 22:48:09 2016 Sylviane Tran
** Last update Fri Jun 24 18:00:19 2016 Sylviane Tran
*/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include "person.h"
#include "map.h"

static void			init_face(t_map *map)
{
  int				i;

  i = 0;
  map->items.persons[0][DOWN] = IMG_Load("./img/evolie_face64x64.png");
  map->items.persons[1][DOWN] = IMG_Load("./img/Aquali_face64x64.png");
  map->items.persons[2][DOWN] = IMG_Load("./img/givrali_face64x64.png");
  map->items.persons[3][DOWN] = IMG_Load("./img/Noctali_face64x64.png");
  map->items.persons[4][DOWN] = IMG_Load("./img/Pyrolie_face64x64.png");
  map->items.persons[5][DOWN] = IMG_Load("./img/Mentali_face64x64.png");
  map->items.persons[6][DOWN] = IMG_Load("./img/Phyllali_face64x64.png");
  map->items.persons[7][DOWN] = IMG_Load("./img/voltali_face64x64.png");
  while (i < 8)
    map->items.persons[i++][4] = NULL;
}

static void			init_back(t_map *map)
{
  map->items.persons[0][UP] = IMG_Load("./img/evolie_dos64x64.png");
  map->items.persons[1][UP] = IMG_Load("./img/Aquali_dos64x64.png");
  map->items.persons[2][UP] = IMG_Load("./img/givrali_dos64x64.png");
  map->items.persons[3][UP] = IMG_Load("./img/Noctali_dos64x64.png");
  map->items.persons[4][UP] = IMG_Load("./img/Pyroli_dos64x64.png");
  map->items.persons[5][UP] = IMG_Load("./img/Mentali_dos64x64.png");
  map->items.persons[6][UP] = IMG_Load("./img/Phyllali_dos64x64.png");
  map->items.persons[7][UP] = IMG_Load("./img/voltali_dos64x64.png");
}

static void			init_left(t_map *map)
{
  map->items.persons[0][LEFT] = IMG_Load("./img/evolie_left64x64.png");
  map->items.persons[1][LEFT] = IMG_Load("./img/aquali_left64x64.png");
  map->items.persons[2][LEFT] = IMG_Load("./img/Givrali_left64x64.png");
  map->items.persons[3][LEFT] = IMG_Load("./img/Noctali_left64x64.png");
  map->items.persons[4][LEFT] = IMG_Load("./img/Pyroli_left64x64.png");
  map->items.persons[5][LEFT] = IMG_Load("./img/Mentali_left64x64.png");
  map->items.persons[6][LEFT] = IMG_Load("./img/Phyllali_left64x64.png");
  map->items.persons[7][LEFT] = IMG_Load("./img/voltali_left64x64.png");
}

static void			init_right(t_map *map)
{
  map->items.persons[0][RIGHT] = IMG_Load("./img/evolie_right64x64.png");
  map->items.persons[1][RIGHT] = IMG_Load("./img/aquali_right64x64.png");
  map->items.persons[2][RIGHT] = IMG_Load("./img/Givrali_right64x64.png");
  map->items.persons[3][RIGHT] = IMG_Load("./img/Noctali_right64x64.png");
  map->items.persons[4][RIGHT] = IMG_Load("./img/Pyroli_right64x64.png");
  map->items.persons[5][RIGHT] = IMG_Load("./img/Mentali_right64x64.png");
  map->items.persons[6][RIGHT] = IMG_Load("./img/Phyllali_right64x64.png");
  map->items.persons[7][RIGHT] = IMG_Load("./img/voltali_right64x64.png");
}

void				*init_perso(t_map *map)
{
  int				i;

  i = 0;
  if ((map->items.persons = malloc(sizeof(SDL_Surface **) * 9)) == NULL)
    return (NULL);
  while (i < 8)
    if ((map->items.persons[i++] = malloc(sizeof(SDL_Surface *) * 5)) == NULL)
      return (NULL);
  map->items.persons[i] = NULL;
  i = 0;
  init_face(map);
  init_left(map);
  init_right(map);
  init_back(map);
  while (i < 8)
    if (!check_load(map->items.persons[i++], 4))
      return (NULL);
  return (map);
}
