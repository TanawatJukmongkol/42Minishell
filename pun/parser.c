/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:46:42 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/10 12:04:18 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pun.h"
#include <threads.h>

/*void	clear_cmd_table(t_cmd_table *table)
{
	table->cmd = NULL;
	table->here_doc = NULL;
	table->search_argv = 0;
	// table->indx = 0;
	table->infile.begin = NULL;
	table->outfile.begin = NULL;
	table->argv.begin = NULL;
}

void	build_stream_from_table(t_token_stream *s, t_cmd_table *table)
{
	if (table->cmd)
		ft_token(s, __cmd)->value = ft_strdup(table->cmd);
	if (table->argv.begin)
	{
		// Problem stems from moving around and setting pointer
		// deep copy token to t_token_stream *s, here! (Or find a way to manipulate head pointer to table->argv.begin)
		s->last->next = table->argv.begin;
		s->last = table->argv.last;
	}
	if (table->here_doc)
		ft_token(s, __here_doc)->value = ft_strdup(table->here_doc);
	if (table->infile.begin)
	{
		// Here as well!
		s->last->next = table->infile.begin;
		s->last = table->infile.last;
	}
	if (table->outfile.begin)
	{
		// Omg here as well T^T
		s->last->next = table->outfile.begin;
		s->last = table->outfile.last;
	}
	clear_cmd_table(table);
}

void	rm_next(t_token *t)
{
	t_token	*tmp;

	tmp = t->next;
	t->next = t->next->next;
	free(tmp->value);
	free(tmp);
}

char	*set_cmd_table(t_token *t)
{
	char	*val;

	val = ft_strdup(t->next->value);
	rm_next(t);
	return (val);
}

void	cmdtable_switch(t_token_stream *s, t_token *t, void *vars)
{
	t_cmd_table	*table;

	table = (t_cmd_table *)vars;
	if (table->search_argv && t->type == __none)
		ft_token(&table->argv, __argv)->value = ft_strdup(t->value);
	if (t->next)
	{
		if (t->type == __here_doc)
			table->here_doc = set_cmd_table(t);
		if (t->type == __redirr_in)
		{
			ft_token(&table->infile, __redirr_in)->value = ft_strdup(\
				t->next->value);
			rm_next(t);
		}
		if (t->type == __redirr_append)
		{
			ft_token(&table->outfile, __redirr_append)->value = ft_strdup(\
				t->next->value);
			rm_next(t);
		}
		if (t->type == __redirr_trunc)
		{
			ft_token(&table->outfile, __redirr_trunc)->value = ft_strdup(\
				t->next->value);
			rm_next(t);
		}
	}
	if (t->type == __none && !table->search_argv)
	{
		table->cmd = ft_strdup(t->value);
		table->search_argv = 1;
	}
	if (table->search_argv && t->type != __none)
		table->search_argv = 0;
	if (t->next == NULL)
		build_stream_from_table(s, table);
	// table->indx++;
	if (t->type == __pipe || t->next == NULL)
	{
		build_stream_from_table(s, table);
		if (t->type == __pipe)
			ft_token(s, __pipe)->value = ft_strdup("|");
	}
}

void	parser(t_token_stream *output, t_token_stream *input)
{
	t_cmd_table		cmd_table;

	if (!output || !input)
		return ;
	clear_cmd_table(&cmd_table);
	while (input->begin)
		ft_token_consume(output, input, cmdtable_switch, &cmd_table);
}*/

void	init_table(t_cmd_table *table)
{
	table->cmd = NULL;
	table->here_doc = NULL;
	table->search_argv = 0;
	table->infile.begin = NULL;
	table->infile.last = NULL;
	table->outfile.begin = NULL;
	table->outfile.last = NULL;
	table->argv.begin = NULL;
	table->argv.last = NULL;
}

void	rm_next(t_token *t)
{
	t_token	*tmp;

	if (!t->next)
		return ;
	tmp = t->next;
	t->next = t->next->next;
	free(tmp->value);
	free(tmp);
}

void	build_table(t_token_stream *s, t_cmd_table *table, int pipe)
{
	(void)(pipe);
	if (table->cmd)
		ft_token(s, __cmd)->value = table->cmd;
	if (table->argv.begin)
	{
		s->last->next = table->argv.begin;
		s->last = table->argv.last;
	}
	if (table->here_doc)
		ft_token(s, __here_doc)->value = ft_strdup(table->here_doc);
	if (table->infile.begin)
	{
		if (!s->begin)
		{
			s->begin = table->infile.begin;
			s->last = table->infile.last;
		}
		s->last->next = table->infile.begin;
		s->last = table->infile.last;
	}
	if (table->outfile.begin)
	{
		if (!s->begin)
		{
			s->begin = table->outfile.begin;
			s->last = table->outfile.last;
		}
		s->last->next = table->outfile.begin;
		s->last = table->outfile.last;
	}
	if (pipe)
		ft_token(s, __pipe)->value = ft_strdup("|");
	init_table(table);
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
	{
		if (t->type == __here_doc)
		{
			if (table->here_doc)
				free(table->here_doc);
			table->here_doc = ft_strdup(t->next->value);
			rm_next(t);
		}
		if (t->type == __redirr_in)
		{
			ft_token(&table->infile, t->type)->value = ft_strdup(t->next->value);
			rm_next(t);
		}
		if (t->type == __redirr_append || t->type == __redirr_trunc)
		{
			ft_token(&table->outfile, t->type)->value = ft_strdup(t->next->value);
			rm_next(t);
		}
	}
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
		ft_token_consume(output, input, cmdtable_switch, &cmd_table);
}

