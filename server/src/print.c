/*
** print.c for  in /home/clairegizard/PSU/PSU_2015_zappy/server/src
** 
** Made by ClaireGizard
** Login   <gizard_a@epitech.net>
** 
** Started on  Mon Jun 20 15:01:58 2016 ClaireGizard
** Last update Mon Jun 20 15:05:59 2016 ClaireGizard
*/

#include <stdlib.h>
#include <stdio.h>
#include "args.h"

void	print_usage()
{
  dprintf(1, "./zappy_server -p [port > 1024] -x [width world > 0]");
  dprintf(1, "-y [height world > 0] -n [name of team not null] -c ");
  dprintf(1, "[number of clients team] -t ");
  dprintf(1, "[time delay for executing actions > 0]\n");
}
