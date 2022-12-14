/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 03:38:53 by atouati           #+#    #+#             */
/*   Updated: 2022/11/18 08:39:56 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell2.h"

void	add_befor_opirations(char **str, char **dest, int *i, int *j)
{
	if (((*str)[*i + 1] == '<' && (*str)[*i] != '<')
		|| ((*str)[*i + 1] == '>' && (*str)[*i] != '>')
		|| ((*str)[*i + 1] == '|' && (*str)[*i] != '|'))
	{
		(*j)++;
		(*dest)[*j] = ' ';
	}
}