# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/19 06:32:57 by tjukmong          #+#    #+#              #
#    Updated: 2023/09/05 14:09:10 by Tanawat J.       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
SRCS		= minishell.c
LIBS		= libminishell libft # liblifetime libminishell

SRC_DIR		= ./src
LIB_DIR		= ./lib
BUILD_DIR	= ./build

CC			= gcc
CFLAGS		= -g -Wall -Werror -Wextra
INCLUDE_OBJ	= ${addprefix -I,${LIBS_DIR}}
INCLUDE_SRC	= ${addprefix -L,${LIBS_DIR}} \
			  -lreadline \
			  -l:libminishell.a
			  # -l:libft.a \
			  -l:libminishell.a

SRC			= ${addprefix ${BUILD_DIR}/,${SRCS}}
LIBS_DIR	= ${addprefix ${LIB_DIR}/,${LIBS}}
OBJ			= ${SRC:.c=.o}

all: lib ${BUILD_DIR} ${NAME}

lib:
	make -C ${LIB_DIR}/libft
	make -C ${LIB_DIR}/liblifetime
	make -C ${LIB_DIR}/libminishell

lib-fclean:
	make fclean -C ${LIB_DIR}/libft
	make fclean -C ${LIB_DIR}/liblifetime
	make fclean -C ${LIB_DIR}/libminishell

${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

${BUILD_DIR}/%.o:${SRC_DIR}/%.c
	$(CC) ${INCLUDE_OBJ} -c -o $@ $^ $(CFLAGS)

${NAME}: ${OBJ}
	$(CC) ${OBJ} ${INCLUDE_SRC} -o ${NAME} $(CFLAGS)

clean:
	rm -rf ${BUILD_DIR}

fclean: lib-fclean clean
	rm -f ${NAME}

re: fclean all

.PHONY: all lib clean fclean re

