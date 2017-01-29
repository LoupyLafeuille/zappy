/*
** expulse.c for  in /home/clairegizard/PSU/PSU_2015_zappy/server/src
**
** Made by ClaireGizard
** Login   <gizard_a@epitech.net>
**
** Started on  Sat Jun 18 11:39:21 2016 ClaireGizard
** Last update Wed Jun 22 12:29:27 2016 ClaireGizard
*/

#include <pthread.h>
#include "dllc.h"
#include "tab_command.h"
#include "person_utils.h"

t_send		g_send[] =
  {
    {UP, &send_up},
    {DOWN, &send_down},
    {LEFT, &send_left},
    {RIGHT, &send_right},
    {0, NULL}
  };

void		expulse(t_person *person, t_server *srv, e_dir direct)
{
  int		i;

  i = 0;
  while (g_move[i].fct != NULL)
    {
      if (g_move[i].dir == direct)
	{
	  g_move[i].fct(&(srv->map), person);
	  g_send[i].fct(srv, person);
	}
      ++i;
    }
}

int		expulse_cmd(t_server *srv, int fd)
{
  t_person	*person;
  t_dllc	*tmp;
  t_dllc	*next;
  t_person	*tmp_person;

  person = srv->sockets[fd].person;
  tmp = srv->map.map[person->y][person->x].persons->nxt;
  while (tmp != srv->map.map[person->y][person->x].persons)
    {
      tmp_person = tmp->data;
      if (person != tmp_person)
	{
	  next = tmp->nxt;
	  expulse(tmp_person, srv, person->orientation);
	  remove_person(srv->map.map[person->y][person->x].persons, tmp_person);
	  tmp = next;
	}
      else
	tmp = tmp->nxt;
    }
  return (0);
}
