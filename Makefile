
NAME		= minishell

# Shared sources
SRCS		= minishell.c

# Contributers
SRCS_PUN	= ft_readline.c ft_chdir.c ft_realpath.c ft_getcwd.c \
				ft_initenv.c ft_token.c ft_token_consume.c \
				ft_tokenfree.c get_next_quote.c lexer.c \
				lexer_stage1.c lexer_stage2_1.c lexer_stage2_2.c \
				lexer_stage3.c lexer_stage4.c parser.c

SRCS_TUN	= 

LIBS		= libft

SRC_DIR		= ./src
SRC_DIR_PUN	= ./pun
SRC_DIR_TUN	= ./tun
LIB_DIR		= .
BUILD_DIR	= ./build

CC			= cc
CFLAGS		= -g -Wall -Werror -Wextra

INCLUDE_OBJ_LINUX	= 
INCLUDE_SRC_LINUX	= 

INCLUDE_OBJ_OSX		= -I/usr/local/opt/readline/include
INCLUDE_SRC_OSX		= -L/usr/local/opt/readline/lib

UNAME_S		= $(shell uname -s)

INCLUDE_OBJ_SHARE	= ${addprefix -I,${LIBS_DIR}}
INCLUDE_SRC_SHARE	= ${addprefix -L,${LIBS_DIR}} \
						-l:libft.a \
						-lreadline

ifeq ($(UNAME_S), Linux)
INCLUDE_OBJ = $(INCLUDE_OBJ_LINUX) $(INCLUDE_OBJ_SHARE)
INCLUDE_SRC = $(INCLUDE_OBJ_LINUX) $(INCLUDE_SRC_SHARE)

else
INCLUDE_OBJ = $(INCLUDE_OBJ_OSX) $(INCLUDE_OBJ_SHARE)
INCLUDE_SRC = $(INCLUDE_OBJ_OSX) $(INCLUDE_SRC_SHARE)
endif

SRC			= ${addprefix ${BUILD_DIR}/,${SRCS}}\
				${addprefix ${BUILD_DIR}/,${SRCS_PUN}}\
				${addprefix ${BUILD_DIR}/,${SRCS_TUN}}
LIBS_DIR	= ${addprefix ${LIB_DIR}/,${LIBS}}
OBJ			= ${SRC:.c=.o}
UNAME_S		= $(shell uname -s)

all: lib ${BUILD_DIR} ${NAME}

${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

${BUILD_DIR}/%.o:${SRC_DIR}/%.c
	$(CC) ${INCLUDE_OBJ} -c -o $@ $^ $(CFLAGS)

${BUILD_DIR}/%.o:${SRC_DIR_PUN}/%.c
	$(CC) ${INCLUDE_OBJ} -c -o $@ $^ $(CFLAGS)

${BUILD_DIR}/%.o:${SRC_DIR_TUN}/%.c
	$(CC) ${INCLUDE_OBJ} -c -o $@ $^ $(CFLAGS)

${NAME}:	${OBJ}
	$(CC) ${OBJ} ${INCLUDE_SRC} -o ${NAME} $(CFLAGS)

lib:
	make -C $(LIB_DIR)/libft

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all lib clean fclean re

