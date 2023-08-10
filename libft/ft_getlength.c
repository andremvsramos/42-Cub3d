/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getlength.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 14:21:27 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Calculates the length (number of digits) of an unsigned long long integer
 * in the specified base.
 *
 * @param n     The unsigned long long integer for which to calculate
 * the length.
 * @param base  The base to use for the calculation (e.g., 10 for decimal).
 * @return      The length of the integer in the specified base.
 */
int	ft_getlength(unsigned long long n, int base)
{
	int	length;

	length = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		length++;
		n /= base;
	}
	return (length);
}
