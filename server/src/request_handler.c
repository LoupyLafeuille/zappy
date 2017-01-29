/*
** io_handler.c for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/src
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Thu Jun 09 00:32:17 2016 Loik Gaonach
** Last update Sun Jun 26 17:28:46 2016 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"
#include "request.h"
#include "tab_command.h"
#include "game.h"
#include "time_utils.h"

static void		cleanup_request(t_dllc *elem, t_req *req)
{
  delete_request(req);
  delete_elem_dllc(elem);
}

static t_command	*command_exist(const t_req *req)
{
  char			*end;
  int			i;
  unsigned int		len;

  i = 0;
  if ((end = strpbrk(req->msg, " \n")))
    {
      if (end - req->msg <= 0)
	return (NULL);
      len = end - req->msg;
      while (g_tab[i].str)
	{
	  if (len == strlen(g_tab[i].str)
	      && strncmp(g_tab[i].str, req->msg, len) == 0)
	    return (&g_tab[i]);
	  ++i;
	}
    }
  return (NULL);
}

static double	process_request(t_server *srv, int fd, t_req *req,
				t_command *s_cmd)
{
  double	t;

  if (!req->started)
    {
      if (strcmp(s_cmd->str, "incantation") == 0 && !check_incant(srv, fd, 1))
	{
	  add_responce(srv->sockets[fd].write_buff, "ko\n");
	  cleanup_request(srv->sockets[fd].read_buff->nxt, req);
	  req->started = 1;
	  gettimeofday(&req->start, NULL);
	  return (0);
	}
      req->started = 1;
      gettimeofday(&req->start, NULL);
    }
  t = (s_cmd->delay == 0) ? 0 : (s_cmd->delay / srv->args->delai) * 1000000;
  if (t == 0 || diff_time_now(&req->start) >= t)
    {
      (void)strtok(req->msg, " \n");
      s_cmd->fct(srv, fd);
      cleanup_request(srv->sockets[fd].read_buff->nxt, req);
      return (0);
    }
  else
    return (t - diff_time_now(&req->start));
}

double		client_handler(t_server *srv, int fd)
{
  t_req		*req;
  t_command	*s_cmd;
  double	wait;

  wait = CYCLE / srv->args->delai * 1000000;
  if ((req = get_request(srv->sockets[fd].read_buff)))
    {
      if (!srv->sockets[fd].team)
	{
	  team_name_cmd(strtok(req->msg, "\n"), srv, fd);
	  cleanup_request(srv->sockets[fd].read_buff->nxt, req);
	  wait = 0;
	}
      else if (!(s_cmd = command_exist(req)))
	{
	  cleanup_request(srv->sockets[fd].read_buff->nxt, req);
	  add_responce(srv->sockets[fd].write_buff, "ko\n");
	  wait = 0;
	}
      else
	wait = process_request(srv, fd, req, s_cmd);
    }
  return (wait);
}

void		stdin_handler(t_server *srv, int fd)
{
  t_req		*req;
  int		i;

  if ((req = pop_request(srv->sockets[fd].read_buff)))
    {
      if (strcmp(req->msg, "quit\n") == 0)
	{
	  i = 0;
	  while (i < FD_SETSIZE)
	    {
	      if (srv->sockets[i].type != FD_FREE)
		delete_socket(srv->sockets, i);
	      ++i;
	    }
	  exit(EXIT_SUCCESS);
	}
      delete_request(req);
    }
}
