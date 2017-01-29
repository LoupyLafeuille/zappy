/*
** team.h for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/include
** 
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
** 
** Started on  Mon Jun 13 17:53:32 2016 Loik Gaonach
** Last update Mon Jun 13 17:53:32 2016 Loik Gaonach
*/

#ifndef TEAM_H_
# define TEAM_H_

# include <stdlib.h>
# include "dllc.h"

typedef struct	s_team
{
  int		available;
  char		*name;
  t_dllc	*eggs;
  t_dllc	*persons;
}		t_team;

t_team		*create_team(const char *name, int nb_max);
void		delete_team(t_team *team);
t_team		*find_team(t_dllc *list, const char *name);

#endif
