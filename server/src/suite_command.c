/*
** suite_command.c for  in /home/clairegizard/PSU/PSU_2015_zappy/server/src
**
** Made by ClaireGizard
** Login   <gizard_a@epitech.net>
**
** Started on  Thu Jun  9 09:46:45 2016 ClaireGizard
** Last update Tue Jun 21 15:09:57 2016 
*/

#include <string.h>
#include "dllc.h"
#include "tab_command.h"

int		pose_obj_cmd(t_server *srv, int fd)
{
  char		*buf;
  t_person	*person;

  if ((buf = strtok(NULL, "\n")) == NULL)
    {
      add_responce(srv->sockets[fd].write_buff, "ko\n");
      return (1);
    }
  person = srv->sockets[fd].person;
  if (check_perso_pose(person, buf) != 1)
    check_inventaire_pose(srv, buf, fd);
  return (0);
}

int		prend_obj_cmd(t_server *srv, int fd)
{
  char		*buf;
  t_person	*person;

  if ((buf = strtok(NULL, "\n")) == NULL)
    {
      add_responce(srv->sockets[fd].write_buff, "ko\n");
      return (1);
    }
  person = srv->sockets[fd].person;
  if ((check_inventaire(buf, srv, fd)) != 1)
    {
      check_perso(person, buf);
      srv->map.take_stone = 1;
    }
  return (0);
}
