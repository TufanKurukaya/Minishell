/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:13:21 by tkurukay          #+#    #+#             */
/*   Updated: 2024/08/12 11:13:22 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int x)
{
	if ((x <= 'z' && x >= 'a') || (x <= 'Z' && x >= 'A'))
		return (1);
	else if (x <= '9' && x >= '0')
		return (1);
	return (0);
}
