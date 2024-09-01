/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:15:03 by tkurukay          #+#    #+#             */
/*   Updated: 2024/08/18 12:08:34 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stddef.h>

/*
- Returns the last element of the given token list.
- Verilen token listesinin son elemanını döndürür.
*/
t_token	*last_token(t_token *node)
{
	if (node == NULL)
		return (0);
	while (node)
	{
		if (node->next == NULL)
			return (node);
		node = node->next;
	}
	return (node);
}

/*
- Creates a new token.
- Yeni bir token oluşturur.
*/
t_token	*new_token(char *value, enum e_token_type type)
{
	t_token	*token;

	token = gc_malloc(sizeof(t_token));
	*token = (t_token){.value = value, .type = type, .flag = 0};
	return (token);
}

/*
- Adds a new token to the end of the given token list.
- Verilen token listesinin sonuna yeni bir token ekler.
*/
void	add_token_back(t_token **node, t_token *new)
{
	t_token	*token;

	if (!new)
		return ;
	if (*node)
	{
		token = last_token(*node);
		new->prev = token;
		token->next = &*new;
	}
	else
		*node = new;
}
