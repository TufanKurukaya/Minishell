/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:15:36 by tkurukay          #+#    #+#             */
/*   Updated: 2024/08/15 03:35:30 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>

void	handle_sigint(int sig)
{
	*get_exit_status() = 128 + sig;
	if (g_signal == HERE_SIG)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		ft_exit(NULL);
	}
	else if (g_signal == EXEC_SIG)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else if (g_signal == PROMT_SIG)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigquit(int sig)
{
	*get_exit_status() = 128 + sig;
	if (g_signal == EXEC_SIG)
	{
		printf("Quit : %d\n", sig);
		rl_replace_line("", 0);
	}
}

void	signal_base(void)
{
	if (g_signal == EXEC_SIG)
		signal(SIGQUIT, handle_sigquit);
	else
		signal(SIGQUIT, SIG_IGN);
}
