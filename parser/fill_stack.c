/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouati <atouati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 03:46:24 by atouati           #+#    #+#             */
/*   Updated: 2022/11/18 23:27:34 by atouati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell2.h"


void	add_num(t_minishell **top, t_minishell *tmp)
{
	t_minishell	*temp;

	if (*top == NULL)
		*top = tmp;
	else
	{
		temp = *top;
		while (temp->next)
			temp = temp->next;
		temp->next = tmp;
	}
}

int	get_type(int i, char **str)
{
	if (i == 0)
		return (ARG);
	else if (str[i - 1][0] == '<' && str[i - 1][1] == '\0')
		return (INPUT_FILE);
	else if (str[i - 1][0] == '>' && str[i - 1][1] == '\0')
		return (OUTPUT_FILE);
	else if (str[i - 1][0] == '>' && str[i - 1][1] == '>')
		return (APPEND);
	else if (str[i - 1][0] == '<' && str[i - 1][1] == '<')
		return (HEREDOC);
	else
		return (ARG);
}

int	check_error(char	**str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if ((str[i][0] == '<' || str[i][0] == '>')
			&& (str[i + 1][0] == '<' || str[i + 1][0] == '>'))
				return (0);
		if (str[i][0] == '<' && str[i][1] == '>')
			return (0);
		if (str[i][0] == '>' && str[i][1] == '<')
			return (0);
		i++;
	}
	if (str[i + 1] == NULL && (str[i][0] == '<' || str[i][0] == '>'))
			return (0);
	return (1);
	
}

int	check_error_2(char *str)
{
	if (str[0] == '<' && str[1] == '<')
	{
		if (!ft_memcmp(str, "<<"))
			return (0);
	}
	else if (str[0] == '>' && str[1] == '>')
	{
		if (!ft_memcmp(str, ">>"))
			return (0);
	}
	else if (str[0] == '<' && str[1] == '\0')
	{
		return (0);
	}
	else if (str[0] == '>' && str[1] == '\0')
	{
		return (0);
	}
	else
		return (0);
	return (1);
	
}

t_minishell	*fill_stack(t_minishell *stack_a, char **str, char **env, t_shell *mini)
{
	t_minishell	*tmp;
	int			i;

	i = 0;
	tmp = NULL;
	if (!check_error(str))
	{
		printf("minishell: syntax error near unexpected token\n");
		mini->ret = 258;
		return (NULL);
	}
	while (str[i])
	{
		if (check_error_2(str[i]))
		{
			printf("minishell: syntax error near unexpected token\n");
			mini->ret = 258;
			return (NULL);
		}
		if (str[i][0] != '<' && str[i][0] != '>' && str[i][0] != '|')
		{
			//printf("------ %s\n", str[i]);
			str[i] = handling_quotes(str[i], -1, ' ');
			str[i] = check_expand(str[i], env, get_type(i, str), mini);
			if (str[i][0] != '\0')
			{
				tmp = malloc(sizeof(t_minishell));
				tmp->data = ft_strdup(str[i]);
				tmp->type = get_type(i, str);
				tmp->next = NULL;
				add_num(&stack_a, tmp);
			}
		}
		i++;
	}
	return (stack_a);
}

void	open_and_define(t_minishell **tokens)
{
	int			i;
	t_minishell	*head;

	i = 0;
	while (tokens[i] != NULL)
	{
		head = tokens[i];
		while (tokens[i] != NULL)
		{
			tokens[i]->file.fd = -4;
			if (tokens[i]->type == OUTPUT_FILE)
			{
				tokens[i]->file.type = OUTPUT_FILE;
				tokens[i]->file.fd = open(tokens[i]->data, O_CREAT | O_TRUNC, 0600);
			}
			else if (tokens[i]->type == INPUT_FILE)
			{
				tokens[i]->file.type = INPUT_FILE;
				tokens[i]->file.fd = open(tokens[i]->data, O_RDONLY);
			}
			else if (tokens[i]->type == APPEND)
			{
				tokens[i]->file.type = APPEND;
				tokens[i]->file.fd = open(tokens[i]->data, O_CREAT | O_APPEND, 0600);
			}
			if (tokens[i]->file.fd < 0 && tokens[i]->file.fd != -4)
			{
				printf("minishell: %s: No such file or directory\n", tokens[i]->data);
				exit (0);
			}
			tokens[i] = tokens[i]->next;
		}
		tokens[i] = head;
		i++;
	}
	
}

void	define_cmd(t_minishell **tokens)
{
	int			i;
	t_minishell	*head;

	i = 0;
	while (tokens[i])
	{
		head = tokens[i];
		while (tokens[i])
		{
			if (tokens[i]->type == ARG)
			{
				tokens[i]->type = CMD;
				break ;
			}
			tokens[i] = tokens[i]->next;
		}
		tokens[i] = head;
		i++;
	}
}

t_minishell	**sep_split(char **str, char sep, char **env, t_shell *mini)
{
	t_minishell	**tokens;
	t_minishell	*head;
	int			i;
	char		**chr;

	i = 0;
	while (str[i])
		i++;
	tokens = malloc(sizeof(t_minishell *) * (i + 1));
	i = 0;
	while (str[i])
	{
		chr = ft_split(str[i], sep);
		tokens[i] = NULL;
		tokens[i] = fill_stack(tokens[i], chr, env, mini);
		i++;
		ft_free(chr);
	}
	tokens[i] = NULL;
	define_cmd(tokens);
	//open_and_define(tokens);
	ft_free(str);
	return (tokens);
}