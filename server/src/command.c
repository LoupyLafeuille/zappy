/*
** command.c for  in /home/clairegizard/PSU/PSU_2015_zappy/server/src
**
** Made by ClaireGizard
** Login   <gizard_a@epitech.net>
**
** Started on  Thu Jun  9 09:44:53 2016 ClaireGizard
** Last update Wed Jun 22 10:38:45 2016 ClaireGizard
*/

#define _GNU_SOURCE
#include <stdio.h>
#include "server.h"
#include "dllc.h"
#include "tab_command.h"

int			inventaire_cmd(t_server *srv, int fd)
{
  char			*buf;
  int			*inv;
  int			ret;

  inv = srv->sockets[fd].person->items;
  ret = asprintf(&buf, "{%s %d, %s %d, %s %d, %s %d, %s %d, %s %d, %s %d}\n",
	   get_obj(0), inv[0], get_obj(1), inv[1], get_obj(2), inv[2],
	   get_obj(3), inv[3], get_obj(4), inv[4], get_obj(5), inv[5],
	   get_obj(6), inv[6]);
  if (ret != -1)
    add_responce(srv->sockets[fd].write_buff, buf);
  free(buf);
  return (0);
}
