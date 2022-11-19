/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouati <atouati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 22:18:12 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/19 14:51:37 by atouati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    t_minishell *head;
    head = token;
    while (token)
    {
        if (is_type(token, OUTPUT_FILE))
            redir(mini, token, OUTPUT_FILE);
        else if(is_type(token, APPEND))
            redir(mini, token, APPEND);
        else if(is_type(token, INPUT_FILE))
            input(mini, token);
        else if (is_type(token, HEREDOC))
            heredoc_func(mini, token);
        token = token->next;
    }
    
    token = head;
    if (mini->no_exec == 0)
        exec_cmd(mini, token);
}

void execution(t_shell *ptr)
{
    t_minishell **token;
    int status;
    int i;
    int pipe;
    
    i = 0;
    pipe = 0;
    token = ptr->start;
    while (token[i] && ptr->exit == 0)
    {
        ptr->charge = 1;
        ptr->parent = 1;
        ptr->last = 1;
        if (token[i + 1])
            minipipe(ptr, token[i]);
        else
        {
            redir_and_exec(ptr, token[i]);
            reset_std(ptr);
            close_fds(ptr);
		    reset_fds(ptr);
		}
        //if (ptr->last == 0)
        //   ptr->ret = status;
        //if (ptr->parent == 0)
        //   exit(ptr->ret);
        //ptr->no_exec = 0;
        i++;
    }
    while (i--)
    {
        waitpid(-1, &status, 0);
        status = WEXITSTATUS(status);
    }
    ptr->ret = status;
    
}
