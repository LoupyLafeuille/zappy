/*
** dllc.h for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/include
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Wed Jun 08 18:55:48 2016 Loik Gaonach
** Last update Sun Jun 26 21:55:47 2016 julien
*/

#ifndef DLLC_H_
# define  DLLC_H_

# include <stdlib.h>

# define MAX_SIZE_INVENTAIRE	4096

typedef struct	s_dllc
{
  void		*data;
  struct s_dllc	*nxt;
  struct s_dllc	*prv;
}		t_dllc;

t_dllc	*create_dllc();
t_dllc	*get_first_dllc(t_dllc *list);
t_dllc	*get_last_dllc(t_dllc *list);
int	dump_dllc(t_dllc *list);
int	delete_dllc(t_dllc **list);
int	put_bot_dllc(t_dllc *elem, void *data);
int	put_top_dllc(t_dllc *elem, void *data);
t_dllc	*delete_elem_dllc(t_dllc *elem);
int	len_dllc(t_dllc *list);

#endif /* ! DLLC_H_ */
