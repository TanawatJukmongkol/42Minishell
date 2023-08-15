# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/19 06:32:57 by tjukmong          #+#    #+#              #
#    Updated: 2023/08/16 06:07:30 by tponutha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Prgram Name
NAME		= minishell

# Complier Properties
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -O3 -lreadline
RM			= rm -f

# Source
SRCS		= minishell.c
HEADER		= ./minishell.h
SRC_PUN		= ./src_pun/
SRC_TUN		= ./src_tun/
SRC_DIR		= ${SRC_PUN} ${SRC_TUN}
LIBFT_DIR	= ./libft/
LIBMS_DIR	= ./libminishell/
BUILD_DIR	= ./build/

# Library Flag
LIBINCFLAG	= -L$(LIBFT_DIR) -L$(LIBMS_DIR)
LIBFLAG		= -lft -lminishell

# Object
SRC			= ${addprefix ${BUILD_DIR},${SRCS}}
SRC_BONUS	= ${addprefix ${BUILD_DIR},${SRCS_BONUS}}
OBJ			= ${SRC:.c=.o}
OBJ_BONUS	= ${SRC_BONUS:.c=.o}

# Main Rule
.PHONY:	all library clean fclean re

all: library ${BUILD_DIR} ${NAME}

library:
	make -C $(LIBFT_DIR)
	make -C $(LIBMS_DIR)

${NAME}: ${OBJ} $(HEADER)
	$(CC) $(CFLAGS) ${OBJ} $(LIBINCFLAG) $(LIBFLAG) -o ${NAME}

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(LIBMS_DIR) clean
	$(RM) $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	make -C $(LIBMS_DIR) fclean
	$(RM) ${NAME}

re: fclean all

${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

${BUILD_DIR}%.o:${SRC_DIR}%.c
	$(CC) $(CFLAGS) -c -o $@ $^



# bonus: library ${BUILD_DIR} ${OBJ_BONUS}
# 	$(CC) ${OBJ_BONUS} ${wildcard ${LIB_DIR}/*/*.a} -o ${NAME} $(CFLAGS)
