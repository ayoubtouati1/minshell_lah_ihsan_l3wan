/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 05:51:08 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/11 21:15:39 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell2.h"
#include <stdio.h>
#include "../libft/libft.h"
int    ft_pwd(void)
{
    t_shell *g_mini;
    char *pwd;
    
    if(pwd == getenv("PWD"))
    {
        ft_putendl_fd(pwd, STDOUT);
        return(0);
    }
    else
        return (1);
}