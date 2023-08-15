
#include "libminishell.h"

void	ft_genenv(t_envp *envp)
{
	t_envnode	*tmp;
	size_t		indx;
	// char		*val;

	indx = 0;
	if (envp->cache)
	{
		while (envp->cache[indx])
			free(envp->cache[indx++]);
		free(envp->cache);
	}
	envp->cache = malloc(envp->len + 1);
	envp->cache[envp->len] = NULL;
	tmp = envp->begin;
	indx = 0;
	while (tmp)
	{
		// val = ft_strjoin("=", tmp->value);
		envp->cache[indx] = ft_strjoin(tmp->key, tmp->value);
		// free(val);
		indx++;
		tmp = tmp->next;
	}
}