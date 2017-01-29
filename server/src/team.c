/*
** team.c for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/src
** 
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
** 
** Started on  Mon Jun 13 18:08:39 2016 Loik Gaonach
** Last update Mon Jun 13 18:08:39 2016 Loik Gaonach
*/

#include <stdlib.h>
#include <string.h>
#include "team.h"
#include "egg.h"

t_team		*create_team(const char *name, int nb_max)
{
  t_team	*team;

  if ((team = malloc(sizeof(*team))) == NULL)
    return (NULL);
  if ((team->name = strdup(name)) == NULL)
    return (NULL);
  if ((team->persons = create_dllc()) == NULL)
    return (NULL);
  if ((team->eggs = create_dllc()) == NULL)
    return (NULL);
  team->available = nb_max;
  return (team);
}

void		delete_team(t_team *team)
{
  if (team->name)
    {
      free(team->name);
      team->name = NULL;
    }
  delete_dllc(&team->persons);
  delete_dllc(&team->eggs);
  free(team);
}

t_team		*find_team(t_dllc *list, const char *name)
{
  t_dllc	*tmp;

  tmp = list->nxt;
  while (tmp != list)
    {
      if (strcmp(name, ((t_team*)tmp->data)->name) == 0)
	return (tmp->data);
      tmp = tmp->nxt;
    }
  return (NULL);
}
