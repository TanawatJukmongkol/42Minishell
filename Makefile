# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/19 06:32:57 by tjukmong          #+#    #+#              #
#    Updated: 2023/08/19 02:34:21 by tponutha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Prgram Name
NAME		= minishell

# Complier Properties
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -O3
RM			= rm -f

# Man Source
MAN_DIR			= ./src_share
MAN_HEADER		= ./minishell.h ./libminishell.h
SRC_MAN			= minishell.c
SRCS_MAN		= ${addprefix ${MAN_DIR},${SRC_MAN}}

# Pun Source
PUN_DIR		= ./src_pun/
PUN_HEADER	= ${addprefix ${PUN_DIR},pun.h}
SRC_PUN		= 
SRCS_PUN	= ${addprefix ${PUN_DIR},${SRC_PUN}}

# Tun Source
TUN_DIR		= ./src_tun/
TUN_HEADER	= ${addprefix ${TUN_DIR},tun.h}
SRC_TUN		= 
SRCS_TUN	= ${addprefix ${TUN_DIR},${SRC_TUN}}

# Library Flag & directory
LIBFT_DIR	= ./libft/
LIBINCFLAG	= -L$(LIBFT_DIR)
LIBFLAG		= -lft -lreadline

# Object
HEADER		= $(MAN_HEADER) $(PUN_HEADER) $(TUN_HEADER)
SRC			= $(SRC_MAN) $(SRC_PUN) $(SRC_TUN)
OBJ			= ${SRC:.c=.o}

# Build Rule
%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^

# Main Rule
all: library ${NAME}

library:
	make -C $(LIBFT_DIR)

${NAME}: ${OBJ} $(HEADER)
	$(CC) $(CFLAGS) ${OBJ} $(LIBINCFLAG) $(LIBFLAG) -o ${NAME}

clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) ${NAME}

re: fclean all

# Additional Rule
norm:
	make -C $(LIBFT_DIR) norm
	@norminette -R CheckForbiddenSourceHeader $(SRC) $(HEADER)

# bonus: library ${BUILD_DIR} ${OBJ_BONUS}
# 	$(CC) ${OBJ_BONUS} ${wildcard ${LIB_DIR}/*/*.a} -o ${NAME} $(CFLAGS)

.PHONY:	all library clean fclean re norm
