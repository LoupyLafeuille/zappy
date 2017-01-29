/*
** rbuff.h for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/include
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Wed Jun 08 18:55:35 2016 Loik Gaonach
** Last update Sun Jun 26 11:38:15 2016 Sylviane Tran
*/

#ifndef RINGBUFFER_H_
# define RINGBUFFER_H_

# define NEXT(i, len)	(((i + 1) >= len) ? 0 : i + 1)

typedef struct	s_rbuff
{
  char		*buff;
  int		len;
  int		start;
  int		end;
}		t_rbuff;

t_rbuff		*create_rbuff(int len);
void		delete_rbuff(t_rbuff *buff);
int		put_rbuff(t_rbuff *buff, char c);
int		pop_rbuff(t_rbuff *buff, char *c);
int		putstr_rbuff(t_rbuff *buff, char *str);
int		findcmd_rbuff(t_rbuff *buff);
char		*getcmd_rbuff(t_rbuff *buff);

#endif /* !RINGBUFFER */
