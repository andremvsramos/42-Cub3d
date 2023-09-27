/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_putposnbr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 14:13:27 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Prints a number with leading zeroes when the zero formatting flag is set.
 *
 * @param number     The number to be printed.
 * @param values     The buffer structure containing formatting information.
 * @param precision  The precision value.
 * @return The total number of characters printed.
 */
static int	ft_print_zeroes(char *number, t_buffer *values, int precision)
{
	int	count;

	count = 0;
	if (values->space)
		count += write(1, " ", 1);
	if (values->plus)
		count += write(1, "+", 1);
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
 * Prints a number with a specified width and precision when the
 * width and precision formatting flags are set.
 *
 * @param number     The number to be printed.
 * @param values     The buffer structure containing formatting
 * information.
 * @param precision  The precision value.
 * @return The total number of characters printed.
 */
static int	ft_print_width(char *number, t_buffer *values, int precision)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen(number);
	if (values->space || values->plus)
		len++;
	if (values->width && values->precision)
	{
		while ((values->width--) > precision)
			count += write(1, " ", 1);
		while ((values->precision--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
	}
	else
		count += ft_print_posnbrw2(number, values, len);
	if (values->space)
		count += write(1, " ", 1);
	if (values->plus)
		count += write(1, "+", 1);
	count += ft_putstr(number);
	return (count);
}

/**
 * Prints a negative number with a specified width and precision
 * when the precision is greater than the number length.
 * This function is a helper function used by ft_print_minus_width.
 * It handles the case where the width and precision formatting
 * flags are not set.
 *
 * @param number   The number to be printed (excluding the sign).
 * @param values   The buffer structure containing formatting
 * information.
 * @return The total number of characters printed.
 */
static int	ft_print_minus_width2(char *number, t_buffer *values)
{
	int	count;

	count = 0;
	while ((values->precision--) > (int)ft_strlen(number))
		count += write(1, "0", 1);
	count += ft_putstr(number);
	while ((values->width--) > (int)ft_strlen(number))
		count += write(1, " ", 1);
	return (count);
}

/**
 * Prints a negative number with a specified width and precision,
 * considering flags.
 * If the plus flag is set, a plus sign (+) will be printed
 * before the number.
 * If the space flag is set, a space character will be printed
 * before the number.
 * The width specifies the minimum field width, padding the
 * output with spaces if necessary.
 * The precision specifies the minimum number of digits to be
 * printed, padding with leading zeros if necessary.
 *
 * @param number   The number to be printed (excluding the sign).
 * @param values   The buffer structure containing formatting information.
 * @param precision The precision value specified in the buffer structure.
 * @return The total number of characters printed.
 */
static int	ft_print_minus_width(char *number, t_buffer *values, int precision)
{
	int	count;

	count = 0;
	if (values->plus || values->space)
		precision++;
	if (values->space)
		count += write(1, " ", 1);
	if (values->plus)
		count += write(1, "+", 1);
	if (values->width && values->precision)
	{
		while ((values->precision--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
		count += ft_putstr(number);
		while ((values->width--) > precision)
			count += write(1, " ", 1);
	}
	else
		count += ft_print_minus_width2(number, values);
	return (count);
}

/**
 * Formats and prints an unsigned number based on the buffer structure.
 * It converts the number to a string representation, handles
 * the precision and width, and prints the formatted number.
 *
 * @param values     Pointer to the buffer structure.
 * @param nb         The unsigned number to be formatted and printed.
 * @return           The number of characters printed.
 */
int	ft_format_putposnbr(t_buffer *values, unsigned long long nb)
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
