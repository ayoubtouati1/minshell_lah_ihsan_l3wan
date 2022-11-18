/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:26:05 by atouati           #+#    #+#             */
/*   Updated: 2022/11/18 08:40:11 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell2.h"

int	ft_strnstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	c;
	size_t	n_len;
	char	*hay;
	char	*need;

	i = 0;
	hay = (char *)haystack;
	need = (char *)needle;
	n_len = ft_strlen(needle);
	if (n_len == 0 || haystack == needle)
		return (hay);
	while (hay[i] != '\0')
	{
		c = 0;
		while (hay[i + c] != '\0' && need[c] != '\0'
			&& hay[i + c] == need[c])
			c++;
		if (c == n_len)
			return (i);
		i++;
	}
	return (0);
}
