/*
** tab_command.h for  in /home/clairegizard/PSU/PSU_2015_zappy/server/include
**
** Made by ClaireGizard
** Login   <gizard_a@epitech.net>
**
** Started on  Thu Jun  9 09:40:22 2016 ClaireGizard
** Last update Sun Jun 26 11:40:40 2016 Sylviane Tran
*/

#ifndef TAB_COMMAND_H_
# define TAB_COMMAND_H_

#include <stdlib.h>
#include <time.h>
#include "server.h"
#include "map.h"

typedef	struct	s_command
{
  int		(*fct)(t_server *srv, int fd);
  char		*str;
  int		delay;
}		t_command;

typedef struct	s_move
{
  e_dir		dir;
  void		(*fct)(const t_map *map, t_person *pers);
}		t_move;

typedef struct	s_send
{
  e_dir		dir;
  int		(*fct)(t_server *srv, t_person *pers);
}		t_send;

typedef struct	s_pos
{
  int		x;
  int		y;
  int		xc;
  int		yc;
}		t_pos;

typedef struct	s_formula
{
  int		player;
  int		l;
  int		d;
  int		s;
  int		m;
  int		p;
  int		t;
}		t_formula;

extern t_send		g_send[];
extern t_move		g_move[];
extern t_command	g_tab[];

void		expulse(t_person *person, t_server *srv, e_dir direct);
int		send_right(t_server *srv, t_person *person);
int		send_left(t_server *srv, t_person *person);
int		send_up(t_server *srv, t_person *person);
int		send_down(t_server *srv, t_person *person);
char		*get_obj(int i);
int		check_perso_pose(t_person *person, char *buf);
int		check_perso(t_person *person, char *buf);
int		check_inventaire_pose(t_server *srv, char *buf, int fd);
int		check_inventaire(char *buf, t_server *srv, int fd);
int		avance_cmd(t_server *srv, int fd);
int		droite_cmd(t_server *srv, int fd);
int		gauche_cmd(t_server *srv, int fd);
int		voir_cmd(t_server *srv, int fd);
int		inventaire_cmd(t_server *srv, int fd);
int		prend_obj_cmd(t_server *srv, int fd);
int		pose_obj_cmd(t_server *srv, int fd);
int		expulse_cmd(t_server *srv, int fd);
int		broadcast_texte_cmd(t_server *srv, int fd);
int		incantation_cmd(t_server *srv, int fd);
int		fork_cmd(t_server *srv, int fd);
int		connect_nbr_cmd(t_server *srv, int fd);

int		check_incant(t_server *srv, int fd, int f);

void		team_name_cmd(const char *cmd, t_server *srv, int fd);
void		move_up(const t_map *map, t_person *pers);
void		move_down(const t_map *map, t_person *pers);
void		move_left(const t_map *map, t_person *pers);
void		move_right(const t_map *map, t_person *pers);

#endif /* TAB_COMMAND_H_ */
