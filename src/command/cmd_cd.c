/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:14:24 by tkurukay          #+#    #+#             */
/*   Updated: 2024/08/18 11:36:24 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include "../../inc/minishell.h"
#include <stdio.h>
#include <unistd.h>

/*
- Updates the value of the OLDPWD key in the t_env structure (linked list). If it doesn't exist, creates a new one.
- t_env yapısındaki(sıralı liste) OLDPWD keyinin value'sini günceller. yoksa yenisini oluşturur.
*/
void	update_oldpwd(t_data *data, char *pwd)
{
	t_env	*node;

	node = get_env(data, "OLDPWD");
	if (!node)
	{
		node = gc_malloc(sizeof(t_env));
		node->key = "OLDPWD";
		node->value = pwd;
		node->next = data->env;
		data->env = node;
	}
	else
		node->value = pwd;
}

/*
- The equivalent of the cd command in Bash for the minishell.
- Bash deki cd komutunun minishelldeki karşılığıdır.
*/
void	cmd_cd(t_data *data, t_token *node, char *path, char *pwd)
{
	t_env	*env;

	env = get_env(data, "HOME");
	if (node && is_args(node))
		path = node->value;
	else if (!node && env)
		path = env->value;
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		*get_exit_status() = 1;
		return ;
	}
	pwd = get_pwd(data)->value;
	if (chdir(path) == -1)
		print_error(node, ": No such file or directory\n", 1);
	else
	{
		update_oldpwd(data, pwd);
		get_pwd(data)->value = getcwd(NULL, 0);
		if (!get_pwd(data)->value)
			perror("minishell");
		add_garbage_c(get_pwd(data)->value);
		*get_exit_status() = 0;
	}
}
