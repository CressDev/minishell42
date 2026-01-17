/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 11:10:15 by amonteag          #+#    #+#             */
/*   Updated: 2026/01/17 19:35:53 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name_with_eq(char *raw_token, int start, int end)
{
	char	*var_name;
	char	*var_name_eq;

	var_name = ft_substr(raw_token, start, end - start);
	if (!var_name)
		return (NULL);
	var_name_eq = ft_strjoin(var_name, "=");
	free(var_name);
	if (!var_name_eq)
		return (NULL);
	return (var_name_eq);
}

char	*handle_special_vars(char *raw_token, int *pos)
{
	char	*result;

	if (raw_token[*pos + 1] == '?')
	{
		*pos = *pos + 2;
		result = ft_itoa(g_signal);
		if (!result)
		{
			write(2, "Error: malloc failed for exit code\n", 36);
			return (NULL);
		}
		return (result);
	}
	if (raw_token[*pos + 1] == '-')
	{
		*pos = *pos + 2;
		result = ft_strdup("himBHs");
		if (!result)
			return (write(2, "Error: malloc failed for shell flags\n", 38),
				NULL);
		return (result);
	}
	return (NULL);
}

char	*extract_var_value(char *raw_token, int start, int end, t_list *env)
{
	char	*var_name_eq;
	char	*var_value;
	char	*result;

	var_name_eq = get_var_name_with_eq(raw_token, start, end);
	if (!var_name_eq)
	{
		result = ft_strdup("");
		if (!result)
			write(2, "Error: malloc failed for empty string\n", 39);
		return (result);
	}
	var_value = get_value(env, var_name_eq);
	free(var_name_eq);
	if (!var_value)
	{
		result = ft_strdup("");
		if (!result)
			write(2, "Error: malloc failed for empty var\n", 36);
		return (result);
	}
	result = ft_strdup(var_value);
	if (!result)
		write(2, "Error: malloc failed for var value\n", 36);
	return (result);
}

t_cmd	*init_cmd(t_envs *envs)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->envs = envs;
	cmd->args = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*parse_tokens(t_token *token, t_envs *envs)
{
	t_cmd	*head;
	t_cmd	*current;
	t_token *token_list;

	head = NULL;
	current = NULL;
	token_list = token; // Guardar el inicio de la lista
	while (token)
	{
		if (token->type == TOKEN_WORD)
		{
			current = token_word(current, token, envs);
			if (!head)
				head = current;
			current->argc++;
		}
		else if (token->type == TOKEN_PIPE)
			current = token_pipe(envs, current);
		else if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
		{
			token_redirect(current, token);
			if (token->next)
				token = token->next;
		}
		expand_token(token, envs);
		token = token->next;
	}
	// --- ASIGNA ARGUMENTOS Y HEREDOCS A CADA COMANDO DE LA PIPELINE ---
	t_cmd *cmd_iter = head;
	t_token *tok_iter = token_list;
	while (cmd_iter) {
		t_token *start = tok_iter;
		t_token *end = tok_iter;
		// Busca el final del segmento (pipe o NULL)
		while (end && end->type != TOKEN_PIPE)
			end = end->next;

		// Helpers modificados para aceptar rango [start, end)
		int argc = 0;
		int hcount = 0;
		t_token *tmp = start;
		t_token *prev = NULL;
		while (tmp != end) {
			if (tmp->type == TOKEN_WORD && (!prev || (prev->type != TOKEN_REDIR_IN && prev->type != TOKEN_REDIR_OUT && prev->type != TOKEN_APPEND && prev->type != TOKEN_HEREDOC)))
				argc++;
			prev = tmp;
			tmp = tmp->next;
		}
		cmd_iter->args = ft_calloc(argc + 1, sizeof(char *));
		tmp = start;
		prev = NULL;
		int i = 0;
		while (tmp != end) {
			if (tmp->type == TOKEN_WORD && (!prev || (prev->type != TOKEN_REDIR_IN && prev->type != TOKEN_REDIR_OUT && prev->type != TOKEN_APPEND && prev->type != TOKEN_HEREDOC)))
				cmd_iter->args[i++] = ft_strdup(tmp->content);
			prev = tmp;
			tmp = tmp->next;
		}
		cmd_iter->args[i] = NULL;

		tmp = start;
		while (tmp != end) {
			if (tmp->type == TOKEN_HEREDOC && tmp->next && tmp->next->type == TOKEN_WORD)
				hcount++;
			tmp = tmp->next;
		}
		if (hcount > 0) {
			cmd_iter->heredoc_delimiter = ft_calloc(hcount + 1, sizeof(char *));
			tmp = start;
			i = 0;
			while (tmp != end) {
				if (tmp->type == TOKEN_HEREDOC && tmp->next && tmp->next->type == TOKEN_WORD)
					cmd_iter->heredoc_delimiter[i++] = ft_strdup(tmp->next->content);
				tmp = tmp->next;
			}
			cmd_iter->heredoc_delimiter[i] = NULL;
			cmd_iter->is_heredoc = 1;
		}

		if (end && end->type == TOKEN_PIPE)
			tok_iter = end->next;
		else
			tok_iter = end;
		cmd_iter = cmd_iter->next;
	}
	return head;
}
