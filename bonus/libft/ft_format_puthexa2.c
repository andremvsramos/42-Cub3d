/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_puthexa2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 14:06:38 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Handles the padding of leading zeroes, the hexadecimal string, and trailing
 * spaces for a hexadecimal number, considering the alignment strategy
 * of the buffer structure.
 *
 * @param hexastr   The hexadecimal string representation.
 * @param values    Pointer to the buffer structure.
 * @param len       The length of the hexadecimal string.
 * @return          The number of characters printed.
 */
int	ft_phexamw1(char *hexastr, t_buffer *values, int len)
{
	int	count;

	count = 0;
	while ((values->precision--) > len)
		count += write(1, "0", 1);
	count += ft_putstr(hexastr);
	while ((values->width--) > len)
		count += write(1, " ", 1);
	return (count);
}

/**
 * Handles the padding of leading spaces, hash character, and leading zeroes
 * for a hexadecimal number, considering the alignment strategy of
 * the buffer structure.
 *
 * @param hexastr   The hexadecimal string representation.
 * @param values    Pointer to the buffer structure.
 * @param len       The length of the hexadecimal string.
 * @param base      The base character for hexadecimal conversion.
 * @return          The number of characters printed.
 */
int	ft_phexaw1(char *hexastr, t_buffer *values, int len, char base)
{
	int	count;

	count = 0;
	while ((values->width--) > len)
		count += write(1, " ", 1);
	if (values->hash && hexastr[0] != '0')
	{
		count += write(1, "0", 1);
		count += ft_putchar(base + 23);
	}
	while ((values->precision--) > (int)ft_strlen(hexastr))
		count += write(1, "0", 1);
	return (count);
}

/**
 * Handles the padding of leading zeroes for a hexadecimal number,
 * considering the alignment strategy of the buffer structure.
 *
 * @param hexastr   The hexadecimal string representation.
 * @param values    Pointer to the buffer structure.
 * @param len       The length of the hexadecimal string.
 * @param base      The base character for hexadecimal conversion.
 * @return          The number of characters printed.
 */
int	ft_phexa01(char *hexastr, t_buffer *values, int len, char base)
{
	int	count;

	count = 0;
	if (values->hash && hexastr[0] != '0')
	{
		count += write(1, "0", 1);
		count += ft_putchar(base + 23);
	}
	while ((values->width--) > len)
		count += write(1, "0", 1);
	while ((values->precision--) > len)
		count += write(1, "0", 1);
	return (count);
}
