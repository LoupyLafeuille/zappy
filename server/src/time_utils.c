/*
** time_utils.c for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/src
** 
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
** 
** Started on  Thu Jun 23 17:15:00 2016 Loik Gaonach
** Last update Thu Jun 23 17:15:00 2016 Loik Gaonach
*/

#include <stddef.h>
#include "time_utils.h"

unsigned long		diff_time_now(struct timeval *b)
{
  struct timeval	d;
  struct timeval	now;

  if (gettimeofday(&now, NULL) != -1)
    {
      timersub(&now, b, &d);
      return (1000000 * d.tv_sec + d.tv_usec);
    }
  return (0);
}
