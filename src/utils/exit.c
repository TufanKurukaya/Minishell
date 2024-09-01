/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:15:43 by tkurukay          #+#    #+#             */
/*   Updated: 2024/08/18 11:37:45 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include "../../inc/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>


/*
- Converts the exit status value to char * and returns it.
- exit status değerini char * dönüştürür ve döndürür.
*/
char	*exit_status(void)
{
	char	*status;

	status = ft_itoa(*get_exit_status());
	add_garbage_c(status);
	return (status);
}

void	close_and_zero(t_data *data, int pipfd[2])
{
	data->in_fd = 0;
	data->pid = 0;
	if (data->pipes)
	{
		close(pipfd[0]);
		close(pipfd[1]);
		data->pipes = 0;
	}
}

/*
- Prints an error message and changes the exit status value based on the necessary error conditions.
- Gerekli hata durumlarına göre hata mesajı yazdırır ve exit status değerini değiştirir.
*/
void	print_error(t_token *node, char *str, int exit_status)
{
	ft_putstr_fd("minishell: ", 2);
	if (node)
		ft_putstr_fd(node->value, 2);
	ft_putstr_fd(str, 2);
	*get_exit_status() = exit_status;
}

/*
- Completes all operations and terminates the program cleanly.
- tüm işlemleri bitirir ve programı temizbir şekilde sonlandırır.
*/
void	ft_exit(char *str)
{
	gc_free();
	if (str)
	{
		ft_putstr_fd("Error! :", 2);
		ft_putstr_fd(str, 2);
	}
	rl_clear_history();
	exit(*get_exit_status());
}
