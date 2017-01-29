/*
** movement.c for  in /home/tran_9/Cours/B4/SysT/zappy/PSU_2015_zappy/server/src
**
** Made by Sylviane Tran
** Login   <tran_9@epitech.net>
**
** Started on  Sat Jun 18 16:38:37 2016 Sylviane Tran
** Last update Sat Jun 18 16:38:59 2016 Sylviane Tran
*/

#include "server.h"
#include "dllc.h"
#include "tab_command.h"

t_move		g_move[] =
  {
    {UP, &move_up},
    {DOWN, &move_down},
    {LEFT, &move_left},
    {RIGHT, &move_right},
    {0, NULL}
  };

int		droite_cmd(t_server *srv, int fd)
{
  t_person	*person;
  e_dir		i;

  person = srv->sockets[fd].person;
  i = person->orientation;
  if (i == 3)
    person->orientation = UP;
  else
    person->orientation = i + 1;
  add_responce(srv->sockets[fd].write_buff, "ok\n");
  return (0);
}

int		gauche_cmd(t_server *srv, int fd)
{
  t_person	*person;
  e_dir		i;

  person = srv->sockets[fd].person;
  i = person->orientation;
  if (i == 0)
    person->orientation = LEFT;
  else
    person->orientation = i - 1;
  add_responce(srv->sockets[fd].write_buff, "ok\n");
  return (0);
}
