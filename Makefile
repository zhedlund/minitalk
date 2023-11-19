NAME 	= minitalk
SERVER	= server
CLIENT	= client

LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC_S = server.c
SRC_C = client.c

OBJ_S = $(SRC_S:.c=.o)
OBJ_C = $(SRC_C:.c=.o)

$(NAME):	$(SERVER) $(CLIENT)

all :		$(NAME)

$(LIBFT):
			make -C $(LIBFTDIR)

$(SERVER):	$(OBJ_S) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_S) -o $(SERVER) -L$(LIBFTDIR) -lft

$(CLIENT): $(OBJ_C) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_C) -o $(CLIENT) -L$(LIBFTDIR) -lft

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJ_S) $(OBJ_C)
			make -C $(LIBFTDIR) clean

fclean:		clean
			$(RM) $(CLIENT) $(SERVER)
			make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re