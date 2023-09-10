# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/19 06:32:57 by tjukmong          #+#    #+#              #
#    Updated: 2023/09/09 21:34:31 by tponutha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Prgram Name
NAME			= minishell

# Complier Properties
CC				= cc
CFLAGS			= -Wall -Werror -Wextra -O3 -g
RM				= rm -f

# OS Checking
UNAME = $(shell uname -s)

# Man Source
MAN_DIR			= ./src_share/
MAN_HEADER		= ${addprefix ${MAN_DIR},minishell.h}
SRC_MAN			=	minishell.c
SRCS_MAN		= ${addprefix ${MAN_DIR},${SRC_MAN}}

# Share Source
SHARE_DIR		= ./libminishell/
SHARE_HEADER	= ${addprefix ${SHARE_DIR},libminishell.h}
SRC_SHARE_MAC	=	ft_signal_mac.c
SRC_SHARE_LINUX	=	ft_signal_linux.c
SRC_SHARE		= 	ft_chdir.c \
					ft_exit.c \
					ft_genenv.c \
					ft_getenv.c \
					ft_getcwd.c \
					ft_initenv.c \
					ft_readline.c \
					ft_realpath.c \
					ft_setenv.c \
					ft_token_consume.c \
					ft_token.c \
					ft_tokenfree.c \
					ft_unsetenv.c \
					get_next_quote.c \
ifeq ($(UNAME), Linux)
	SRC_SHARE_FINAL	= ${SRC_SHARE} ${SRC_SHARE_LINUX}
else
	SRC_SHARE_FINAL	= ${SRC_SHARE} ${SRC_SHARE_MAC}
SRCS_SHARE		= ${addprefix ${SHARE_DIR},${SRC_SHARE_FINAL}}

# Pun Source
PUN_DIR			= ./src_pun/
PUN_HEADER		= ${addprefix ${PUN_DIR},pun.h}
SRC_PUN			= 
SRCS_PUN		= ${addprefix ${PUN_DIR},${SRC_PUN}}

# Tun Source
TUN_DIR			= ./src_tun/
TUN_HEADER		= ${addprefix ${TUN_DIR},tun.h}
SRC_TUN			=	tun_builtin.c \
					tun_child.c \
					tun_exit.c \
					tun_init.c \
SRCS_TUN		= ${addprefix ${TUN_DIR},${SRC_TUN}}

# Library Flag & directory
LIBFT_DIR		= ./libft/
LIBINCFLAG		= -L$(LIBFT_DIR)
LIBFLAG			= -lft -lreadline

# Object
HEADER			= ${MAN_HEADER} ${SHARE_DIR} ${PUN_HEADER} ${TUN_HEADER}
SRC				= ${SRC_MAN} ${SRC_SHARE} ${SRC_PUN} ${SRC_TUN}
OBJ				= ${SRC:.c=.o}

# Build Rule
${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

${BUILD_DIR}/%.o:${SRC_DIR}/%.c
	$(CC) $(CFLAGS) ${INCLUDE_OBJ} -c -o $@ $^ 

# Main Rule
all: lib ${BUILD_DIR} ${NAME}

lib:
	make -C $(LIBFT_DIR)

lib-clean:
	make -C $(LIBFT_DIR) clean

lib-fclean:
	make -C $(LIBFT_DIR) fclean

${NAME}: ${OBJ} ${HEADER}
	$(CC) $(CFLAGS) ${OBJ} $(LIBINCFLAG) $(LIBFLAG) -o ${NAME}

clean:	lib-clean
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJ)

fclean: clean lib-fclean
	$(RM) ${NAME}

re: fclean all

# Additional Rule
lib-norm:
	make -C $(LIBFT_DIR) norm

norm:	lib-norm
	@norminette -R CheckForbiddenSourceHeader $(SRC) $(HEADER)

# bonus: library ${BUILD_DIR} ${OBJ_BONUS}
# 	$(CC) ${OBJ_BONUS} ${wildcard ${LIB_DIR}/*/*.a} -o ${NAME} $(CFLAGS)

.PHONY:	all lib lib-clean lib-fclean lib-norm clean fclean re norm
