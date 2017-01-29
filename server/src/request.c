/*
** request.c for zappy in /home/pumpkin/Desktop/queue
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Mon Jun 13 23:08:35 2016 Loik Gaonach
** Last update Sun Jun 26 22:06:21 2016 julien
*/

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "request.h"

t_req	*create_request(const char *msg, size_t len)
{
  t_req	*req;

  if ((req = malloc(sizeof(t_req))) == NULL)
    return (NULL);
  if ((req->msg = strndup(msg, len)) == NULL)
    {
      free(req);
      return (NULL);
    }
  req->started = 0;
  return (req);
}

void	delete_request(t_req *req)
{
  free(req->msg);
  free(req);
}

int	push_request(t_dllc *list, const char *msg, size_t len)
{
  t_req	*req;

  if (len_dllc(list))
    {
      req = list->prv->data;
      if (!strchr(req->msg, '\n'))
	{
	  if (!(req->msg = realloc(req->msg, strlen(req->msg) + 1 + len)))
	    return (-1);
	  strncat(req->msg, msg, len);
	  return (0);
	}
    }
  if (len_dllc(list) < 10)
    {
      if ((req = create_request(msg, len)) == NULL)
	return (-1);
      if (put_bot_dllc(list, req) == -1)
	return (-1);
    }
  return (0);
}

t_req	*get_request(t_dllc *list)
{
  t_req	*req;

  if (len_dllc(list))
    {
      req = list->nxt->data;
      if (strchr(req->msg, '\n'))
	return (req);
    }
  return (NULL);
}

t_req	*pop_request(t_dllc *list)
{
  t_req	*req;

  if ((req = get_request(list)))
    {
      delete_elem_dllc(list->nxt);
      return (req);
    }
  return (NULL);
}
