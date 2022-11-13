/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sepr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouati <atouati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 02:49:36 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/12 19:34:09 by atouati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/minishell.h"
#include "minishell2.h"

t_minishell *next_sep(t_minishell *token, int skip)
{
    if (token && skip)
        token = token->next;
    while (token && token->type < INPUT_FILE)
       token = token->next;
    return (token);
}

t_minishell *prev_sep(t_minishell *token, int skip)
{
    if (token && skip)
        token = token->next;
    while (token && token->type < INPUT_FILE)
        token = token->next;
    return (token);
}

