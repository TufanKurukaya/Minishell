/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:15:00 by tkurukay          #+#    #+#             */
/*   Updated: 2024/08/18 11:37:30 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include "../../inc/minishell.h"

/*
- Creates a new token.
- Labels the created token as WORD and sets its value.
- Determines if the created value needs to be concatenated with the next value.
- Yeni bir token oluşturur.
- Oluşan token WORD olarak etiketlenir ve değerini ayarlar.
- Oluşan değerin bir sonraki değer ile birleşmesi gerekip grerkmediğine karar verir
*/
void	lexer_word(t_data *data, int *i)
{
	t_token	*node;
	int		end;

	end = *i;
	while (data->cmd[end] && !ft_strchr(" \t\v\f|<>\'\"", data->cmd[end]))
		end++;
	node = new_token(ft_substr(data->cmd, *i, end - *i), WORD);
	add_garbage_c(node->value);
	if (data->cmd[end] == '\'' || data->cmd[end] == '\"')
		node->flag = 1;
	add_token_back(&data->token, node);
	*i = end - 1;
}

/*
- Adds the pipe symbol as a token.
- Pipe işaretini token olarak ekler.
*/
void	lexer_pipe(t_data *data)
{
	t_token	*node;

	node = new_token(ft_strdup("|"), PIPE);
	add_garbage_c(node->value);
	add_token_back(&data->token, node);
}

/*
- Adds all redirections as tokens based on their labels.
- Tüm rediractionları etiketine göre token olarak ekler.
*/
void	lexer_redirect(t_data *data, int *i, enum e_token_type type)
{
	t_token	*node;
	char	sign[2];

	sign[0] = data->cmd[*i];
	sign[1] = '\0';
	if (sign[0] == '>' && sign[0] == data->cmd[*i + 1])
	{
		node = new_token(ft_strdup(">>"), APPEND);
		*i += 1;
	}
	else if (sign[0] == '<' && sign[0] == data->cmd[*i + 1])
	{
		node = new_token(ft_strdup("<<"), HEREDOC);
		*i += 1;
	}
	else
		node = new_token(ft_strdup(sign), type);
	add_garbage_c(node->value);
	add_token_back(&data->token, node);
}

/*
- Extracts the value between single quotes and adds it as a token.
- Extracts the value between double quotes and adds it as a token.
- In both cases, determines if concatenation with the next value is necessary.
- Tek tırnaklar arasındaki değeri alır ve token olarak ekler.
- Çift tırnaklar arasındaki değeri alır ve token olarak ekler.
- Her iki durumda da bir sonraki değer ile birleşmesi gerekip gerekmediğine karar verir.
*/
void	lexer_quote(t_data *data, int *i, enum e_token_type type)
{
	int		end;
	char	quote;
	t_token	*node;

	quote = data->cmd[*i];
	end = *i;
	while (data->cmd[++end] != quote)
	{
		if (data->cmd[end] == '\0')
		{
			data->syntax = 1;
			return ;
		}
	}
	node = new_token(ft_substr(data->cmd, *i + 1, end - *i - 1), type);
	add_garbage_c(node->value);
	if (ft_validchar(data->cmd[end + 1]) && !ft_strchr("|<>", data->cmd[end
				+ 1]))
		node->flag = 1;
	add_token_back(&data->token, node);
	*i = end;
}

/*
- Splits the incoming command into tokens.
- Gelen komutu tokenlara ayırır.
*/
void	lexer(t_data *data)
{
	int	i;

	i = -1;
	while (data->cmd[++i])
	{
		i = skip_space(data->cmd, i);
		if (data->cmd[i] == '\0')
			break ;
		if (data->cmd[i] == '\'')
			lexer_quote(data, &i, SINGLE_QUOTE);
		else if (data->cmd[i] == '\"')
			lexer_quote(data, &i, DOUBLE_QUOTE);
		else if (data->cmd[i] == '|')
			lexer_pipe(data);
		else if (data->cmd[i] == '<')
			lexer_redirect(data, &i, REDIRECT_IN);
		else if (data->cmd[i] == '>')
			lexer_redirect(data, &i, REDIRECT_OUT);
		else
			lexer_word(data, &i);
	}
}
