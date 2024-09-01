/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:15:52 by tkurukay          #+#    #+#             */
/*   Updated: 2024/08/18 11:38:09 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include "../../inc/minishell.h"
#include <limits.h>

/*
- Concatenates the given double character strings.
- Verilen çift işaretli karakter dizisini birleştirir.
*/
char	*ft_str_arr_join(char **str_list, unsigned int str_count)
{
	unsigned int	total_len;
	unsigned int	result_len;
	unsigned int	i;
	char			*result;

	i = 0;
	total_len = 0;
	if (!str_list)
		return (NULL);
	while (i < str_count)
	{
		total_len += ft_strlen(str_list[i]);
		i++;
	}
	if (total_len == 0)
		return (NULL);
	result = (char *)gc_malloc(sizeof(char) * (total_len + 1));
	i = -1;
	result_len = 0;
	while (++i < str_count && str_list[i])
		result_len += ft_strlcpy(&result[result_len], str_list[i], UINT_MAX);
	return (result);
}

/*
- Checks if tokens are redirects.
- Tokenlerin redirect olup olmadığını kontrol eder.
*/
int	rdir(t_token *node)
{
	if (node->type == HEREDOC)
		return (2);
	return (node->type == REDIRECT_IN || node->type == REDIRECT_OUT
		|| node->type == APPEND);
}

/*
- Checks if tokens are arguments.
- Tokenlerin argüman olup olmadığını kontrol eder.
*/
int	is_args(t_token *node)
{
	if (node->type == SINGLE_QUOTE)
		return (2);
	return (node->type == WORD || node->type == DOUBLE_QUOTE);
}

/*
- Skips spaces in the given string.
- Verilen karakter dizisindeki boşlukları atlar.
*/
int	skip_space(char *str, int i)
{
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

/*
- Checks if the given character is printable and not a space.
- Verilen karakterin yazdırılabilir ve boşluk olmadığını kontrol eder.
*/
int	ft_validchar(int c)
{
	return (!ft_isspace(c) && ft_isprint(c));
}
