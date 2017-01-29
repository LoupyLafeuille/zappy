/*
** server.h for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/include
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Tue Jun 07 19:28:40 2016 Loik Gaonach
** Last update Sun Jun 26 11:38:53 2016 Sylviane Tran
*/

#ifndef SERVER_H_
# define SERVER_H_

# include "socket.h"
# include "args.h"
# include "map.h"

typedef struct	s_server
{
  t_socket	sockets[FD_SETSIZE];
  t_param	*args;
  t_map		map;
  t_dllc	*team;
  int		port;
}		t_server;

void		add_responce(t_dllc *list, char *res);
void		*loop(void *srv);
int		game_run(t_server *srv);
int		handle_clients(t_server *srv);

double		client_handler(t_server *srv, int fd);
void		stdin_handler(t_server *srv, int fd);

#endif /* !SERVER_H_ */
