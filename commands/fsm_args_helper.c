/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_args_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:30:00 by cress             #+#    #+#             */
/*   Updated: 2026/01/17 07:47:29 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Cuenta los argumentos reales (no redirecciones ni sus argumentos)
int count_args_no_redirect_fsm(t_token *token)
{
    int count = 0;
    t_token *prev = NULL;
    while (token)
    {
        if (token->type == TOKEN_WORD && (!prev || (prev->type != TOKEN_REDIR_IN && prev->type != TOKEN_REDIR_OUT && prev->type != TOKEN_APPEND && prev->type != TOKEN_HEREDOC)))
            count++;
        prev = token;
        token = token->next;
    }
    return count;
}

// Rellena el array de argumentos reales (no redirecciones ni sus argumentos)
void fill_args_array_fsm(t_cmd *cmd, t_token *token)
{
    int i = 0;
    t_token *prev = NULL;
    while (token)
    {
        if (token->type == TOKEN_WORD && (!prev || (prev->type != TOKEN_REDIR_IN && prev->type != TOKEN_REDIR_OUT && prev->type != TOKEN_APPEND && prev->type != TOKEN_HEREDOC)))
        {
            cmd->args[i] = ft_strdup(token->content);
            i++;
        }
        prev = token;
        token = token->next;
    }
    cmd->args[i] = NULL;
}

// Ejemplo de uso en tu parser principal:
// int argc = count_args_no_redirect_fsm(token_list);
// cmd->args = ft_calloc(argc + 1, sizeof(char *));
// fill_args_array_fsm(cmd, token_list);

// Cuenta los delimitadores de heredoc (<<) en la lista de tokens
int count_heredoc_delims_fsm(t_token *token)
{
    int count = 0;
    while (token)
    {
        if (token->type == TOKEN_HEREDOC && token->next && token->next->type == TOKEN_WORD)
            count++;
        token = token->next;
    }
    return count;
}

// Rellena el array de delimitadores de heredoc en cmd
void fill_heredoc_delims_fsm(t_cmd *cmd, t_token *token)
{
    int i = 0;
    while (token)
    {
        if (token->type == TOKEN_HEREDOC && token->next && token->next->type == TOKEN_WORD)
        {
            cmd->heredoc_delimiter[i] = ft_strdup(token->next->content);
            i++;
        }
        token = token->next;
    }
    if (cmd->heredoc_delimiter)
        cmd->heredoc_delimiter[i] = NULL;
}
