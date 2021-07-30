# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/30 02:13:31 by ybong             #+#    #+#              #
#    Updated: 2021/07/30 11:37:53 by ybong            ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

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
	$(CC) $(CFLAGS) -o $@ $(MINITALK) $(SERVER).o $(LIB_DIR)/$(LIB)

$(CLIENT) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(MINITALK) $(CLIENT).o $(LIB_DIR)/$(LIB)

$(OBJS) : $(SRCS)
	@make -C $(LIB_DIR)
	$(CC) $(CFLAGS) -c $(SRCS)


fclean : clean
	@make fclean -C $(LIB_DIR)
	rm -f $(SERVER) $(CLIENT)

clean :
	@make clean -C $(LIB_DIR)
	rm -rf $(OBJS)

re : fclean all

.PHONY : all clean fclean re