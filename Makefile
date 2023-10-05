
NAME		= minishell

# Shared sources
SRCS		= minishell.c \
				ft_clear_env.c \
				ft_editenv.c \
				ft_exit.c \
				ft_getcwd.c \
				ft_getenv.c \
				ft_initenv.c \
				ft_readline.c \
				ft_realpath.c \
				ft_setenv.c \
				ft_unsetenv.c \
				ft_init_main.c \
				ft_chdir.c

HEADERS		= libminishell.h \
				minishell.h

# Contributers (PUN)
SRCS_PUN	= ft_token.c \
				ft_token_consume.c \
				ft_tokenfree.c \
				get_next_quote.c \
				lexer.c \
				lexer_stage1.c \
				lexer_stage2_1.c \
				lexer_stage2_2.c \
				lexer_stage3.c \
				lexer_stage4.c \
				parser.c

HEADERS_PUN	= pun.h

# Contributers (TUN)
SRCS_TUN	= tun_builtin.c \
				tun_child.c \
				tun_exit.c \
				tun_file.c \
				tun_fork.c \
				tun_get_argv.c \
				tun_get_file.c \
				tun_init.c \
				tun_parent.c \
				tun_pipe.c \
				tun_split_token.c \
				tun_exeve.c

HEADERS_TUN	= tun.h


SRC_DIR		= ./src
SRC_DIR_PUN	= ./pun
SRC_DIR_TUN	= ./tun
LIB_DIR		= ./libft
BUILD_DIR	= ./build

CC			= cc
CFLAGS		= -g -Wall -Werror -Wextra

INCLUDE_OBJ_LINUX	= 
INCLUDE_SRC_LINUX	= 

INCLUDE_OBJ_OSX		= -I/usr/local/opt/readline/include
INCLUDE_SRC_OSX		= -L/usr/local/opt/readline/lib

UNAME_S		= $(shell uname -s)

INCLUDE_OBJ_SHARE	= ${addprefix -I,${LIB_DIR}}
INCLUDE_SRC_SHARE	= ${addprefix -L,${LIB_DIR}} \
						-l:libft.a \
						-lreadline

ifeq ($(UNAME_S), Linux)
INCLUDE_OBJ = $(INCLUDE_OBJ_LINUX) $(INCLUDE_OBJ_SHARE)
INCLUDE_SRC = $(INCLUDE_OBJ_LINUX) $(INCLUDE_SRC_SHARE)

else
INCLUDE_OBJ = $(INCLUDE_OBJ_OSX) $(INCLUDE_OBJ_SHARE)
INCLUDE_SRC = $(INCLUDE_OBJ_OSX) $(INCLUDE_SRC_SHARE)
endif

SRC			= ${addprefix ${BUILD_DIR}/,${SRCS}} \
				${addprefix ${BUILD_DIR}/,${SRCS_PUN}} \
				${addprefix ${BUILD_DIR}/,${SRCS_TUN}}
HEADER		= ${addprefix ${SRC_DIR}/,${HEADERS}} \
				${addprefix ${SRC_DIR_PUN}/,${HEADERS_PUN}} \
				${addprefix ${SRC_DIR_TUN}/,${HEADERS_TUN}}
OBJ			= ${SRC:.c=.o}
UNAME_S		= $(shell uname -s)

all: lib ${BUILD_DIR} ${NAME}

${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

${BUILD_DIR}/%.o:${SRC_DIR}/%.c
	$(CC) $(CFLAGS) ${INCLUDE_OBJ} -c -o $@ $^

${BUILD_DIR}/%.o:${SRC_DIR_PUN}/%.c
	$(CC) $(CFLAGS) ${INCLUDE_OBJ} -c -o $@ $^

${BUILD_DIR}/%.o:${SRC_DIR_TUN}/%.c
	$(CC) $(CFLAGS) ${INCLUDE_OBJ} -c -o $@ $^

${NAME}:	${OBJ} ${HEADER}
	$(CC) $(CFLAGS) ${OBJ} ${INCLUDE_SRC} -o ${NAME}

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
	rm -rf $(BUILD_DIR)

fclean: clean lib-fclean
	rm -f ${NAME}

re: fclean all

norm:	lib-norm
	@norminette -R CheckForbiddenSourceHeader $(SRC) $(HEADER)

.PHONY: all lib clean fclean re

