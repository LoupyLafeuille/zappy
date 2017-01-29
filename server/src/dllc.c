/*
** dllc.c for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/src
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Wed Jun 08 18:49:30 2016 Loik Gaonach
** Last update Sun Jun 26 03:16:38 2016 Sylviane Tran
*/

#include <stdlib.h>
#include "dllc.h"

t_dllc		*create_dllc()
{
  t_dllc	*root;

  if ((root = malloc(sizeof(*root))) == NULL)
    return (NULL);
  else
    {
      root->nxt = root;
      root->prv = root;
      return (root);
    }
}

int		dump_dllc(t_dllc *list)
{
  t_dllc	*tmp;
  t_dllc	*follow;

  tmp = list->nxt;
  while (tmp != list)
    {
      follow = tmp->nxt;
      free(tmp);
      tmp = follow;
    }
  list->nxt = list;
  list->prv = list;
  return (0);
}

int		delete_dllc(t_dllc **list)
{
  dump_dllc(*list);
  free(*list);
  return (0);
}

int		put_bot_dllc(t_dllc *elem, void *data)
{
  t_dllc	*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (-1);
  else
    {
      new->data = data;
      new->prv = elem->prv;
      new->nxt = elem;
      elem->prv->nxt = new;
      elem->prv = new;
    }
  return (0);
}

int		put_top_dllc(t_dllc *elem, void *data)
{
  t_dllc	*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (-1);
  else
    {
      new->data = data;
      new->prv = elem;
      new->nxt = elem->nxt;
      elem->nxt->prv = new;
      elem->nxt = new;
    }
  return (0);
}
