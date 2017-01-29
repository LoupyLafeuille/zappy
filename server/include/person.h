/*
** person.h for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/include
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Wed Jun 15 00:34:24 2016 Loik Gaonach
** Last update Sun Jun 26 11:37:50 2016 Sylviane Tran
*/

#ifndef PERSON_H_
# define PERSON_H_

# include <sys/time.h>
# include "dllc.h"

# define DEFAULT_LIFE		1260
# define DEFAULT_ORIENTATION	(rand() % 4)
# define DEFAULT_LEVEL		1
# define DEFAULT_FOOD		10

typedef enum		DIRECTION
{
  UP,
  RIGHT,
  DOWN,
  LEFT
}			e_dir;

typedef struct		s_person
{
  e_dir			orientation;
  int			lvl;
  int			life;
  int			x;
  int			y;
  int			items[7];
  char			*team;
  struct timeval	cycle;
  int			fd;
}			t_person;

t_person		*create_person(int x, int y, char *team, int fd);
void			delete_person(t_person *pers);

#endif /* !PERSON_H_ */
