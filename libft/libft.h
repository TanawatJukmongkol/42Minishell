/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/05 16:05:32 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# ifdef __linux
#  include <stdint.h>
# endif

# ifndef SIZE_MAX
#  if __WORDSIZE == 64
#   define SIZE_MAX 18446744073709551615UL
#  else
#   define SIZE_MAX 4294967295U
#  endif
# endif

/*		MEMORY FUNCTION		*/
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

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
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
void	ft_free_split(void *box);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/*		FILE DESRIPTOR WRITING FUNCTION		*/
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *c, int fd);
void	ft_putendl_fd(char *c, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif