/*
** socket_io.c for myirc in /home/pumpkin/Desktop/PSU_2015_myirc/src
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Fri May 27 19:00:11 2016 Loik Gaonach
** Last update Sun Jun 26 22:05:35 2016 julien
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include "server.h"
#include "request.h"

char		*read_socket(int fd)
{
  int		len;
  int		ret;
  char		*tmp;

  len = 0;
  if (ioctl(fd, FIONREAD, &len) == -1)
    {
      perror("read_socket:ioctl");
      return (NULL);
    }
  if (len > 0)
    {
      if ((tmp = malloc(sizeof(char) * (len + 1))) == NULL)
	return (NULL);
      memset(tmp, 0, len + 1);
      if ((ret = read(fd, tmp, len)) > 0)
	return (tmp);
      else if (ret == -1)
	{
	  if (tmp)
	    free(tmp);
	  perror("read");
	}
    }
  return (NULL);
}

int		server_read(t_socket sock[], int fd)
{
  int		client_fd;

  if ((client_fd = add_client_socket(sock, fd)))
    add_responce(sock[client_fd].write_buff, strdup("BIENVENUE\n"));
  return (0);
}

void		parse_request(t_socket *sock, char *buff)
{
  char		*next;
  char		end;

  end = 0;
  while (!end)
    {
      if ((next = strchr(buff, '\n')))
	{
	  push_request(sock->read_buff, buff, next - buff + 1);
	  buff = next + 1;
	}
      else
	{
	  push_request(sock->read_buff, buff, strlen(buff));
	  end = 1;
	}
    }
}

int		client_read(t_socket sock[], int fd)
{
  char		*tmp;

  if ((tmp = read_socket(fd)))
    {
      parse_request(&sock[fd], tmp);
      free(tmp);
      return (0);
    }
  return (-1);
}

int		client_write(t_socket sock[], int fd)
{
  t_res		*res;
  unsigned int	ret;

  if (len_dllc(sock[fd].write_buff) > 0)
    {
      res = sock[fd].write_buff->nxt->data;
      ret = write(fd, res->buff + res->i, strlen(res->buff));
      if (ret != strlen(res->buff) - res->i)
	res->i = ret;
      else
	{
	  free(res->buff);
	  free(res);
	  delete_elem_dllc(sock[fd].write_buff->nxt);
	}
    }
  return (0);
}
