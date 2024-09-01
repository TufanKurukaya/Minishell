/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:14:27 by tkurukay          #+#    #+#             */
/*   Updated: 2024/08/18 11:12:45 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include "../../inc/minishell.h"
#include <stdio.h>

/*
- Compares two strings ignoring case sensitivity.
- Büyük küçük harf duyarlılığını yok sayarak iki stringi karşılaştırır.
*/
int	is_echo(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (1);
	i = 0;
	while (ft_tolower(str1[i]) && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}


/*
- Checks the flag for the echo command.
- echo komutunun flag kontrolünü yapar.
*/
int	check_flags(t_token *node)
{
	int	i;

	i = 1;
	if ((node->type == WORD && !node->value[0]))
		return (2);
	if (!node->value[i])
		return (0);
	while (node->value[i])
	{
		if (node->value[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}


/*
- The equivalent of the echo command in Bash for the minishell.
- Bash deki echo komutunun minishelldeki karşılığıdır.
*/
void	cmd_echo(t_token *node)
{
	int	check;

	check = 0;
	while (node && ((is_args(node) && *node->value == '-')
			|| (node->type == WORD && !node->value[0])))
	{
		if (!check_flags(node))
			break ;
		check = check_flags(node);
		node = node->next;
	}
	while (node)
	{
		if (is_args(node))
			printf("%s", node->value);
		else
			return ;
		if (node->next && (is_args(node->next)))
			printf(" ");
		node = node->next;
	}
	if (check != 1)
		printf("\n");
	*get_exit_status() = 0;
}
