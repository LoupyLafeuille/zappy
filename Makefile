##
## Makefile for zappy in /home/pumpkin/Epitech/PSU_2015_zappy
##
## Made by Loik Gaonach
## Login   <gaonac_l@epitech.net>
##
## Started on  Wed Jun 08 18:53:02 2016 Loik Gaonach
## Last update Sun Jun 26 14:03:10 2016 Sylviane Tran
##

all		:
			make -C ./server
			make -C ./client

zappy_server	:
			make -C ./server

zappy_ai	:
			make -C ./client

clean		:
			make -C ./server clean
			make -C ./client clean

fclean		:	clean
			make -C ./server fclean
			make -C ./client fclean

re		:	fclean all

.PHONY		:	all fclean re
