
# Libminishell - v0.0.1 BASH shell interpreter essential functions

> A library for minishell, becuase life is pain, and they don't want us to use some availible functions in C

# File system functions

`ft_realpath(char *path_any);`
> Find the absolute path, with relative path support.

`ft_chdir(char *path_any);`
> Change current dirrectory, with relative path support.

`ft_open(char *path_any, int options)`
> Open file, with relative path support.

`ft_redir(int fd_dst, int fd_src);`
> Redirrect file output from one file descriptor to another.

# Environmental variables

`ft_initenv(t_envp env, char **envp);`
> Initializes, and populate the env linked-list.

`ft_genenv(t_envp env, char **envp)`
> Generate the env cache.

`ft_getenv(t_envp env, char *name)`
> Rewrite of the <stdlib.h> getenv, with caching.

`ft_setenv(t_envp env, char *name)`
> Rewrite of the <stdlib.h> setenv, with caching.

`ft_unsetenv(t_envp env, char *name)`
> Rewrite of the <stdlib.h> unsetenv, with caching.

# Lexical analysis (a.k.a. Tokenizer)

`t_token	*ft_token(t_token_stream *stream, t_token_type type)`
> Adds a token to the token stream.

`ft_token_consume(t_token_stream *dst, t_token_stream *src, void (*fn)(t_token_stream *s, t_token *t));`
> Consumes a token from token stream to be processed in the Lexical analysis pipeline.

`ft_tokenfree(t_token_stream *s)`
> Clears all the token from the stream.
