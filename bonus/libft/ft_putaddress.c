/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 14:42:58 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Print the hexadecimal representation of an address.
 *
 * @param nb The address to be printed.
 *
 * @return The total number of characters printed.
 *         If the address is NULL (0), it also prints "(nil)" and returns
 *         the count.
 */
int	ft_putaddress(unsigned long nb)
{
	int	count;

	count = 0;
	if (!nb)
		return (ft_putstr("(nil)"));
	else
		write (1, "0x", 2);
	count += ft_puthexa(nb, 'x');
	return (count + 2);
}
