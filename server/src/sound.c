/*
** sound.c for zappy in /home/loupy/Rendu/PSU_2015_zappy/server/src
**
** Made by
** Login   <loupy@epitech.net>
**
** Started on  Wed Jun 15 23:15:36 2016
** Last update Sun Jun 26 18:05:04 2016 
*/

#include <string.h>
#include "dllc.h"
#include "tab_command.h"
#include "team.h"
#include "person.h"

static char	set_orientation(char k, e_dir dir)
{
  if (dir == UP)
    return (k + 0);
  else if (dir == DOWN)
    return (k += (k - 44 > 8) ? -4 : 4);
  else if (dir == LEFT)
    return (k += (k - 50 < 1) ? 6 : -2);
  else if (dir == RIGHT)
    return (k += (k - 46 > 8) ? -6 : 2);
  return (k);
}

static void	get_orientation(int vect_x, int vect_y,
				t_person *pers, char *k)
{
  if (vect_x == 0 && vect_y == 0)
    k[0] = '0';
  else if (vect_x == 0)
    k[0] = set_orientation((vect_y > 0) ? '1' : '5', pers->orientation);
  else if (vect_y == 0)
    k[0] = set_orientation((vect_x > 0) ? '3' : '7', pers->orientation);
  else if (vect_x > 0 && vect_y > 0)
    k[0] = set_orientation('2', pers->orientation);
  else if (vect_x < 0 && vect_y < 0)
    k[0] = set_orientation('6', pers->orientation);
  else if (vect_x < 0 && vect_y > 0)
    k[0] = set_orientation('8', pers->orientation);
  else if (vect_x > 0 && vect_y < 0)
    k[0] = set_orientation('4', pers->orientation);
}

static void	get_k(t_server *srv, t_person *pers, int fd, char *k)
{
  int		vect_x;
  int		vect_y;

  vect_x = pers->x - srv->sockets[fd].person->x;
  vect_y = pers->y - srv->sockets[fd].person->y;
  get_orientation(vect_x, vect_y, pers, k);

}

static int	to_each_player(t_server *srv,
			       t_person *pers, int fd, char *tmp)
{
  char		k[2];
  char		*buff;

  if (pers->fd != fd)
    {
      memset(k, 0, 2);
      if ((buff = malloc(12 + strlen(tmp))) == NULL)
	return (0);
      memset(buff, 0, 12 + strlen(tmp));
      get_k(srv, pers, fd, k);
      strcpy(buff, "message ");
      strcat(strcat(strcat(buff, k), ","), tmp);
      add_responce(srv->sockets[pers->fd].write_buff, buff);
      free(buff);
    }
  return (1);
}

int		broadcast_texte_cmd(t_server *srv, int fd)
{
  t_dllc	*tmp;
  t_dllc	*tmp2;
  t_team	*team;
  t_person	*pers;
  char		*msg;

  tmp = srv->team->nxt;
  if ((msg = strtok(NULL, "\0")) == NULL)
    return (-1);
  while (tmp != srv->team)
    {
      team = tmp->data;
      tmp2 = team->persons->nxt;
      while (tmp2 != team->persons)
	{
	  pers = tmp2->data;
	  if (pers->fd != fd)
	    if (to_each_player(srv, pers, fd, msg) == -1)
	      return (0);
	  tmp2 = tmp2->nxt;
	}
      tmp = tmp->nxt;
    }
  add_responce(srv->sockets[fd].write_buff, "ok\n");
  return (0);
}
