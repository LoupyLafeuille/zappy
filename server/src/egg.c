/*
** egg.c for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/src
** 
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
** 
** Started on  Sat Jun 18 04:03:20 2016 Loik Gaonach
** Last update Sat Jun 18 04:03:20 2016 Loik Gaonach
*/

#include <stdlib.h>
#include "egg.h"

t_egg	*create_egg(int x, int y)
{
  t_egg	*egg;

  if ((egg = malloc(sizeof(t_egg))) == NULL)
    return (NULL);
  egg->x = x;
  egg->y = y;
  return (egg);
}

void	delete_egg(t_egg *egg)
{
  free(egg);
}
