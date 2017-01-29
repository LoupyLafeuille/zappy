/*
** args.c for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/src
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Wed Jun 08 18:56:35 2016 Loik Gaonach
** Last update Sat Jun 25 21:54:39 2016 
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "args.h"

t_args		g_args_server[] =
  {
    {"-p", &init_port},
    {"-x", &init_x},
    {"-y", &init_y},
    {"-c", &init_nb_client},
    {"-t", &init_delai},
    {"-n", &init_name},
    {"-i", &init_interface},
    {NULL, NULL}
  };

void		delete_param(t_param *param)
{
  int		i;

  i = 0;
  while (i < param->nb_client)
    free(param->name[i++]);
  free(param->name);
  free(param);
}

static int	get_arg_pos(const char *str)
{
  int		i;

  i = 0;
  while (g_args_server[i].flag != NULL)
    {
      if (strcmp(g_args_server[i].flag, str) == 0)
	return (i);
      ++i;
    }
  return (-1);
}

int		check_nb_param(t_param *param)
{
  if (param->port < 1024 || param->delai <= 0 || param->x <= 1 || param->y <= 1
      || param->nb_client < 2 || param->name == NULL)
    {
      print_usage();
      return (1);
    }
  return (0);
}

t_param		*get_param(int ac, char **av)
{
  t_param	*param;
  int		i;
  int		pos;

  i = 1;
  if ((param = malloc(sizeof(t_param))) == NULL)
    return (NULL);
  if (init_param(param) == -1)
    return (NULL);
  while (i < ac)
    {
      if (((pos = get_arg_pos(av[i])) == -1)
	  || (g_args_server[pos].set_param(param, ac, av, &i) == -1))
	{
	  print_usage();
	  return (NULL);
	}
      ++i;
    }
  if ((check_nb_param(param)) == 1)
    return (NULL);
  return (param);
}
