/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 15:01:35 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Calculate the length of an unsigned long long integer.
 *
 * @param n The unsigned long long integer.
 *
 * @return The number of digits in the unsigned long long integer.
 */
static int	ft_length(unsigned long long n)
{
	int	length;

	length = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		length++;
		n = n / 10;
	}
	return (length);
}

/**
 * Convert an unsigned long long integer to a string representation.
 *
 * @param n The unsigned long long integer to be converted.
 *
 * @return The string representation of the unsigned long long integer.
 *         The returned string must be freed after use.
 */
char	*ft_utoa(unsigned long long n)
{
	char	*result;
	int		length;

	length = ft_length(n);
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (0);
	result[length] = '\0';
	if (n == 0)
		result[0] = '0';
	while (n != 0)
	{
		length--;
		result[length] = ft_abs(n % 10) + '0';
		n = n / 10;
	}
	return (result);
}
