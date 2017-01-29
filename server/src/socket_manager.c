/*
** socket_manager.c for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/src
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Wed Jun 08 18:53:45 2016 Loik Gaonach
** Last update Sun Jun 26 03:24:17 2016 Sylviane Tran
*/

#include <unistd.h>
#include <stdio.h>
#include "socket.h"

int			add_server_socket(t_socket sock[], int fd, int port)
{
  struct sockaddr_in	s_in;

  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  s_in.sin_addr.s_addr = INADDR_ANY;
  if (bind_socket(fd, &s_in) == -1)
    {
      if (close(fd) == -1)
	perror("setup_socket:close");
      return (-1);
    }
  if (listen_socket(fd, port) == -1)
    {
      if (close(fd) == -1)
	perror("setup_socket:close2");
      return (-1);
    }
  sock[fd].type = FD_SERVER;
  sock[fd].read_func = server_read;
  return (0);
}

int			add_client_socket(t_socket sock[], int srv_fd)
{
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;
  int			fd;

  client_sin_len = sizeof(client_sin);
  if ((fd = accept(srv_fd, (struct sockaddr *)&client_sin,
		   &client_sin_len)) == -1)
    {
      perror("add_client_fd:accept");
      return (-1);
    }
  sock[fd].type = FD_CLIENT;
  sock[fd].read_func = client_read;
  sock[fd].write_func = client_write;
  sock[fd].fd = fd;
  if ((sock[fd].read_buff = create_dllc()) == NULL)
    return (-1);
  if ((sock[fd].write_buff = create_dllc()) == NULL)
    return (-1);
  sock[fd].team = 0;
  return (fd);
}

int		delete_socket(t_socket sock[], int fd)
{
  if (sock[fd].type != FD_DUMMY && close(fd) == -1)
    perror("delete_socket:close");
  if (sock[fd].read_buff)
    delete_dllc(&sock[fd].read_buff);
  sock[fd].read_buff = NULL;
  if (sock[fd].write_buff)
    delete_dllc(&sock[fd].write_buff);
  sock[fd].write_buff = NULL;
  sock[fd].read_func = NULL;
  sock[fd].write_func = NULL;
  sock[fd].type = FD_FREE;
  return (0);
}

int		add_stdin(t_socket sock[], int fd)
{
  sock[fd].type = FD_DUMMY;
  sock[fd].read_func = client_read;
  sock[fd].write_func = client_write;
  sock[fd].fd = fd;
  if ((sock[fd].read_buff = create_dllc()) == NULL)
    return (-1);
  return (0);
}
