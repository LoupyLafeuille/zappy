/*
** init_nbr.c for zappy in /home/loupy/Rendu/PSU_2015_zappy/server/src
**
** Made by
** Login   <loupy@epitech.net>
**
** Started on  Thu Jun  9 14:45:50 2016
** Last update Mon Jun 20 11:09:31 2016 ClaireGizard
*/

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "args.h"

int		init_port(t_param *param, int ac, char **av, int *i)
{
  if (++*i < ac)
    {
      if ((param->port = atoi(av[*i])) < 1024)
	return (-1);
    }
  return (0);
}

int		init_x(t_param *param, int ac, char **av, int *i)
{
  if (++*i < ac)
    {
      if ((param->x = atoi(av[*i])) < 0)
	return (-1);
    }
  return (0);
}

int		init_y(t_param *param, int ac, char **av, int *i)
{
  if (++*i < ac)
    {
      if ((param->y = atoi(av[*i])) < 0)
	return (-1);
    }
  return (0);
}

int		init_nb_client(t_param *param, int ac, char **av, int *i)
{
  if (++*i < ac)
    {
      if ((param->nb_client = atoi(av[*i])) < 2)
	return (-1);
    }
  return (0);
}

int		init_delai(t_param *param, int ac, char **av, int *i)
{
  if (++*i < ac)
    {
      if ((param->delai = atoi(av[*i])) <= 0)
	return (-1);
    }
  return (0);
}
