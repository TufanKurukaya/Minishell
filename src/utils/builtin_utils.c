/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:15:40 by tkurukay          #+#    #+#             */
/*   Updated: 2024/08/18 11:31:33 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include "../../inc/minishell.h"
#include <unistd.h>

/*
- Checks for built-in commands.
- Builtin komutlarının kontrolünü yapar.
*/
int	builtins(char *path)
{
	if (!is_echo(path, "echo"))
		return (1);
	if (ft_strcmp(path, "cd") == 0)
		return (1);
	if (ft_strcmp(path, "pwd") == 0)
		return (1);
	if (ft_strcmp(path, "export") == 0)
		return (1);
	if (ft_strcmp(path, "unset") == 0)
		return (1);
	if (ft_strcmp(path, "env") == 0)
		return (1);
	if (ft_strcmp(path, "exit") == 0)
		return (1);
	return (0);
}

/*
- Checks if the command starts with ./ or /
- Komutun başında ./ veya / var mı kontrol eder.
*/
int	is_path(char *str)
{
	return ((str[0] == '.' && str[1] == '/') || str[0] == '/');
}

/*
- Concatenates the entered command with paths in the path variable and checks if it is an executable file.
- Girilen komutu path değişkenindeki yollarla birleştirir ve çalıştırılabilir dosya olup olmadığını kontrol eder.
*/
char	*check_path(char **path, t_token *node)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (path[i])
	{
		tmp = ft_str_arr_join((char *[]){path[i], "/", node->value}, 3);
		if (access(tmp, F_OK) == 0)
		{
			if (access(tmp, X_OK) == 0)
				return (tmp);
			else
			{
				print_error(node, ": Permission denied\n", 126);
				return (NULL);
			}
		}
		i++;
		garbage_collecter(tmp);
	}
	return (print_error(node, ": command not found\n", 127), NULL);
}


/*
- Allows the child process to execute built-in commands.
- Çocuk processin builtinleri çalıştırmasını sağlar.
*/
int	my_builtin(t_data *data, char **args)
{
	t_token	*node;

	if (args)
	{
		node = args_to_token(args);
		if (!ft_strcmp(args[0], "cd"))
			return (cmd_cd(data, node->next, NULL, NULL), 1);
		else if (!ft_strcmp(args[0], "pwd"))
			return (cmd_pwd(), 1);
		else if (!is_echo(args[0], "echo"))
			return (cmd_echo(node->next), 1);
		else if (!ft_strcmp(args[0], "env"))
			return (cmd_env(data, node), 1);
		else if (!ft_strcmp(args[0], "export"))
			return (cmd_export(data, node->next), 1);
		else if (!ft_strcmp(args[0], "unset"))
			return (cmd_unset(data, node->next), 1);
		else if (!ft_strcmp(args[0], "exit"))
			return (cmd_exit(node->next), 1);
	}
	return (0);
}

/*
- Allows the main process to execute built-in commands.
- Ana processin builtinleri çalıştırmasını sağlar.
*/
void	pars_single_cmd(t_data *data)
{
	if (is_args(data->token))
	{
		while (data->token && *data->token->value == '\0'
			&& data->token->type == WORD)
			data->token = data->token->next;
		if (!data->token)
			return ;
		if (!ft_strcmp(data->token->value, "cd"))
			cmd_cd(data, data->token->next, NULL, NULL);
		else if (!ft_strcmp(data->token->value, "pwd"))
			cmd_pwd();
		else if (!is_echo(data->token->value, "echo"))
			cmd_echo(data->token->next);
		else if (!ft_strcmp(data->token->value, "env"))
			cmd_env(data, data->token);
		else if (!ft_strcmp(data->token->value, "export"))
			cmd_export(data, data->token->next);
		else if (!ft_strcmp(data->token->value, "unset"))
			cmd_unset(data, data->token->next);
		else if (!ft_strcmp(data->token->value, "exit"))
			cmd_exit(data->token->next);
		else
			use_execve(data);
	}
}
