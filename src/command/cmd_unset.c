/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:14:42 by tkurukay          #+#    #+#             */
/*   Updated: 2024/08/18 11:15:25 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include "../../inc/minishell.h"

/*
- Checks if the argument provided for the unset and export commands is valid.
- unset ve export komutu için girilen argümanın geçerli olup olmadığını kontrol eder.
*/
int	check_valid_key(char *key, t_token *node)
{
	int	i;

	i = 0;
	while (key[i] && ((ft_isalnum(key[i]) && !ft_isdigit(key[0]))
			|| key[i] == '_'))
		i++;
	if ((int)ft_strlen(key) != i)
		return (print_error(node, ": not a valid identifier\n", 1), 1);
	return (0);
}

/*
- Organizes env variables for the unset command.
- unset komutu için env değişkenlerini organize eder.
*/
void	unset_organizer(t_data *data, t_env *tmp)
{
	t_env	*prev;

	prev = data->env;
	if (tmp)
	{
		while (prev)
		{
			if (prev->next == tmp)
				break ;
			prev = prev->next;
		}
		if (prev)
			prev->next = tmp->next;
		else
			data->env = tmp->next;
	}
}

/*
- The equivalent of the unset command in Bash for the minishell.
- Bash deki unset komutunun minishelldeki karşılığıdır.
*/
void	cmd_unset(t_data *data, t_token *node)
{
	t_env	*tmp;
	int		flag;

	flag = 0;
	while (node)
	{
		if (check_valid_key(node->value, node))
		{
			node = node->next;
			flag = 1;
			continue ;
		}
		tmp = get_env(data, node->value);
		unset_organizer(data, tmp);
		node = node->next;
	}
	*get_exit_status() = flag;
}
