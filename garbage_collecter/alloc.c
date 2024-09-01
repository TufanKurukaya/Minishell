/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:13:08 by tkurukay          #+#    #+#             */
/*   Updated: 2024/08/18 11:35:58 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/minishell.h"
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>

/*
- A static memory area is created and the address of this area is returned.
- Statik bellek alanı oluşturulur ve bu alanın adresi döndürülür.
*/
t_malloc	*get_garbage_c(void)
{
	static t_malloc	garbage_c = {NULL, NULL};

	return (&garbage_c);
}

/*
- Works like malloc, but adds the memory area to the t_malloc structure (linked list).
- Malloc gibi çalışır, ancak bellek alanını t_malloc yapısına(sıralı liste) ekler.
*/
void	*gc_malloc(unsigned int size)
{
	void		*ptr;
	t_malloc	*garbage_c;

	garbage_c = get_garbage_c();
	while (garbage_c->next)
		garbage_c = garbage_c->next;
	garbage_c->next = ft_calloc(1, sizeof(t_malloc));
	if (!garbage_c->next)
		ft_exit(strerror(errno));
	ptr = ft_calloc(1, size);
	if (!ptr)
		ft_exit(strerror(errno));
	*garbage_c->next = (t_malloc){.ptr = ptr, .next = NULL};
	return (ptr);
}

/*
- Adds the memory area given as a parameter to the t_malloc structure (linked list).
- Parametre olarak verilen bellek alanını t_malloc yapısına(sıralı liste) ekler.
*/
void	add_garbage_c(void *ptr)
{
	t_malloc	*garbage_c;

	if (!ptr)
		ft_exit(strerror(errno));
	garbage_c = get_garbage_c();
	while (garbage_c->next)
		garbage_c = garbage_c->next;
	garbage_c->next = ft_calloc(1, sizeof(t_malloc));
	if (!garbage_c->next)
	{
		free(ptr);
		ft_exit(strerror(errno));
	}
	*garbage_c->next = (t_malloc){.ptr = ptr, .next = NULL};
}
