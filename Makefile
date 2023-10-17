
NAME		= minishell

# Shared sources
SRCS_COMMON		= minishell.c \
				ft_clear_env.c \
				ft_clear_main.c \
				ft_tokenfree.c \
				ft_editenv.c \
				ft_sorttable.c \
				ft_dynamic_prompt.c \
				ft_getcwd.c \
				ft_getenv.c \
				ft_initenv.c \
				ft_readline.c \
				ft_realpath.c \
				ft_setenv.c \
				ft_unsetenv.c \
				ft_init_main.c \
				ft_chdir.c \

SRCS_LINUX		=	ft_signal_linux.c
SRCS_MAC		=	ft_signal_mac.c

HEADERS		= libminishell.h \
				minishell.h

# Contributers (PUN)
SRCS_PUN	= ft_token.c \
				ft_token_consume.c \
				get_next_quote.c \
				lexer.c \
				lexer_stage1.c \
				lexer_stage2_1.c \
				lexer_stage2_2.c \
				lexer_stage3.c \
				lexer_stage4.c \
				parser_utils.c \
				parser.c

HEADERS_PUN	= pun.h

# Contributers (TUN)

SRCS_TUN	= tun_builtin.c \
		  		tun_echo.c \
				tun_child.c \
				tun_builtin_exit.c \
				tun_process_exit.c \
				tun_file.c \
				tun_fork.c \
				tun_translate.c \
				tun_init.c \
				tun_parent.c \
				tun_pipe.c \
				tun_split_token.c \
				tun_exeve.c \
				tun_heredoc.c \
				tun_heredoc_utils.c \
				tun_perror.c \
				tun_redirect.c \
				tun_directory.c 

#HEADERS_TUN	= tun.h
# add  to define

SRC_DIR		= .
SRC_DIR_PUN	= .
SRC_DIR_TUN	= .
LIB_DIR		= ./libft
BUILD_DIR	= ./build

CC			= cc
CFLAGS		= -g -Wall -Werror -Wextra -D READLINE_LIBRARY=1# -fsanitize=address


INCLUDE_OBJ_LINUX	= 
INCLUDE_SRC_LINUX	= 

INCLUDE_OBJ_OSX		= -I/usr/local/Cellar/readline/8.2.1/include
INCLUDE_SRC_OSX		= -L/usr/local/Cellar/readline/8.2.1/lib

UNAME_S		= $(shell uname -s)

INCLUDE_OBJ_SHARE	= ${addprefix -I,${LIB_DIR}}
INCLUDE_SRC_SHARE	= ${INCLUDE_SRC_OSX} \
						${addprefix -L,${LIB_DIR}} \
						-lft \
						-lreadline

ifeq ($(UNAME_S), Linux)
INCLUDE_OBJ = $(INCLUDE_OBJ_LINUX) $(INCLUDE_OBJ_SHARE)
INCLUDE_SRC = $(INCLUDE_OBJ_LINUX) $(INCLUDE_SRC_SHARE)
SRCS = ${addprefix ${SRCS_COMMON}, ${SRCS_LINUX}}

else
INCLUDE_OBJ = $(INCLUDE_OBJ_OSX) $(INCLUDE_OBJ_SHARE)
INCLUDE_SRC = $(INCLUDE_OBJ_OSX) $(INCLUDE_SRC_SHARE)
SRCS = ${addprefix ${SRCS_COMMON}, ${SRCS_MAC}}
endif

SRC			= ${addprefix ${SRC_DIR}/,${SRCS}} \
				${addprefix ${SRC_DIR_PUN}/,${SRCS_PUN}} \
				${addprefix ${SRC_DIR_TUN}/,${SRCS_TUN}}
HEADER		= ${addprefix ${SRC_DIR}/,${HEADERS}} \
				${addprefix ${SRC_DIR_PUN}/,${HEADERS_PUN}} \
				${addprefix ${SRC_DIR_TUN}/,${HEADERS_TUN}}
OBJS		= ${addprefix ${BUILD_DIR}/,${SRCS}} \
				${addprefix ${BUILD_DIR}/,${SRCS_PUN}} \
				${addprefix ${BUILD_DIR}/,${SRCS_TUN}}
OBJ			= ${OBJS:.c=.o}

all: ${NAME}

build-create:
	mkdir -p ${BUILD_DIR}

${NAME}: lib build-create ${BUILD_DIR} ${HEADER} ${OBJ}
	$(CC) $(CFLAGS) ${OBJ} ${INCLUDE_SRC} -o ${NAME}

${BUILD_DIR}/%.o:${SRC_DIR}/%.c
	$(CC) $(CFLAGS) ${INCLUDE_OBJ} -c -o $@ $^

${BUILD_DIR}/%.o:${SRC_DIR_PUN}/%.c
	$(CC) $(CFLAGS) ${INCLUDE_OBJ} -c -o $@ $^

${BUILD_DIR}/%.o:${SRC_DIR_TUN}/%.c
	$(CC) $(CFLAGS) ${INCLUDE_OBJ} -c -o $@ $^

lib:
	@make -C $(LIB_DIR)

lib-clean:
	@make -C $(LIB_DIR) clean

lib-fclean:
	@make -C $(LIB_DIR) fclean

lib-re:
	@make -C $(LIB_DIR) re

lib-norm:
	@make -C $(LIB_DIR) norm

clean:	lib-clean
	rm -rf ${BUILD_DIR}

fclean: clean lib-fclean
	rm -f ${NAME}

re: fclean all

norm:	lib-norm
	@norminette -R CheckForbiddenSourceHeader $(SRC) $(HEADER)

.PHONY: all lib lib-clean lib-fclean lib-re lib-norm build-create clean fclean re
