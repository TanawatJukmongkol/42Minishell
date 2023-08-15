# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/27 21:14:32 by tjukmong          #+#    #+#              #
#    Updated: 2023/08/16 06:11:29 by tponutha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Static Libaray name.
NAME		= libminishell.a

# Header file include dirrectory.
HEAD		= .
HEADER		= libminishell.h

# To test the libaray, create a file with the same name as TESTFILE and play
# arround with it :D (output executable will be named after this option with
# .out extension, with .log file created, for log file obviously).
TESTFILE	= main.c
LOGFILE		= ${TESTFILE:.c=.log}

# Source dirrectory.
DIRSRC		= ./

# Source files.
SRC			=	ft_chdir.c ft_realpath.c \
				ft_initenv.c ft_genenv.c \
				ft_token.c ft_token_consume.c ft_tokenfree.c

BONUS	= 

# Object files (similar to DLLs)
# Path to object files
SRCS			= ${addprefix ${DIRSRC}, ${SRC}}
BONUSES			= ${addprefix ${DIRSRC}, ${BONUS}}
# Source objects (replaces .c with .o).
SRCOBJ			= ${SRCS:.c=.o}
# Bonus objects (same thing as SRCOBJ, but for BONUS)
BONUSOBJ		= ${BONUSES:.c=.o}

# C Compiler.
CC				= gcc
# CC Flags
CFLAGS			= -Wall -Wextra -Werror

# Remove files.
RM				= rm -f

# Link sources, if not specified (default).
.PHONY:			all test clean fclean re

all:			${NAME}

bonus:			all
				${CC} ${CFLAGS} -c ${BONUSES}
				ar rc ${NAME} ${BONUSOBJ}

# Link mandatory.
${NAME}:		$(SRCOBJ)
				ar rc ${NAME} ${SRCOBJ}

# Tester file
test:			all
	${CC} ${CFLAGS} ${TESTFILE} ${NAME} ../libft/libft.a -o ${TESTFILE:.c=.out}
	@ echo -e "\033[1;36m========-[ Execution output ]-========\033[0;37m"	   > ${LOGFILE}
	@ exec ${DIRSRC}${TESTFILE:.c=.out} | cat -e						  >> ${LOGFILE}
	@ echo -e "\n\033[1;35m============-[ Valgrind ]-============\033[0;37m" >> ${LOGFILE}
	@- valgrind ${DIRSRC}${TESTFILE:.c=.out} -qs --leak-check=full		  >> ${LOGFILE} 2>&1
	@ echo -e "\033[1;32m===========-[ Norm errors ]-==========\033[0;37m"	  >> ${LOGFILE}
	@ norminette ${DIRSRC} | grep "Error" | cat							  >> ${LOGFILE}
	@ echo -e "\033[1;32m======================================\033[0;37m"	  >> ${LOGFILE}
	@ less -R ${LOGFILE}

readlog:
	less -R ${LOGFILE}

# Annnddd Lastly...
clean:
				${RM} ${SRCOBJ} ${BONUSOBJ}

fclean:			clean
				${RM} ${NAME} ${TESTFILE:.c=.out} ${LOGFILE}

re:				fclean all

norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS) $(HEADER)