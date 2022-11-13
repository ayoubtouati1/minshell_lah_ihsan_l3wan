/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 02:55:29 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/13 02:55:35 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"
#include "libft/libft.h"

void sig_handler(int sig)
{
    t_sig sig_m;
    if (sig == SIGINT)
    {
        ft_putstr_fd("\b\b   ", 1);
        ft_putstr_fd("\n", 1);
        ft_putstr_fd("minihell-$ ", 1);
        sig_m.exit_status = 1;
    }
    if (sig == SIGQUIT)
    {
        char *nbr;

        nbr = ft_itoa(sig);
        if (sig_m.pid != 0)
        {
            ft_putstr_fd("Quit :", 1);
            ft_putstr_fd(nbr, 1);
            sig_m.exit_status = 131;
            sig_m.sigquit = 1;
        }
        free(nbr);
        nbr = NULL;
    } 
}

void init_sig(void)
{
    t_sig sig_m;
    sig_m.sigint = 0;
    sig_m.pid = 0;
    sig_m.exit_status = 0;
    sig_m.sigquit = 0;
}