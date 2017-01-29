/*
** request.h for zappy in /home/pumpkin/Desktop/queue
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Mon Jun 13 23:18:37 2016 Loik Gaonach
** Last update Sun Jun 26 11:38:38 2016 Sylviane Tran
*/

#ifndef REQUEST_H_
# define REQUEST_H_

# include <sys/time.h>
# include "dllc.h"

typedef struct		s_req
{
  char			*msg;
  struct timeval	start;
  int			delay;
  char			started;
}			t_req;

typedef struct		s_req_manager
{
  t_dllc		*list;
  char			*tmp;
}			t_req_manager;

t_req		*create_request(const char *msg, size_t len);
void		delete_request(t_req *req);
int		push_request(t_dllc *list, const char *msg, size_t len);
t_req		*pop_request(t_dllc *list);
t_req		*get_request(t_dllc *list);

#endif /* !REQUEST_H_ */
