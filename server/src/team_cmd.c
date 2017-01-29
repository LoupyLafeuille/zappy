/*
** team_cmd.c for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/src
** 
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
** 
** Started on  Mon Jun 13 18:57:28 2016 Loik Gaonach
** Last update Mon Jun 13 18:57:28 2016 Loik Gaonach
*/

#define _GNU_SOURCE
#include <stdio.h>
#include "server.h"
#include "team.h"
#include "person.h"
#include "map.h"
#include "egg.h"

static t_person	*create_team_person(t_server *srv, t_team *team, int fd)
{
  t_person	*pers;
  t_egg		*egg;

  if (len_dllc(team->eggs))
    {
      egg = team->eggs->nxt->data;
      pers = create_person(egg->x, egg->y, team->name, fd);
      srv->map.map[egg->y][egg->x].items[EGGS]--;
      delete_egg(egg);
      delete_elem_dllc(team->eggs->nxt);
    }
  else
    pers = create_person(rand() % srv->map.x, rand() % srv->map.y,
			 team->name, fd);
  if (pers)
    return (pers);
  return (NULL);
}

void		team_name_cmd(const char *cmd, t_server *srv, int fd)
{
  t_team	*team;
  t_person	*pers;
  char		*res;

  if (cmd && (team = find_team(srv->team, cmd)) && team->available)
    {
      if ((pers = create_team_person(srv, team, fd)))
	{
	  team->available--;
	  put_bot_dllc(srv->map.map[pers->y][pers->x].persons, pers);
	  put_bot_dllc(team->persons, pers);
	  srv->sockets[fd].person = pers;
	  srv->sockets[fd].team = 1;
	  if (gettimeofday(&pers->cycle, NULL) == -1)
	    add_responce(srv->sockets[fd].write_buff, "ko\n");
	  if (asprintf(&res, "%d\n%d %d\n", team->available,
		       srv->map.x, srv->map.y) != -1)
	    {
	      add_responce(srv->sockets[fd].write_buff, res);
	      free(res);
	    }
	  return ;
	}
    }
  add_responce(srv->sockets[fd].write_buff, "ko\n");
}

int		fork_cmd(t_server *srv, int fd)
{
  t_socket	*sock;
  t_team	*team;
  t_egg		*egg;

  sock = &srv->sockets[fd];
  if ((team = find_team(srv->team, sock->person->team)))
    {
      team->available++;
      srv->map.map[sock->person->y][sock->person->x].items[EGGS]++;
      if ((egg = create_egg(sock->person->x, sock->person->y)))
	{
	  put_bot_dllc(team->eggs, egg);
	  add_responce(sock->write_buff, "ok\n");
	}
      else
	add_responce(sock->write_buff, "ko\n");
    }
  else
    add_responce(sock->write_buff, "ko\n");
  return (0);
}

int		connect_nbr_cmd(t_server *srv, int fd)
{
  t_team	*team;
  char		*res;

  if ((team = find_team(srv->team, srv->sockets[fd].person->team)))
    {
      if (asprintf(&res, "%d\n", team->available))
	{
	  add_responce(srv->sockets[fd].write_buff, res);
	  free(res);
	  return (0);
	}
    }
  add_responce(srv->sockets[fd].write_buff, "ko\n");
  return (0);
}
