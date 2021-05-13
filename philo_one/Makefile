NAME	= philo_one
SRC		= main.c utils.c init.c routine.c
OBJ		= ${addprefix ${OBJ_DIR}, ${SRC:.c=.o}}
OBJ_DIR	= objs/
CC		= gcc
CFLAGS	= -Wall -Wextra# -Werror -fsanitize=address -g

${OBJ_DIR}%.o:	srcs/%.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME}:		${OBJ_DIR} ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o $@ -pthread

${OBJ_DIR}:
	mkdir -p ${OBJ_DIR}

all:			${NAME}

clean:
	rm -rf ${OBJ_DIR}

fclean:			clean
	rm -rf ${NAME}

re:				fclean all

.PHONY:	all clean fclean re
