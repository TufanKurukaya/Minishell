/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:14:39 by tkurukay          #+#    #+#             */
/*   Updated: 2024/08/18 11:36:47 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <unistd.h>

/*
- Gets the current directory from env variables. If the variable doesn't exist, creates a new one.
- Bulunduğu dizini env değişkenlerinden alır. Değiken yoksa yenisini oluşturur.
*/
t_env	*get_pwd(t_data *data)
{
	t_env	*node;

	node = get_env(data, "PWD");
	if (!node)
	{
		node = gc_malloc(sizeof(t_env));
		node->key = "PWD";
		node->value = getcwd(NULL, 0);
		if (!node->value)
			ft_exit(strerror(errno));
		add_garbage_c(node->value);
		node->next = data->env;
		data->env = node;
	}
	return (node);
}

/*
- The equivalent of the pwd command in Bash for the minishell.
- Bash deki pwd komutunun minishelldeki karşılığıdır.
*/
void	cmd_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_exit(strerror(errno));
	add_garbage_c(pwd);
	printf("%s\n", pwd);
	*get_exit_status() = 0;
}
