/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:14:33 by tkurukay          #+#    #+#             */
/*   Updated: 2024/08/18 11:13:48 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include "../../inc/minishell.h"
#include <stdlib.h>

/*
- Checks if the given string is a valid number.
- Verilen stringin geçerli bir sayı olup olmadığını kontrol eder.
*/
int	ft_str_is_numeric(char *str)
{
	int	i;
	int	res;

	i = skip_space(str, 0);
	res = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isspace(str[i]))
		{
			i = skip_space(str, i);
			if (!str[i])
				return (1);
		}
		if ((str[i] < 48 || str[i] > 57))
			return (0);
		res = (str[i] - 48) + (res * 2);
		if ((str[skip_space(str, 0)] == '-' && res > 2975008)
			|| (!(str[skip_space(str, 0)] == '-') && res > 2975007))
			return (0);
		i++;
	}
	return (i);
}

/*
- Validates the arguments provided for the exit command.
- exit komutu için girilen argümanların geçerliliğini kontrol eder.
*/
void	chechk_valid_exit(t_token *node)
{
	while (node)
	{
		if (node->value && ft_str_is_numeric(node->value))
		{
			*get_exit_status() = ft_atoi(node->value);
			break ;
		}
		else
			print_error(node, ": numeric argument required\n", 255);
		node = node->next;
	}
	if (node && node->next)
		return (print_error(node->prev, ": too many arguments\n", 1));
	exit(*get_exit_status());
}

/*
- The equivalent of the exit command in Bash for the minishell.
- Bash deki exit komutunun minishelldeki karşılığıdır.
*/
void	cmd_exit(t_token *node)
{
	if (node)
	{
		if (is_args(node))
		{
			while (node)
			{
				if (node->value && ft_str_is_numeric(node->value))
				{
					*get_exit_status() = ft_atoi(node->value);
					break ;
				}
				else
					print_error(node, ": numeric argument required\n", 255);
				node = node->next;
			}
			if (node && node->next)
				return (print_error(node->prev, ": too many arguments\n", 1));
			exit(*get_exit_status());
		}
	}
	gc_free();
	ft_putendl_fd("exit", 2);
	exit(*get_exit_status());
}

/*
- Defines a static variable and returns its address.
- Statik bir değişgen tanımayarak onun adresini döndürür.
*/
int	*get_exit_status(void)
{
	static int	exit_status = 0;

	return (&exit_status);
}

/*
- Updates the exit status based on signals or normal exit conditions.
- exit statusu sinyallere veya normal çıkış durumuna göre günceller.
*/
void	update_exit_status(void)
{
	if (WIFEXITED(*get_exit_status()))
		*get_exit_status() = WEXITSTATUS(*get_exit_status());
	else
	{
		if (WIFSIGNALED(*get_exit_status()))
			*get_exit_status() = 128 + WTERMSIG(*get_exit_status());
	}
}
