/*
** egg.h for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/include
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Sat Jun 18 04:04:34 2016 Loik Gaonach
** Last update Sun Jun 26 11:37:07 2016 Sylviane Tran
*/

#ifndef EGG_H_
# define EGG_H_

typedef struct	s_egg
{
  int		x;
  int		y;
}		t_egg;

t_egg		*create_egg(int x, int y);
void		delete_egg(t_egg *egg);

#endif /* !EGG_H_ */
