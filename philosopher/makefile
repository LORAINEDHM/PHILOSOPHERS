CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -Isrcs -fsanitize=address \

NAME		=	philo

SRCS		=	main.c fork.c libft.c threads.c messages.c\
				actions.c utils.c death.c\

OBJ			=	${addprefix srcs/, ${SRCS:.c=.o}}


all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -lpthread -o philo

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:			fclean all

.PHONY:		all fclean re