SRC = server.c\
client.c

CC = gcc
CFLAGS =
AR = ar rcs
NAME = libft.a
OBJ = $(SRC:.c=.o)

SERVER = server
CLIENT = client

all : sv cl

sv : $(SERVER)

$(SERVER) : 
	$(CC) $(CFLAGS) -o $@ server.c libft.a

cl : $(CLIENT)

$(CLIENT) :
	$(CC) $(CFLAGS) -o $@ client.c libft.a

fclean :
	rm -f server client
re : fclean all