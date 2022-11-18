/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 04:01:09 by atouati           #+#    #+#             */
/*   Updated: 2022/11/18 08:37:52 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell2.h"


int	check_dollar(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '$')
			return (0);
		i++;
	}
	return (1);
}

int	cont_dollar(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (i);
}
