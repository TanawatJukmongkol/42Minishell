# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/27 21:14:32 by tjukmong          #+#    #+#              #
#    Updated: 2023/09/11 03:08:59 by tponutha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Static Libaray name.
NAME		= libft.a

# Makefile Properties
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

# Source & Header dirrectory
DIRSRC		= ./
HEADER		= ./libft.h

# Source files.
MAN_SRC		= ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c\
			ft_memchr.c ft_memcmp.c ft_strlen.c ft_isalpha.c\
			ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
			ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c\
			ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c\
			ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c\
			ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c\
			ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c\
			ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c

HEAP_SRC	= heap_init.c heap_get.c heap_push.c heap_pop.c \
			heap_free.c heap_remove.c heap_purge.c heap_discard.c

ADD_SRC		= ft_malloc.c ft_zeros.c ft_strclen.c ft_ternary.c

SRC			= $(MAN_SRC) $(HEAP_SRC) $(ADD_SRC)

# Path to object files
SRCS		= ${addprefix ${DIRSRC}, ${SRC}}
SRCOBJ		= ${SRCS:.c=.o}

# Make Rule
all:	${NAME}

${NAME}:	$(SRCOBJ) $(HEADER)
	ar rc ${NAME} ${SRCOBJ}

# Debug Rule
test:	all
	${CC} ${CFLAGS} ${TESTFILE} ${NAME} -o ${TESTFILE:.c=.out}
	@ echo "\033[1;36m========-[ Execution output ]-========\033[0;37m"	   > ${LOGFILE}
	@ exec ${DIRSRC}${TESTFILE:.c=.out} | cat -e						  >> ${LOGFILE}
	@ echo "\n\033[1;35m============-[ Valgrind ]-============\033[0;37m" >> ${LOGFILE}
	@ valgrind ${DIRSRC}${TESTFILE:.c=.out} -qs --leak-check=full		  >> ${LOGFILE} 2>&1
	@ echo "\033[1;32m===========-[ Norm errors ]-==========\033[0;37m"	  >> ${LOGFILE}
	@ norminette ${DIRSRC} | grep "Error" | cat							  >> ${LOGFILE}
	@ echo "\033[1;32m======================================\033[0;37m"	  >> ${LOGFILE}
	@ less -R ${LOGFILE}

# Clean Rule
clean:
	${RM} ${SRCOBJ} ${BONUSOBJ}

fclean:	clean
	${RM} ${NAME} ${TESTFILE:.c=.out} ${LOGFILE}

# Remake Rule
re:	fclean all

# Additional Rule
norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS) $(HEADER)

readlog:
	less -R ${LOGFILE}

# Failsafe
.PHONY:	all test clean fclean re norm readlog