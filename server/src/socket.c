/*
** socket.c for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/src
** 
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
** 
** Started on  Wed Jun 08 18:54:00 2016 Loik Gaonach
** Last update Wed Jun 08 18:54:00 2016 Loik Gaonach
*/

#include <stdio.h>
#include <unistd.h>
#include "socket.h"

int			create_socket(void)
{
  struct protoent	*pe;
  int			fd;

  if ((pe = getprotobyname("TCP")) == NULL)
    {
      fprintf(stderr, "Failed to get protocol name\n");
      return (-1);
    }
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    {
      perror("create_socket:socket");
      return (-1);
    }
  return (fd);
}

int	bind_socket(int fd, struct sockaddr_in *s_in)
{
  int	optval;

  if (bind(fd, (const struct sockaddr *) s_in, sizeof(*s_in)) == -1)
    {
      perror("bind_socket:bind");
      return (-1);
    }
  optval = 1;
  if (setsockopt(fd, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR),
		 &optval, sizeof(optval)) == -1)
    {
      perror("bind_socket:setsockopt");
      return (-1);
    }
  return (0);
}

int	listen_socket(int fd, int port)
{
  if (listen(fd, port) == -1)
    {
      perror("listen_socket:listen");
      return (-1);
    }
  return (0);
}
