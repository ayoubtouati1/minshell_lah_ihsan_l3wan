/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouati <atouati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 22:18:12 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/13 00:12:18 by atouati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/minishell.h"
#include "minishell2.h"
#include "libft/libft.h"

static int		is_type(t_minishell *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

static int is_types(t_minishell *token, char *types)
{
    if (ft_strchr(types, 'X') && is_type(token ,CMD))
        return (1);
    else if (ft_strchr(types, 'x') && is_type(token, ARG))
		return (1);
	else if (ft_strchr(types, 'O') && is_type(token, OUTPUT_FILE))
		return (1);
	else if (ft_strchr(types, 'A') && is_type(token, APPEND))
		return (1);
	else if (ft_strchr(types, 'I') && is_type(token, INPUT_FILE))
		return (1);
    // else if (ft_strchr(types, H) && is_type(token, HEREDOC))
    //     return (1);
        
    return (0);    
}

void    redir_and_exec(t_shell *mini, t_minishell *token)
{
    t_minishell *prev;
    t_minishell *next;
    int pipe;
    int i;
   // prev = prev_sep(token, 0);
   // next = next_sep(token, 0);
    
    if (is_type(token, OUTPUT_FILE))
        redir(mini, token, OUTPUT_FILE);
    else if(is_type(token, APPEND))
        redir(mini, token, APPEND);
    else if(is_type(token, INPUT_FILE))
        input(mini, token);
    // else if (mini->start[i])
    //     pipe = minipipe(mini);
        // else if (is_type(token, HEREDOC))
        //     herdoc_func(mini, HEREDOC);
    if (mini->no_exec == 0)
        exec_cmd(mini, token);
}

void execution(t_shell *ptr)
{
    t_minishell **token;
    int status;
    int i = 0;
    token = ptr->start;
    // if (is_types(ptr->start, "TAI"))
    //     token = ptr->start->next;
    while (token[i])
    {
         ptr->charge = 1;
         ptr->parent = 1;
         ptr->last = 1;
         redir_and_exec(ptr, token[i]);
         waitpid(-1, &status, 0);
         status = WEXITSTATUS(status);
         if (ptr->last == 0)
             ptr->ret = status;
         if (ptr->parent == 0)
            exit(ptr->ret);
         ptr->no_exec = 0;    
         token[i] = (token[i]->next);
        i++;
    }
}
