/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:14:57 by tkurukay          #+#    #+#             */
/*   Updated: 2024/08/18 11:37:18 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include "../../inc/minishell.h"

/*
- Converts the given arguments (two-dimensional matrix) into tokens (linked list).
- Verilen argümanları(iki boyutlu matris) token olarak çevirir(sıralı liste).
*/
t_token	*args_to_token(char **args)
{
	t_token	*token;
	int		i;

	i = -1;
	token = NULL;
	while (args[++i])
		add_token_back(&token, new_token(args[i], WORD));
	return (token);
}

/*
- Concatenates the value of the given token.
- Sets the concatenated value as the new value and adjusts the links.
- Verilen tokenin value değerini birleştirir.
- Birleştirilen değeri yeni value olarak ayarlar ve bağlantıları düzenler.
*/
void	join_value(t_token *node)
{
	char	*new;

	new = ft_strjoin(node->prev->value, node->value);
	add_garbage_c(new);
	node->prev->value = new;
	node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	node->prev->flag = node->flag;
}

/*
- Sets the values that need to be expanded according to possible scenarios.
- Genişletilmesi gereken değerleri oluşabilecek durumlara göre ayarlar.
*/
void	expander_utils(t_data *data, t_token *node, char *tmp, int i)
{
	t_env	*env;
	char	*str;
	char	*env_key;
	char	*prev;

	env_key = NULL;
	str = NULL;
	env_key = ft_substr(tmp + 1, 0, i - 1);
	add_garbage_c(env_key);
	prev = ft_substr(node->value, 0, tmp - node->value);
	add_garbage_c(prev);
	env = get_env(data, env_key);
	if (env && env->value)
		str = ft_str_arr_join((char *[]){prev, env->value, tmp + i}, 3);
	else if (*env_key == '?')
		str = ft_str_arr_join((char *[]){prev, exit_status(), tmp + 2}, 3);
	else
		str = ft_str_arr_join((char *[]){prev, tmp + i}, 2);
	if (str == NULL)
		str = "";
	garbage_collecter(node->value);
	node->value = ft_strdup(str);
	add_garbage_c(node->value);
	garbage_collecter(str);
}

/*
- Selects the values that need to be expanded and initiates the expansion process.
- Genişletilmesi gereken değerleri seçer ve genişletme işlemini başlatır.
*/
void	select_expend_value(t_data *data, t_token *node)
{
	char	*tmp;
	int		i;

	tmp = ft_strchr(node->value, '$');
	while (tmp)
	{
		i = 1;
		while (tmp[i] && (ft_isalnum(tmp[i]) || tmp[i] == '?' || tmp[i] == '_'))
		{
			i++;
			if (ft_isdigit(tmp[1]))
				break ;
		}
		if (i == 1)
		{
			tmp++;
			tmp = ft_strchr(tmp, '$');
			continue ;
		}
		expander_utils(data, node, tmp, i);
		tmp = ft_strchr(node->value, '$');
	}
}

/*
- Calls the necessary functions for the expansion process.
- Genişletme işlemi için gerekli olan fonksiyonları çağırır.
*/
void	expander(t_data *data)
{
	t_token	*node;
	int		hedir;

	hedir = 0;
	node = data->token;
	while (node)
	{
		if (node->type == HEREDOC)
		{
			node = node->next;
			hedir = 1;
			continue ;
		}
		if ((node->type == WORD || node->type == DOUBLE_QUOTE) && !hedir)
			select_expend_value(data, node);
		if (node->prev && node->prev->flag)
			join_value(node);
		if (!node->flag)
			hedir = 0;
		node = node->next;
	}
}
