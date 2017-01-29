##
## Makefile for Makefile in /home/ayasch_d/rendu/Tek2/System-Unix/PSU_2015_zappy/client
##
## Made by Dan Ayasch
## Login   <ayasch_d@epitech.net>
##
## Started on  Wed Jun  8 16:49:20 2016 Dan Ayasch
## Last update Sat Jun 25 21:55:24 2016 julien
##

NAME		= ../zappy_ai

CXX		= g++ -std=c++11

CXXFLAGS	+= -Wall -Wextra

CPPFLAGS	+= -I include -I lib/include/

LDLIBS		+= -l jsoncpp -lssl -lcrypto

SRC_DIR		= ./src

SRC_EXT		= cpp

SRCS		= $(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))

OBJS		= $(SRCS:.cpp=.o)

RM		= rm -rf

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) -o $(NAME) $(OBJS) $(LDLIBS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)
		$(RM) ../$(NAME)

re:		fclean all

.PHONY:		all clean fclean re
