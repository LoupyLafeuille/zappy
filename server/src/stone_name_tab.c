/*
** stone_name_tab.c for zappy in /home/loupy/Rendu/PSU_2015_zappy/server/src
**
** Made by
** Login   <loupy@epitech.net>
**
** Started on  Wed Jun 22 15:26:33 2016
** Last update Thu Jun 23 17:21:41 2016 Sylviane Tran
*/

#include <unistd.h>

char		*get_obj(int i)
{
  static char	*tab[] = {"linemate", "deraumere",
			  "sibur", "mendiane", "phiras",
			  "thystame", "nourriture", "oeuf", NULL};

  return (tab[i]);
}
