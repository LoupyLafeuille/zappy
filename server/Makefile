##
## Makefile for zappy in /home/pumpkin/Epitech/PSU_2015_zappy/server
##
## Made by Loik Gaonach
## Login   <gaonac_l@epitech.net>
##
## Started on  Wed Jun 08 18:53:17 2016 Loik Gaonach
## Last update Sun Jun 26 14:02:27 2016 Sylviane Tran
##

NAME		=	../zappy_server

RM              =       rm -f

CC              =       gcc

CFLAGS          +=      -W -Werror -Wextra -Wall -I./include

LDFLAGS         +=	-lSDL -ldl -lSDL_image -lSDL_ttf  -lSDL_mixer -pthread -lm

SRC             =       src/main.c \
			src/socket.c \
			src/socket_manager.c \
			src/handle_client.c \
			src/socket_io.c	\
			src/param.c \
			src/res.c \
			src/args.c \
			src/see_cmd.c \
			src/init_nbr.c \
			src/loop.c \
			src/request_handler.c \
			src/tab_command.c \
			src/move.c \
			src/movement.c \
			src/stone_name_tab.c \
			src/command.c \
			src/person_utils.c \
			src/suite_command.c \
			src/map.c \
			src/sound.c \
			src/request.c \
			src/team_cmd.c \
			src/check.c \
			src/team.c \
			src/send_pos.c \
			src/expulse.c \
			src/person.c \
			src/dllc.c \
			src/game.c \
			src/egg.c \
			src/dllc2.c \
			src/incantation_cmd.c \
			src/draw_map.c \
			src/time_utils.c \
			src/print_data.c \
			src/init_img.c \
			src/init_perso.c \
			src/socket_utils.c \
			src/set_key.c \
			src/init_music.c \
			src/free_item.c \
			src/print.c

OBJ             =       $(SRC:.c=.o)

all             :       $(NAME)

$(NAME)         :       $(OBJ)
			$(CC)  -o $(NAME) $(OBJ) $(LDFLAGS)

clean           :
			$(RM) $(OBJ)

fclean          :       clean
			$(RM) $(NAME)
			$(RM) ../$(NAME)

re              :       fclean all

.PHONY          :       all flcean re
