/*
** socket_utils.c for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/src
** 
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
** 
** Started on  Wed Jun 15 20:27:50 2016 Loik Gaonach
** Last update Wed Jun 15 20:27:50 2016 Loik Gaonach
*/

#include "server.h"
#include "person.h"

t_socket	*find_person_socket(t_socket socks[], t_person *pers)
{
  int		i;

  i = 0;
  while (i < FD_SETSIZE)
    {
      if (socks[i].type == FD_CLIENT && socks[i].person == pers)
	return (&socks[i]);
      ++i;
    }
  return (NULL);
}
