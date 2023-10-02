/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_putunsignnbr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 14:18:02 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Prints a formatted unsigned number with leading zeroes.
 *
 * @param number     The string representation of the unsigned number.
 * @param values     The buffer structure containing formatting information.
 * @param precision  The precision value specified for the formatting.
 * @return The total number of characters printed.
 */
static int	ft_print_zeroes(char *number, t_buffer *values, int precision)
{
	int	count;

	count = 0;
	if (values->width && values->precision)
	{
		while ((values->width--) > precision + (int)ft_strlen(number))
			count += write(1, " ", 1);
		while ((values->precision--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
	}
	else
	{
		while ((values->width--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
		while ((values->precision--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
	}
	count += ft_putstr(number);
	return (count);
}

/**
 * Prints a formatted unsigned number with a specified width.
 *
 * @param number     The string representation of the unsigned number.
 * @param values     The buffer structure containing formatting information.
 * @param precision  The precision value specified for the formatting.
 * @return The total number of characters printed.
 */
static int	ft_print_width(char *number, t_buffer *values, int precision)
{
	int	count;

	count = 0;
	if (values->width && values->precision)
	{
		while ((values->width--) > precision)
			count += write(1, " ", 1);
		while ((values->precision--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
	}
	else
	{
		while ((values->width--) > (int)ft_strlen(number))
			count += write(1, " ", 1);
		while ((values->precision--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
	}
	count += ft_putstr(number);
	return (count);
}

/**
 * Prints a formatted unsigned number with a minus sign and left-aligned width.
 *
 * @param number     The string representation of the unsigned number.
 * @param values     The buffer structure containing formatting information.
 * @param precision  The precision value specified for the formatting.
 * @return The total number of characters printed.
 */
static int	ft_print_minus_width(char *number, t_buffer *values, int precision)
{
	int	count;

	count = 0;
	if (values->width && values->precision)
	{
		while ((values->precision--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
		count += ft_putstr(number);
		while ((values->width--) > precision)
			count += write(1, " ", 1);
	}
	else
	{
		while ((values->precision--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
		count += ft_putstr(number);
		while ((values->width--) > (int)ft_strlen(number))
			count += write(1, " ", 1);
	}
	return (count);
}

/**
 * Formats and prints an unsigned integer number.
 *
 * @param values     The buffer structure containing formatting information.
 * @param nb         The unsigned number to be formatted and printed.
 * @return The total number of characters printed.
 */
int	ft_format_putunsignnbr(t_buffer *values, unsigned long long nb)
{
	int		count;
	char	*number;
	int		precision;

	count = 0;
	number = ft_utoa(nb);
	precision = values->precision;
	if (values->minus)
		count += ft_print_minus_width(number, values, precision);
	else if (values->zero)
		count += ft_print_zeroes(number, values, precision);
	else
		count += ft_print_width(number, values, precision);
	free(number);
	return (count);
}
