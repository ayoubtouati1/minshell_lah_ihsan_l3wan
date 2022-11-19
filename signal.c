/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouati <atouati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 02:55:29 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/19 14:35:50 by atouati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"
#include "libft/libft.h"

void sig_handler(int sig)
{
    if (g_sig.pid == 0)
    {
        sig++;
	    write(1, "\n", 1);
        rl_replace_line("", 0);
	    rl_on_new_line();
	    rl_redisplay();
    }
}

void sig_handler_quit(int code)
{
    char	*nbr;

	nbr = ft_itoa(code);
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Quit: ", 1);
		ft_putendl_fd(nbr, 1);
		g_sig.exit_status = 131;
		g_sig.sigquit = 1;
	}
    ft_memdel(nbr);
}
void init_sig(void)
{
    t_sig sig_m;
    sig_m.sigint = 0;
    sig_m.pid = 0;
    sig_m.exit_status = 0;
    sig_m.sigquit = 0;
}