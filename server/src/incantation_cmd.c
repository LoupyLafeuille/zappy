/*
** incantation_cmd.c for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Sat Jun 18 06:18:12 2016 Loik Gaonach
** Last update Sun Jun 26 03:18:54 2016 Sylviane Tran
*/

#define _GNU_SOURCE
#include <stdio.h>
#include "tab_command.h"
#include "game.h"
#include "person_utils.h"

static const t_formula	g_inc[] = {
    {0, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 1, 2, 2, 2, 2, 1},
};

static int		check_users(t_dllc *list, int lvl)
{
  t_dllc		*tmp;
  t_person		*pers;

  tmp = list->nxt;
  while (tmp != list)
    {
      pers = tmp->data;
      if (pers->lvl != lvl)
	return (0);
      tmp = tmp->nxt;
    }
  return (1);
}

int			check_incant(t_server *srv, int fd, int f)
{
  t_person		*pers;
  int			lvl;
  t_case		c;

  pers = srv->sockets[fd].person;
  lvl = pers->lvl;
  c = srv->map.map[pers->y][pers->x];
  if (check_users(c.persons, lvl)
      && len_dllc(c.persons) == g_inc[lvl].player
      && c.items[LINEMATE] == g_inc[lvl].l
      && c.items[DERAUMERE] == g_inc[lvl].d
      && c.items[SIBUR] == g_inc[lvl].s
      && c.items[MEDIANE] == g_inc[lvl].m
      && c.items[PHIRAS] == g_inc[lvl].p
      && c.items[THYSTANE] == g_inc[lvl].t)
    {
      srv->map.map[pers->y][pers->x].incant = 1;
      if (f)
	broadcast_to_person(srv, srv->map.map[pers->y][pers->x].persons,
			    "elevation en cours\n");
      return (1);
    }
  return (0);
}

static void		update_users(t_dllc *list)
{
  t_dllc		*tmp;

  tmp = list->nxt;
  while (tmp != list)
    {
      ((t_person *)tmp->data)->lvl++;
      tmp = tmp->nxt;
    }
}

int			incantation_cmd(t_server *srv, int fd)
{
  t_person		*pers;
  char			*res;

  pers = srv->sockets[fd].person;
  if (pers->lvl != MAX_LVL)
    {
      if (check_incant(srv, fd, 0))
	{
	  if (asprintf(&res, "niveau actuel : %d\n", pers->lvl + 1) != -1)
	    {
	      broadcast_to_person(srv, srv->map.map[pers->y][pers->x].persons,
				  res);
	      free(res);
	    }
	  update_users(srv->map.map[pers->y][pers->x].persons);
	  srv->map.map[pers->y][pers->x].incant = 0;
	  return (0);
	}
      else
	srv->map.map[pers->y][pers->x].incant = 0;
    }
  add_responce(srv->sockets[fd].write_buff, "ko\n");
  return (0);
}
