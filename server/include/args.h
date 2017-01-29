/*
** args.h for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server/include
**
** Made by Loik Gaonach
** Login   <gaonac_l@epitech.net>
**
** Started on  Wed Jun 08 18:56:05 2016 Loik Gaonach
** Last update Mon Jun 20 15:06:28 2016 ClaireGizard
*/

#ifndef _ARGS_H_
# define _ARGS_H_

# define	PORT		4242
# define	MAP_X		10
# define	MAP_Y		10
# define	NB_CLIENT	0
# define	DELAI		100
# define	DEFAULT_I	1

typedef struct	s_param
{
  int		port;
  int		x;
  int		y;
  int		nb_client;
  int		delai;
  char		**name;
  char		i;
}		t_param;

typedef struct	s_args
{
  char		*flag;
  int		(*set_param)
  (t_param *param, int ac, char **av, int *i);
}		t_args;

extern t_args	g_args_server[];

int		init_port(t_param *param, int ac, char **av, int *i);
int		init_x(t_param *param, int ac, char **av, int *i);
int		init_y(t_param *param, int ac, char **av, int *i);
int		init_nb_client(t_param *param, int ac, char **av, int *i);
int		init_delai(t_param *param, int ac, char **av, int *i);
int		init_name(t_param *param, int ac, char **av, int *i);
int		init_interface(t_param *param, int ac, char **av, int *i);

int		init_param(t_param *param);
int		init_name(t_param *param, int ac, char **av, int *i);

t_param		*get_param(int ac, char **av);

void		delete_param(t_param *param);

void		print_usage();

#endif /* !_ARGS_H_ */
