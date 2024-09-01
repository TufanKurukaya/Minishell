/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:13:11 by tkurukay          #+#    #+#             */
/*   Updated: 2024/08/18 12:22:08 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

/*
- Completely frees the t_malloc structure (linked list).
- t_malloc	yapısını(sıralı liste) tamamen serbest bırakır.
*/
void	gc_free(void)
{
	t_malloc	*tmp;
	t_malloc	*garbage_c;

	garbage_c = get_garbage_c()->next;
	while (garbage_c)
	{
		tmp = garbage_c;
		garbage_c = garbage_c->next;
		free(tmp->ptr);
		free(tmp);
	}
}

/*
- Removes and frees the memory area given as a parameter from the t_malloc structure (linked list).
- Parametre olarak verilen bellek alanını t_malloc yapısından(sıralı liste) çıkarır ve serbest bırakır.
*/
void	garbage_collecter(void *ptr)
{
	t_malloc	*garbage_c;
	t_malloc	*tmp;

	if (!ptr)
		return ;
	garbage_c = get_garbage_c();
	while (garbage_c)
	{
		if (garbage_c->ptr == ptr)
		{
			tmp->next = garbage_c->next;
			free(garbage_c);
			free(ptr);
			ptr = NULL;
			return ;
		}
		tmp = garbage_c;
		garbage_c = garbage_c->next;
	}
}

/*
- Removes the t_token structure (linked list) from the t_malloc structure (linked list) and completely frees it.
- t_token yapısını(sıralı liste) t_malloc yapısından(sıralı liste) çıkarır ve tamamen serbest bırakır.
*/
void	free_token(t_data *data)
{
	t_token	*token;
	t_token	*tmp;

	token = data->token;
	while (token)
	{
		tmp = token;
		token = token->next;
		garbage_collecter(tmp->value);
		garbage_collecter(tmp);
	}
	data->token = NULL;
}
