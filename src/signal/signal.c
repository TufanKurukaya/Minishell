/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:15:36 by tkurukay          #+#    #+#             */
/*   Updated: 2024/08/18 11:30:35 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>

/*
- Handles operations based on the current state when a Ctrl + C signal is received.
- Ctrl + C sinyali geldiğinde ilerleyişin bulunduğu duruma göre işlem yapar.
*/
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

/*
- Function that handles the Ctrl + \ signal.
- Ctrl + \ sinyalini işleyen fonksiyon.
*/
void	handle_sigquit(int sig)
{
	*get_exit_status() = 128 + sig;
	if (g_signal == EXEC_SIG)
	{
		printf("Quit : %d\n", sig);
		rl_replace_line("", 0);
	}
}

/*
- Determines the action based on the current state when a Ctrl + \ signal is received.
- Ctrl+ \ sinyalinin işleyisin bulunduğu duruma göre yapması gereken işlemi seçer.
*/
void	signal_base(void)
{
	if (g_signal == EXEC_SIG)
		signal(SIGQUIT, handle_sigquit);
	else
		signal(SIGQUIT, SIG_IGN);
}
