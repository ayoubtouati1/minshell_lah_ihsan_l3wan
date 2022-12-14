/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouati <atouati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:11:31 by atouati           #+#    #+#             */
/*   Updated: 2022/11/19 14:36:36 by atouati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"
#include "libft/libft.h"

t_sig	g_sig;
int	init_env(t_shell *mini, char **env_array)
{
	t_list_env	*env;
	t_list_env	*new;
	int		i;

	if (!(env = malloc(sizeof(t_list_env))))
		return (1);
		
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->env = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		if (!(new = malloc(sizeof(t_list_env))))
			return (1);
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}

int	init_export_env(t_shell *mini, char **env_array)
{
	t_list_env	*env;
	t_list_env	*new;
	int		i;

	if (!(env = malloc(sizeof(t_list_env))))
		return (1);
		
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->export_env = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		if (!(new = malloc(sizeof(t_list_env))))
			return (1);
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}

t_minishell	**fill_token(t_token *ptr, char **env, t_shell *mini)
{
	t_minishell	*head;
	t_minishell	**tokens;
	int			i;

	tokens = sep_split(ptr->pip_split, ' ', env, mini);
	i = 0;
	while (tokens[i] != NULL)
	{
		head = tokens[i];
		while (tokens[i] != NULL)
		{
			//tokens[i]->data = handling_quotes(tokens[i]->data, -1, ' ');
			tokens[i]->quotes = check_quot(tokens[i]->data);
			//tokens[i]->data = check_expand(tokens[i]->data, env, tokens[i]);
			tokens[i]->data = remove_quotes(tokens[i]->data);
			tokens[i] = tokens[i]->next;
		}
		tokens[i] = head;
		i++;
	}
	return (tokens);
}

int	skeep_space(char *parse_line)
{
	int	i;

	i = 0;
	while (parse_line[i] && parse_line[i] == ' ')
		i++;
	return (i);
}

int	check_error_op(char *parse_line)
{
	int	i;

	i = 0;
	while (parse_line[i])
	{
		if (parse_line[i] == '|' && parse_line[i + skeep_space(parse_line + i + 1) + 1] == '\0')
			return (0);
		if (parse_line[i] == '|' && parse_line[i + skeep_space(parse_line + i + 1) + 1] == '|')
		{
			printf("********** %c *********\n", parse_line[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

void	signals(void)
{
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler_quit);
}

t_minishell	**parser(t_token *ptr, char **env, t_shell *mini)
{
	t_minishell	**tokens;
	int			i;

	i = 0;
	ptr->parse_line = handling_spaces(ptr->parse_line);
	ptr->parse_line = handling_quotes(ptr->parse_line, '|', -1);
	if (!ptr->parse_line)
	{
		printf("quot error\n");
		ptr->if_true = 1;
		return (0);
	}
	i = skeep_space(ptr->parse_line);
	if (ptr->parse_line[i] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		mini->ret = 258;
		ptr->if_true = 1;
		return (0);
	}
	if (!check_error_op(ptr->parse_line))
	{
		printf("......minishell: syntax error near unexpected token `|'\n");
		mini->ret = 258;
		ptr->if_true = 1;
		return (0);
	}
	ptr->pip_split = ft_split(ptr->parse_line + i, '|');
	free(ptr->parse_line);
	ptr->pip_split = replace_in_quotes(ptr->pip_split, -1, '|');
	ptr->pip_split = replace_in_quotes(ptr->pip_split, ' ', -1);
	tokens = fill_token(ptr, env, mini);
	return (tokens);
}

int	main(int ac, char **av, char **env)
{
	t_token     ptr;
    t_shell t_mini;
	char *prt;
    t_mini.in = dup(STDIN);
	t_mini.out = dup(STDOUT);
    t_mini.ret = 0;
    t_mini.no_exec = 0;
   
	reset_fds(&t_mini);
    init_env(&t_mini,env);
    init_export_env(&t_mini ,env);
    (void)ac;
    (void)av;
	while (1)
	{
		t_mini.exit = 0;
		//prt = ms_getprompt();
		ptr.if_true = 0;
		init_sig();
       	signals();
		ptr.parse_line = readline("$ ");
		if (!ptr.parse_line)
			exit (0);
		if (!ft_memcmp(ptr.parse_line, "\n"))
		{
			free(ptr.parse_line);
			continue ;
		}
		add_history(ptr.parse_line);
		t_mini.start = parser(&ptr, env, &t_mini);
		if (ptr.if_true == 1)
			continue ;
		execution(&t_mini);
		//printf("=-=-=-=%d=-=-=-=\n", t_mini.ret);
		t_minishell *head;
		int i = 0;
		while (t_mini.start[i])
		{
			while (t_mini.start[i])
			{
				free(t_mini.start[i]->data);
				head = t_mini.start[i]->next;
				free(t_mini.start[i]);
				t_mini.start[i] = head;
			}
			i++;
		}
		free(t_mini.start);
		//free(prt);
		//system("leaks minishell");
	}
}
