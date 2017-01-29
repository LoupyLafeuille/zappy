/*
** check.c for  in /home/clairegizard/PSU/PSU_2015_zappy/server/src
**
** Made by ClaireGizard
** Login   <gizard_a@epitech.net>
**
** Started on  Tue Jun 14 16:37:39 2016 ClaireGizard
** Last update Tue Jun 21 15:41:46 2016 Sylviane Tran
*/

#include <string.h>
#include "tab_command.h"

int		check_perso_pose(t_person *person, char *buf)
{
  int		i;

  i = 0;
  while (i != 7)
    {
      if ((strcmp(get_obj(i), buf)) == 0)
	{
	  if (person->items[i] >= 1)
	    {
	      --person->items[i];
	      return (0);
	    }
	  return (1);
	}
      ++i;
    }
  return (0);
}

int		check_inventaire_pose(t_server *srv, char *buf, int fd)
{
  int		i;

  i = 0;
  while (i != 7)
    {
      if ((strcmp(get_obj(i), buf)) == 0)
	{
	  ++srv->map.map
	    [srv->sockets[fd].person->y][srv->sockets[fd].person->x].items[i];
	  add_responce(srv->sockets[fd].write_buff, "ok\n");
	  return (0);
	}
      ++i;
    }
  add_responce(srv->sockets[fd].write_buff, "ko\n");
  return (1);
}

int		check_perso(t_person *person, char *buf)
{
  int		i;

  i = 0;
  while (i != 7)
    {
      if ((strcmp(get_obj(i), buf)) == 0)
	{
	  ++person->items[i];
	  return (0);
	}
      ++i;
    }
  return (1);
}

int		check_inventaire(char *buf, t_server *srv, int fd)
{
  int		i;

  i = 0;
  while (i != 7)
    {
      if ((strcmp(get_obj(i), buf)) == 0)
	{
	  if (srv->map.map[srv->sockets[fd].person->y]
	      [srv->sockets[fd].person->x].items[i] >= 1)
	    {
	      --srv->map.map[srv->sockets[fd].person->y]
		[srv->sockets[fd].person->x].items[i];
	      add_responce(srv->sockets[fd].write_buff, "ok\n");
	      return (0);
	    }
	  add_responce(srv->sockets[fd].write_buff, "ko\n");
	  return (1);
	}
      ++i;
    }
  add_responce(srv->sockets[fd].write_buff, "ko\n");
  return (1);
}
