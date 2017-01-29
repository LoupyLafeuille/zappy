/*
** handle_client.c for myirc in /home/pumpkin/Epitech/PSU_2015_myirc/server_src
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>net
**
** Started on  Mon May 23 17:35:34 2016 Loik Gaonach
** Last update Sun Jun 26 22:06:39 2016 julien
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "server.h"
#include "team.h"
#include "game.h"
#include "person_utils.h"

static unsigned long	handle_request(t_server *srv)
{
  int			fd;
  unsigned long		min;
  unsigned long		t;

  fd = 0;
  min = CYCLE / srv->args->delai * 1000000;
  while (fd < FD_SETSIZE)
    {
      if (srv->sockets[fd].type == FD_CLIENT)
	{
	  t = client_handler(srv, fd);
	  t = (t > (unsigned long)CYCLE / srv->args->delai * 1000000) ?
	    (unsigned long)CYCLE / srv->args->delai * 1000000 : t;
	  min = (t < min) ? t : min;
	}
      else if (srv->sockets[fd].type == FD_DUMMY)
	stdin_handler(srv, fd);
      ++fd;
    }
  return (min);
}

static int		my_fd_set(t_socket *sock, fd_set *fd_read,
				  fd_set *fd_write)
{
  int			fd_max;
  int			i;

  FD_ZERO(fd_read);
  FD_ZERO(fd_write);
  fd_max = 0;
  i = 0;
  while (i < FD_SETSIZE)
    {
      if (sock[i].type != FD_FREE)
	{
	  if (sock[i].write_buff && len_dllc(sock[i].write_buff))
	    FD_SET(i, fd_write);
	  FD_SET(i, fd_read);
	  fd_max = i;
	}
      i++;
    }
  return (fd_max);
}

static void		my_fd_isset(t_server *srv, fd_set *fd_read,
				    fd_set *fd_write)
{
  int			i;

  i = 0;
  while (i < FD_SETSIZE)
    {
      if (FD_ISSET(i, fd_read))
	{
	  if (srv->sockets[i].read_func(srv->sockets, i) == -1)
	    destroy_person(srv, i);
	}
      if (FD_ISSET(i, fd_write) && srv->sockets[i].type == FD_CLIENT)
	srv->sockets[i].write_func(srv->sockets, i);
      i++;
    }
}

static int		process(t_server *srv, struct timeval *tv,
				struct timeval **ptr)
{
  double		t;

  t = handle_request(srv);
  tv->tv_sec = 0;
  tv->tv_usec = t;
  *ptr = tv;
  if (game_run(srv))
    return (1);
  return (0);
}

int			handle_clients(t_server *srv)
{
  struct timeval	tv;
  int			fd_max;
  int			error;
  fd_set		fd_read;
  fd_set		fd_write;
  struct timeval	*ptr;

  tv.tv_sec = 1;
  tv.tv_usec = 1;/* CYCLE / srv->args->delai * 1000000; */
  ptr = &tv;
  error = 0;
  while (!error)
    {
      fd_max = my_fd_set(srv->sockets, &fd_read, &fd_write);
      if (select(fd_max + 1, &fd_read, &fd_write, NULL, ptr) >= 0)
	{
	  my_fd_isset(srv, &fd_read, &fd_write);
	  if (process(srv, &tv, &ptr))
	    return (0);
	}
      else
	error = 1;
    }
  return (error);
}
