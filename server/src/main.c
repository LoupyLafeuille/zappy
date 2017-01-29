/*
** main.c for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/src
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Tue Jun 07 18:17:32 2016 Loik Gaonach
** Last update Sun Jun 26 22:08:42 2016 julien
*/

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "server.h"
#include "team.h"
#include "map.h"

pthread_t	g_ui_thread;

static void	sigHandler(int sig)
{
  if (sig == SIGINT)
    exit(EXIT_SUCCESS);
}

static int	setup_team(t_server *srv)
{
  int		i;
  t_team	*t;

  if ((srv->team = create_dllc()) == NULL)
    return (-1);
  i = 0;
  while (srv->args->name[i])
    {
      if ((t = create_team(srv->args->name[i], srv->args->nb_client)) == NULL)
	return (-1);
      put_bot_dllc(srv->team, t);
      ++i;
    }
  return (0);
}

static int	init(t_server *srv, int ac, char **av)
{
  int		fd;

  memset(srv->sockets, 0, FD_SETSIZE * sizeof(t_socket));
  if ((fd = create_socket()) == -1)
    return (-1);
  if ((srv->args = get_param(ac, av)) == NULL)
    return (-1);
  if (add_server_socket(srv->sockets, fd, srv->args->port) == -1
      || add_stdin(srv->sockets, STDIN_FILENO) == -1)
    return (-1);
  if (!create_map(srv->args, &srv->map))
    return (-1);
  if (setup_team(srv) == -1)
    return (-1);
  return (0);
}

static void	cleanup(t_server *srv)
{
  delete_param(srv->args);
  delete_map(&srv->map);
}

int		main(int ac, char **av)
{
  t_server	srv;

  srand(time(0));
  signal(SIGINT, sigHandler);
  if (init(&srv, ac, av) == -1)
    return (EXIT_FAILURE);
  if (srv.map.x >= 25)
    fprintf(stderr, "Cannot load Graphics: x >= 25\n");
  if (srv.map.x < 25 && srv.args->i
      && pthread_create(&g_ui_thread, NULL, loop, &srv))
    return (EXIT_FAILURE);
  if (handle_clients(&srv) == -1)
    return (EXIT_FAILURE);
  if (srv.map.x < 25 &&
      srv.args->i && pthread_cancel(g_ui_thread) != 0)
    return (EXIT_FAILURE);
  cleanup(&srv);
  return (EXIT_SUCCESS);
}
