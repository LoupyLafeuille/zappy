/*
** res.c for myirc in /home/pumpkin/Epitech/PSU_2015_myirc/server_src
** 
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
** 
** Started on  Sun Jun 05 03:15:26 2016 Loik Gaonach
** Last update Sun Jun 05 03:15:26 2016 Loik Gaonach
*/

#include <string.h>
#include <stdlib.h>
#include "dllc.h"
#include "server.h"

void	add_responce(t_dllc *list, char *msg)
{
  t_res	*responce;

  if (msg == NULL)
    return ;
  if ((responce = malloc(sizeof(*responce))))
    {
      responce->buff = strdup(msg);
      responce->i = 0;
    }
  put_bot_dllc(list, responce);
}
