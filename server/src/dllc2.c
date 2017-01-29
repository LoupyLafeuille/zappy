/*
** dllc2.c for  in /home/pumpkin/Epitech/PSU_2015_zappy/server/src
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Wed Jun 08 18:48:51 2016 Loik Gaonach
** Last update Sun Jun 26 03:16:28 2016 Sylviane Tran
*/

#include "dllc.h"

t_dllc		*delete_elem_dllc(t_dllc *elem)
{
  t_dllc	*next;

  next = elem->nxt;
  elem->prv->nxt = elem->nxt;
  elem->nxt->prv = elem->prv;
  free(elem);
  return (next);
}

t_dllc		*get_first_dllc(t_dllc *list)
{
  if (list->nxt != list)
    return (list->nxt);
  else
    return (NULL);
}

t_dllc		*get_last_dllc(t_dllc *list)
{
  if (list->prv != list)
    return (list->prv);
  else
    return (NULL);
}

int		len_dllc(t_dllc *list)
{
  t_dllc	*tmp;
  unsigned int	i;

  i = 0;
  tmp = list->nxt;
  while (tmp != list)
    {
      tmp = tmp->nxt;
      i++;
    }
  return (i);
}
