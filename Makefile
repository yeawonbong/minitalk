# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/30 02:13:31 by ybong             #+#    #+#              #
#    Updated: 2022/01/26 14:22:43 by ybong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = bash

SRCS = minitalk.c\
server.c\
client.c

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)

LIB = libft.a
LIB_DIR = ./include/libft
MINITALK = minitalk.o
SERVER = server
CLIENT = client

all : $(SERVER) $(CLIENT)

$(SERVER) : $(OBJS)
	@echo -n "Assembling [$@]... "
	@$(CC) $(CFLAGS) -o $@ $(MINITALK) $(SERVER).o $(LIB_DIR)/$(LIB)
	@echo "✔"

$(CLIENT) : $(OBJS)
	@echo -n "Assembling [$@]... "
	@$(CC) $(CFLAGS) -o $@ $(MINITALK) $(CLIENT).o $(LIB_DIR)/$(LIB)
	@echo "✔"

$(OBJS) : $(SRCS)
	@echo -n "Compiling... "
	@make -C $(LIB_DIR)
	@$(CC) $(CFLAGS) -c $(SRCS)
	@echo "✔"


fclean : clean
	@echo -n "Cleaning all... "
	@make fclean -C $(LIB_DIR)
	@rm -f $(SERVER) $(CLIENT)
	@echo "✔"

clean :
	@echo -n "Cleaning obj files... "
	@make clean -C $(LIB_DIR)
	@rm -rf $(OBJS)
	@echo "✔"

re : fclean all

.PHONY : all clean fclean re