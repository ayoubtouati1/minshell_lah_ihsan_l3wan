/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 03:44:57 by atouati           #+#    #+#             */
/*   Updated: 2022/11/18 08:39:42 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell2.h"

char	*handling_spaces(char *str)
{
	char	*dest;
	int		i;
	int		j;

	j = 0;
	i = 0;
	dest = count_space_and_alloc(str, dest, i);
	while (str[i])
	{
		if (!add_after_opirations(&str, &dest, &i, &j))
			break ;
		if (!add_inside_quot(&str, &dest, &i, &j))
			break ;
		dest[j] = str[i];
		add_befor_opirations(&str, &dest, &i, &j);
		i++;
		j++;
	}
	dest[j] = '\0';
	free(str);
	return (dest);
}