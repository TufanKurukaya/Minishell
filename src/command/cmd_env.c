/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:14:31 by tkurukay          #+#    #+#             */
/*   Updated: 2024/08/18 11:36:35 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

/*
- The equivalent of the env command in Bash for the minishell.
- Bash deki env komutunun minishelldeki karşılığıdır.
*/
void	cmd_env(t_data *data, t_token *node)
{
	t_env	*env;

	env = data->env;
	if (!node->next)
	{
		while (env)
		{
			if (env->value)
				printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
	}
	*get_exit_status() = 0;
}
