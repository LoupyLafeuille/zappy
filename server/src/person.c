/*
** person.c for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/src
** 
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
** 
** Started on  Wed Jun 15 00:23:25 2016 Loik Gaonach
** Last update Wed Jun 15 00:23:25 2016 Loik Gaonach
*/

#include <stdlib.h>
#include <string.h>
#include "person.h"
#include "map.h"

t_person	*create_person(int x, int y, char *team, int fd)
{
  t_person	*pers;

  if ((pers = malloc(sizeof(t_person))) == NULL)
    return (NULL);
  memset(pers, 0, sizeof(t_person));
  pers->orientation = DEFAULT_ORIENTATION;
  pers->life = DEFAULT_LIFE;
  pers->lvl = DEFAULT_LEVEL;
  pers->x = x;
  pers->y = y;
  pers->items[FOOD] = DEFAULT_FOOD;
  pers->team = team;
  pers->fd = fd;
  gettimeofday(&pers->cycle, NULL);
  return (pers);
}

void		delete_person(t_person *pers)
{
  free(pers);
}
