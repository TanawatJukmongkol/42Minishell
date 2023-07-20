
#include <stdio.h>
#include "libft.h"

static int word_count(const char *s, char *c)
{
    int     word_count;
    int     str_len;
    int     match_len;
    char    *str;
	char	*match;
    
    word_count = 0;
    str = (char *)s;
    str_len = ft_strlen(s);
    match_len = ft_strlen(c);
	match = str;
    while (match != NULL)
	{
		match = ft_strnstr(str, c, str_len - (str - s));
        str = match + match_len;
        word_count++;
    }
    return (word_count);
}

static char     **ft_free_arr(char **s)
{
    int     i;

    i = 0;
    while (s[i])
    {
        free(s[i]);
        i++;
    }
    free(s);
    return (NULL);
}

static char	**ft_cpytotable(const char *s, char *c, int wcount)
{
	char	*str;
	int	str_len;
	int	match_len;

	str = (char *)s;
	while (wcount--)
	{
		match = ft_strnstr(str, c, str_len - (str - s));
		str = match + match_len;
	}
}

char **ft_split_notqoute (const char *s, char *c)
{
    char	**res;
	int		words;

	words = word_count(str, c);
    res = malloc(words + 1);
	return (res);
}

int main () {
    char **split = ft_split_notqoute("a||b", "||");
    if (!split)
		return 0;
	for (int i = 0; split[i] != NULL; i++)
    	printf("%s\n", split[i]);
    ft_free_arr(split);
    return 0;
}

