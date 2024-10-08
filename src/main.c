/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:16:38 by tkurukay          #+#    #+#             */
/*   Updated: 2024/08/18 11:34:54 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>

int		g_signal = 0;

/*
- Initializes the data within the struct that holds all of minishell's data.
- minishell'in tüm verilerini tutan struct'in içindeki verileri başlatır.
*/
void	initilazor(t_data *data)
{
	data->env = gc_malloc(sizeof(t_env));
	data->token = NULL;
	data->cmd = 0;
	data->syntax = 0;
	data->in_fd = 0;
	data->pid = 0;
	data->pipes = 0;
	data->here = 0;
}

/*
- Creates the necessary env variables for minishell.
- minishell için gerekli env değişkenlerini oluşturur.
*/
void	create_env(char **envp, t_data *data)
{
	t_env	*node;
	int		i;
	char	*tmp;

	i = -1;
	node = data->env;
	while (envp[++i])
	{
		tmp = ft_strchr(envp[i], '=');
		data->env->key = ft_substr(envp[i], 0, tmp - envp[i]);
		data->env->value = ft_substr(envp[i], (tmp - envp[i]) + 1,
				ft_strlen(envp[i]));
		add_garbage_c(data->env->key);
		add_garbage_c(data->env->value);
		if (envp[i + 1])
			data->env->next = gc_malloc(sizeof(t_env));
		data->env = data->env->next;
	}
	data->env = node;
	update_oldpwd(data, NULL);
}

/*
- Returns the env variable based on the key value.
- key değerine göre env değişkenini döndürür.
*/
t_env	*get_env(t_data *data, char *key)
{
	t_env	*node;

	node = data->env;
	while (node)
	{
		if (!ft_strcmp(node->key, key))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/*
- The main loop of minishell.
- minishell'in ana döngüsüdür.
*/
void	cycle(t_data *data)
{
	while (1)
	{
		g_signal = PROMT_SIG;
		signal_base();
		data->cmd = readline("omega bash-0.1$ ");
		if (!data->cmd)
			break ;
		add_garbage_c(data->cmd);
		add_history(data->cmd);
		lexer(data);
		if (data->syntax)
		{
			printf("syntax error\n");
			free_token(data);
			garbage_collecter(data->cmd);
			data->syntax = 0;
			continue ;
		}
		expander(data);
		parser(data);
		free_token(data);
		garbage_collecter(data->cmd);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	if (ac >= 2)
		return (0);
	initilazor(&data);
	if (env)
		create_env(env, &data);
	signal(SIGINT, handle_sigint);
	cycle(&data);
	gc_free();
	return (0);
}
