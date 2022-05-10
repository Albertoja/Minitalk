SRCS_CLIENT = client.c minitalk_utils.c

SRCS_SERVER = server.c minitalk_utils.c 

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

OBJS_SERVER = $(SRCS_SERVER:.c=.o)

NAME_CLIENT = client

NAME_SERVER = server

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

RM = rm -f

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME) : $(NAME_SERVER) $(NAME_CLIENT)

%.o: %.c
	@$(CC) $(CFLAGS) -c $? -o $(<:.c=.o)

$(NAME_SERVER): $(OBJS_SERVER)
	@$(CC) -o $(NAME_SERVER) $?

$(NAME_CLIENT): $(OBJS_CLIENT)
	@$(CC) -o $(NAME_CLIENT) $?

clean:
	@$(RM) $(OBJS_CLIENT) $(OBJS_SERVER)

fclean: clean
	@$(RM) $(NAME_SERVER) $(NAME_CLIENT)

re: fclean $(NAME_SERVER) $(NAME_CLIENT)

.PHONY: all clean fclean re