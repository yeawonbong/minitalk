SRCS = server.c\
client.c

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
NAME = minitalk.a
OBJS = $(SRCS:.c=.o)

LIB = libft.a
LIB_DIR = ./include/libft
SERVER = server
CLIENT = client

all : $(SERVER) $(CLIENT)

$(SERVER) : $(NAME)
	$(CC) $(CFLAGS) -o $@ $(NAME)

$(CLIENT) : $(NAME)
	$(CC) $(CFLAGS) -o $@ $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIB_DIR)
	@cp $(LIB_DIR)/$(LIB) $@
	$(AR) $@ $(OBJS)

$(OBJS) : $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)


fclean : clean
	@make fclean -C $(LIB_DIR)
	rm -f $(LIB) $(NAME)
	rm -f $(SERVER) $(CLIENT)

clean :
	@make clean -C $(LIB_DIR)
	rm -rf $(OBJS)

re : fclean all

.PHONY : all clean fclean re