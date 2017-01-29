/*
** socket.h for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/include
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Tue Jun 07 19:29:29 2016 Loik Gaonach
** Last update Sun Jun 26 11:40:09 2016 Sylviane Tran
*/

#ifndef SOCKET_H_
# define SOCKET_H_

# include <netdb.h>
# include "dllc.h"
# include "person.h"

# define FD_FREE	0
# define FD_SERVER	1
# define FD_CLIENT	2
# define FD_DUMMY	3

typedef struct	s_socket	t_socket;

typedef int	(*t_func)(t_socket *sock, int fd);

struct		s_socket
{
  unsigned int	fd;
  char		type;
  t_func	read_func;
  t_func	write_func;
  t_dllc	*read_buff;
  t_dllc	*write_buff;
  t_person	*person;
  char		team;
};

typedef struct	s_res
{
  char		*buff;
  int		i;
}		t_res;
/*
** base socket func
*/
int		create_socket(void);
int		bind_socket(int fd, struct sockaddr_in *s_in);
int		listen_socket(int fd, int port);
/*
** socket managment
*/
int		add_server_socket(t_socket sock[], int fd, int port);
int		add_client_socket(t_socket sock[], int srv_fd);
int		delete_socket(t_socket sock[], int fd);
int		add_stdin(t_socket sock[], int fd);
/*
** socket io
*/
int		server_read(t_socket sock[], int fd);
int		client_read(t_socket sock[], int fd);
int		client_write(t_socket sock[], int fd);

t_socket	*find_person_socket(t_socket socks[], t_person *pers);

#endif /* !SOCKET_H_ */
