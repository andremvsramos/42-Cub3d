/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_putaddress2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 13:58:22 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Performs padding and printing for the minus alignment strategy (part 1).
 *
 * @param hexastr   The hexadecimal string representation to be printed.
 * @param values    Pointer to the buffer structure.
 * @param precision The precision value for formatting.
 * @param len       Length of the hexadecimal string.
 * @return          The number of characters printed.
 */
int	ft_paddmw1(char *hexastr, t_buffer *values, int precision, int len)
{
	int	count;

	count = 0;
	if (values->space)
			count += write(1, " ", 1);
	if (values->plus)
			count += write(1, "+", 1);
	if (ft_strncmp(hexastr, "(nil)", 6))
	{
		count += write(1, "0x", 2);
		len += 2;
	}
	while ((values->precision--) > (int)ft_strlen(hexastr))
		count += write(1, "0", 1);
	count += ft_putstr(hexastr);
	while ((values->width--) > precision)
		count += write(1, " ", 1);
	return (count);
}

/**
 * Performs padding and printing for the zero alignment strategy (part 2).
 *
 * @param hexastr   The hexadecimal string representation to be printed.
 * @param values    Pointer to the buffer structure.
 * @param len       Length of the hexadecimal string.
 * @return          The number of characters printed.
 */
int	ft_paddz2(char *hexastr, t_buffer *values, int len)
{
	int	count;

	count = 0;
	if (values->space)
		count += write(1, " ", 1);
	if (values->plus)
		count += write(1, "+", 1);
	if (ft_strncmp(hexastr, "(nil)", 6))
	{
		count += write(1, "0x", 2);
		len += 2;
	}
	while ((values->width--) > len)
		count += write(1, "0", 1);
	while ((values->precision--) > len)
		count += write(1, "0", 1);
	return (count);
}

/**
 * Performs padding and printing for the zero alignment strategy (part 1).
 *
 * @param hexastr   The hexadecimal string representation to be printed.
 * @param values    Pointer to the buffer structure.
 * @param precision The precision value for formatting.
 * @param len       Length of the hexadecimal string.
 * @return          The number of characters printed.
 */
int	ft_paddz1(char *hexastr, t_buffer *values, int precision, int len)
{
	int	count;

	count = 0;
	while ((values->width--) > precision)
		count += write(1, " ", 1);
	if (values->space)
		count += write(1, " ", 1);
	if (values->plus)
		count += write(1, "+", 1);
	if (ft_strncmp(hexastr, "(nil)", 6))
	{
		count += write(1, "0x", 2);
		len += 2;
	}
	while ((values->precision--) > (int)ft_strlen(hexastr))
		count += write(1, "0", 1);
	return (count);
}

/**
 * Performs padding and printing for the width alignment strategy (part 2).
 *
 * @param hexastr   The hexadecimal string representation to be printed.
 * @param values    Pointer to the buffer structure.
 * @param len       Length of the hexadecimal string.
 * @return          The number of characters printed.
 */
int	ft_paddw2(char *hexastr, t_buffer *values, int len)
{
	int	count;

	count = 0;
	while ((values->width--) > len)
		count += write(1, " ", 1);
	if (values->space)
		count += write(1, " ", 1);
	if (values->plus)
		count += write(1, "+", 1);
	if (ft_strncmp(hexastr, "(nil)", 6))
		count += write(1, "0x", 2);
	while ((values->precision--) > (int)ft_strlen(hexastr))
		count += write(1, "0", 1);
	return (count);
}

/**
 * Performs padding and printing for the width alignment strategy.
 *
 * @param hexastr   The hexadecimal string representation to be printed.
 * @param values    Pointer to the buffer structure.
 * @param precision The precision value for formatting.
 * @param len       Length of the hexadecimal string.
 * @return          The number of characters printed.
 */
int	ft_paddw1(char *hexastr, t_buffer *values, int precision, int len)
{
	int	count;

	count = 0;
	while ((values->width--) > precision)
		count += write(1, " ", 1);
	if (values->space)
		count += write(1, " ", 1);
	if (values->plus)
		count += write(1, "+", 1);
	if (ft_strncmp(hexastr, "(nil)", 6))
	{
		count += write(1, "0x", 2);
		len += 2;
	}
	while ((values->precision--) > (int)ft_strlen(hexastr))
		count += write(1, "0", 1);
	return (count);
}
