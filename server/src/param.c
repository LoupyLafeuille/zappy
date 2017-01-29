/*
** param.c for lp in /home/loupy/Rendu/PSU_2015_zappy/server/src
**
** Made by
** Login   <loupy@epitech.net>
**
** Started on  Wed Jun  8 14:52:41 2016
** Last update Sun Jun 26 21:46:52 2016 julien
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "args.h"

int		init_param(t_param *param)
{
  param->port = PORT;
  param->x = MAP_X;
  param->y = MAP_Y;
  param->nb_client = NB_CLIENT;
  param->delai = DELAI;
  param->i = DEFAULT_I;
  return (0);
}

static int	count_word(int ac, char **av, int i)
{
  int		cpt;

  cpt = 0;
  while (i < ac)
    {
      if (av[i][0] != '-')
	++cpt;
      else
	return (cpt);
      ++i;
    }
  return (cpt);
}

int		init_name(t_param *param, int ac, char **av, int *i)
{
  int		idx;
  int		cpt;
  char		**tab;

  idx = 0;
  ++*i;
  cpt = count_word(ac, av, *i);
  if (cpt <= 0)
    return (-1);
  if ((tab = malloc(sizeof(char *) * (cpt + 1))) == NULL)
    return (-1);
  while (idx < cpt)
    {
      if ((tab[idx] = malloc(sizeof(char) * strlen(av[*i]) + 1)) == NULL)
	return (-1);
      if (strcpy(tab[idx], av[*i]) == NULL)
	return (-1);
      ++*i;
      ++idx;
    }
  tab[idx] = NULL;
  param->name = tab;
  --*i;
  return (0);
}

int		init_interface(t_param *param, int ac, char **av, int *i)
{
  param->i = 0;
  (void)ac;
  (void)av;
  (void)i;
  return (0);
}
