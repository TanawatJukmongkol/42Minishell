/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:46:42 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/15 21:10:50 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pun.h"

void	build_table(t_token_stream *s, t_cmd_table *table, int pipe)
{
	t_token	*cmd;

	cmd = ft_token(s, __cmd);
	cmd->value = table->cmd;
	if (table->argv.begin)
		append_table(s, &table->argv);
	if (table->infile.begin)
		append_table(s, &table->infile);
	if (table->outfile.begin)
		append_table(s, &table->outfile);
	if (pipe)
		ft_token(s, __pipe)->value = ft_strdup("|");
	if (!cmd->value)
	{
		s->begin = cmd->next;
		free(cmd);
	}
	init_table(table);
}

void	cmdtable_multi_token(t_cmd_table *table, t_token *t)
{
	if (t->type == __redirr_in || t->type == __here_doc)
	{
		ft_token(&table->infile, t->type)->value = \
			ft_strdup(t->next->value);
		rm_next(t);
	}
	if (t->type == __redirr_append || t->type == __redirr_trunc)
	{
		ft_token(&table->outfile, t->type)->value = \
			ft_strdup(t->next->value);
		rm_next(t);
	}
}

void	cmdtable_switch(t_token_stream *s, t_token *t, void *vars)
{
	t_cmd_table	*table;

	table = (t_cmd_table *)vars;
	if (t->type == __none)
	{
		if (table->search_argv)
			ft_token(&table->argv, __argv)->value = ft_strdup(t->value);
		else
		{
			table->cmd = ft_strdup(t->value);
			table->search_argv = 1;
		}
	}
	if (t->next)
		cmdtable_multi_token(table, t);
	if (!t->next)
		return (build_table(s, table, 0));
	if (t->type == __pipe)
		return (build_table(s, table, 1));
}

void	parser(t_token_stream *output, t_token_stream *input)
{
	t_cmd_table	cmd_table;

	init_table(&cmd_table);
	while (input->begin)
	{
		if (!input->begin->value)
		{
			ft_tokenfree(input);
			ft_tokenfree(output);
			purge_table(&cmd_table);
			return ;
		}
		ft_token_consume(output, input, cmdtable_switch, &cmd_table);
	}
}

