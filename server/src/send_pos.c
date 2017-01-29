/*
** send_pos.c for  in /home/clairegizard/PSU/PSU_2015_zappy/server/src
**
** Made by ClaireGizard
** Login   <gizard_a@epitech.net>
**
** Started on  Sat Jun 18 14:37:42 2016 ClaireGizard
** Last update Thu Jun 23 12:17:40 2016 ClaireGizard
*/

#include "tab_command.h"

int	send_up(t_server *srv, t_person *person)
{
  char	*buf;

  buf = NULL;
  if ((buf = malloc(sizeof(char) * 20)) == NULL)
    return (1);
  bzero(buf, (sizeof(char) * 20));
  strcat(buf, "deplacement: ");
  if (person->orientation == 0)
    strcat(buf, "5");
  else if (person->orientation == 1)
    strcat(buf, "7");
  else if (person->orientation == 2)
    strcat(buf, "1");
  else if (person->orientation == 3)
    strcat(buf, "3");
  strcat(buf, "\n");
  add_responce(srv->sockets[person->fd].write_buff, buf);
  free(buf);
  return (0);
}

int	send_down(t_server *srv, t_person *person)
{
  char	*buf;

  buf = NULL;
  if ((buf = malloc(sizeof(char) * 20)) == NULL)
    return (1);
  bzero(buf, (sizeof(char) * 20));
  strcat(buf, "deplacement: ");
  if (person->orientation == 0)
    strcat(buf, "1");
  else if (person->orientation == 1)
    strcat(buf, "3");
  else if (person->orientation == 2)
    strcat(buf, "5");
  else if (person->orientation == 3)
    strcat(buf, "7");
  strcat(buf, "\n");
  add_responce(srv->sockets[person->fd].write_buff, buf);
  free(buf);
  return (0);
}

int	send_left(t_server *srv, t_person *person)
{
  char	*buf;

  buf = NULL;
  if ((buf = malloc(sizeof(char) * 20)) == NULL)
    return (1);
  bzero(buf, (sizeof(char) * 20));
  strcat(buf, "deplacement: ");
  if (person->orientation == 0)
    strcat(buf, "7");
  else if (person->orientation == 1)
    strcat(buf, "1");
  else if (person->orientation == 2)
    strcat(buf, "3");
  else if (person->orientation == 3)
    strcat(buf, "5");
  strcat(buf, "\n");
  add_responce(srv->sockets[person->fd].write_buff, buf);
  free(buf);
  return (0);
}

int	send_right(t_server *srv, t_person *person)
{
  char	*buf;

  buf = NULL;
  if ((buf = malloc(sizeof(char) * 20)) == NULL)
    return (1);
  bzero(buf, (sizeof(char) * 20));
  strcat(buf, "deplacement: ");
  if (person->orientation == 0)
    strcat(buf, "3");
  else if (person->orientation == 1)
    strcat(buf, "5");
  else if (person->orientation == 2)
    strcat(buf, "7");
  else if (person->orientation == 3)
    strcat(buf, "1");
  strcat(buf, "\n");
  add_responce(srv->sockets[person->fd].write_buff, buf);
  free(buf);
  return (0);
}
