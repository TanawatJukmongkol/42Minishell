/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/08 17:53:42 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# ifdef __linux
#  include <stdint.h>
# endif

// Annoy from MacOS's vscode
# ifndef __null
#  define __null (void *)0x0
# endif

# ifndef SIZE_MAX
#  if __WORDSIZE == 64
#   define SIZE_MAX 18446744073709551615UL
#  else
#   define SIZE_MAX 4294967295U
#  endif
# endif

typedef struct s_stacknode
{
	size_t				id;
	void				*data;
	struct s_stacknode	*next;
	struct s_stacknode	*prev;
	void				(*destruct)(void *data);
}				t_stacknode;

typedef struct s_stackheap
{
	t_stacknode	*begin;
	t_stacknode	*last;
	size_t		id;
}				t_stackheap;

typedef unsigned int	t_uint;
typedef t_stackheap		t_mem;

/*		MEMORY FUNCTION		*/
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_malloc(size_t nmemb, size_t size, t_stackheap *stack, size_t *id);
void	*ft_zeros(size_t nmemb, size_t size, t_stackheap *stack, size_t *id);

/*		CONDITION		*/
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_ternary(int condition, int val1, int val2);

/*		UNALLOCATED STRING FUNCTION		*/
size_t	ft_strlen(const char *s);
size_t	ft_strclen(const char *s, int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/*		ALLOCATED STRING FUNCTION		*/
char	*ft_strdup(const char *s);
char	*ft_strdup_heap(const char *s, t_stackheap *stack);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_substr_heap(const char *s, t_uint start, size_t len, t_mem *stack);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_heap(char const *s1, char const *s2, t_stackheap *stack);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strtrim_heap(char const *s1, char const *set, t_stackheap *stack);
char	**ft_split(char const *s, char c);
void	ft_free_split(void *box);
char	**ft_split_heap(char const *s, char c, t_stackheap *stack);
char	*ft_itoa(int n);
char	*ft_itoa_heap(int n, t_stackheap *stack);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strmapi_heap(char const *s, char (*f)(t_uint, char), t_mem *st);

/*		FILE DESRIPTOR WRITING FUNCTION		*/
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *c, int fd);
void	ft_putendl_fd(char *c, int fd);
void	ft_putnbr_fd(int n, int fd);

/*		HEAP MANAGEMENT FUNCTION DOCUMENT	*/
/*
1.) heap_init
	- description : init t_stackheap with NULL
	- return : Nothing

2.) heap_push
	- description : Push data & its free function to last of t_stackheap
	- return : id of node, -1 if allocation fail

3.) heap_pop
	- description : Pop out last of t_stackheap and using destruct to free data
	- return Nothing

4.) heap_get
	- description : Find N-th node and get its data's pointer
	- return : Pointer of data at N-th node, NULL if not found

5.) heap_remove
	- description : Remove node in t_stackheap by using its id
	- return : Nothing

6.) heap_free
	- description : Remove node in t_stackheap by using data's pointer
	- return : Nothing
	
7.) heap_purge
	- description : free every node in t_stackheap
	- return : Nothing
*/

void	heap_init(t_stackheap *stack);
size_t	heap_push(t_stackheap *stack, void *data, void (*destruct)(void *data));
void	heap_pop(t_stackheap *stack);
void	*heap_get(t_stackheap *stack, size_t id);
void	heap_remove(t_stackheap *stack, size_t id);
void	heap_free(t_stackheap *stack, void *data);
void	heap_purge(t_stackheap *stack);

#endif