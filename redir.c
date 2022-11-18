/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouati <atouati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:58:29 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/18 03:15:14 by atouati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"
#include "libft/libft.h"

void    redir(t_shell *mini, t_minishell *token, int type)
{
    int id;

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

int minipipe(t_shell *mini, t_minishell *token)
{
    pid_t pid;
    int pipefd[2];
    
    pipe(pipefd);
    pid = fork();
    if (pid == 0)
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
        close(pipefd[1]);
		mini->pipout = pipefd[1];
		mini->pid = -1;
		mini->parent = 0;
		mini->no_exec = 0;
		redir_and_exec(mini, token);
        exit (0);
	}
    else
	{
		ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN);
        close(pipefd[0]);
		mini->pipin = pipefd[0];
		mini->pid = pid;
		mini->last = 0;
		return (1);
	}
    return 0;
}
