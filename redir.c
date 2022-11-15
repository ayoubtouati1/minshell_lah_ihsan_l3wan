/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:58:29 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/15 21:12:36 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"
#include "libft/libft.h"

void    redir(t_shell *mini, t_minishell *token, int type)
{
    ft_close(mini->fdout);
    if (type == OUTPUT_FILE)
        mini->fdout = open(token->data, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    else
        mini->fdout = open(token->data, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
    if (mini->fdout == -1)
    {
        ft_putstr_fd("minishell: ",STDERR);
        ft_putstr_fd(token->data, STDERR);
        ft_putstr_fd(": No such file or directory\n", STDERR);
        mini->ret = 1;
        mini->no_exec = 1;
        return ;
    }
    dup2(mini->fdout, STDOUT);
}

void    input(t_shell *mini, t_minishell *token)
{
    ft_close(mini->fdin);
    mini->fdin = open(token->data, O_RDONLY, S_IRWXU);
    if (mini->fdin == -1)
    {
        ft_putstr_fd("minishell: ",STDERR);
        ft_putstr_fd(token->data, STDERR);
        ft_putstr_fd(": No such file or directory\n", STDERR);
        mini->ret = 1;
        mini->no_exec = 1;
        return ;
    }
    dup2(mini->fdin, STDIN);
}

int minipipe(t_shell *mini)
{
    pid_t pid;
    int pipefd[2];
    
    pipe(pipefd);
    pid = fork();
    if (pid == 0)
	{
		ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		mini->pipin = pipefd[0];
		mini->pid = -1;
		mini->parent = 0;
		mini->no_exec = 0;
		return (2);
	}
    else
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		mini->pipout = pipefd[1];
		mini->pid = pid;
		mini->last = 0;
		return (1);
	}
}
