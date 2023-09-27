/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_putnbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 14:06:10 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Prints a number with leading zeroes based on the width and precision
 * specified in the buffer structure.
 * It prints leading spaces, writes the minus sign, handles the
 * precision by printing leading zeroes, and prints the number without
 * the minus sign.
 *
 * @param number     The string representation of the number.
 * @param values     Pointer to the buffer structure.
 * @param precision  The precision value.
 * @return           The number of characters printed.
 */
static int	ft_print_zeroes(char *number, t_buffer *values, int precision)
{
	int	count;

	count = 0;
	if (values->width && values->precision)
	{
		while ((values->width--) > precision + (int)ft_strlen(number))
			count += write(1, " ", 1);
		count += write(1, "-", 1);
		while ((values->precision--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
	}
	else
	{
		count += write(1, "-", 1);
		while ((values->width--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
		while ((values->precision--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
	}
	count += ft_putstr(number + 1);
	return (count);
}

/**
 * Prints a number with a specified width and handles the precision
 * based on the buffer structure.
 * It prints leading spaces based on the width, writes the minus
 * sign, handles the precision by printing leading zeros, and
 * prints the number without the minus sign.
 *
 * @param number     The string representation of the number.
 * @param values     Pointer to the buffer structure.
 * @param precision  The precision value.
 * @return           The number of characters printed.
 */
static int	ft_print_width(char *number, t_buffer *values, int precision)
{
	int	count;

	count = 0;
	if (values->width && values->precision)
	{
		while ((values->width--) > precision)
			count += write(1, " ", 1);
		count += write(1, "-", 1);
		while ((values->precision--) > (int)ft_strlen(number) - 1)
			count += write(1, "0", 1);
	}
	else
	{
		while ((values->width--) > (int)ft_strlen(number))
			count += write(1, " ", 1);
		count += write(1, "-", 1);
		while ((values->precision--) > (int)ft_strlen(number) - 1)
			count += write(1, "0", 1);
	}
	count += ft_putstr(number + 1);
	return (count);
}

/**
 * Prints a negative number with a minus sign and handles the width
 * and precision based on the buffer structure.
 * It writes the minus sign, handles the precision by printing
 * leading zeros, and prints the number without the minus sign.
 * Finally, it handles the width by printing trailing spaces.
 *
 * @param number     The string representation of the negative number.
 * @param values     Pointer to the buffer structure.
 * @param precision  The precision value.
 * @return           The number of characters printed.
 */
static int	ft_print_minus_width(char *number, t_buffer *values, int precision)
{
	int	count;

	count = 0;
	if (values->width && values->precision)
	{
		count += write(1, "-", 1);
		while ((values->precision--) > (int)ft_strlen(number) - 1)
			count += write(1, "0", 1);
		count += ft_putstr(number + 1);
		while ((values->width--) > precision)
			count += write(1, " ", 1);
	}
	else
	{
		count += write(1, "-", 1);
		while ((values->precision--) > (int)ft_strlen(number) - 1)
			count += write(1, "0", 1);
		count += ft_putstr(number + 1);
		while ((values->width--) > (int)ft_strlen(number))
			count += write(1, " ", 1);
	}
	return (count);
}

/**
 * Formats and prints a signed integer number to the output, based
 * on the buffer structure.
 * If the number is non-negative, it calls ft_format_putposnbr function.
 * If the number is negative, it formats the number,
 * handles the width and precision, and prints the formatted
 * number to the output.
 *
 * @param values    Pointer to the buffer structure.
 * @param nb        The signed integer number to be printed.
 * @return          The number of characters printed.
 */
int	ft_format_putnbr(t_buffer *values, long long nb)
{
	int		count;
	char	*number;
	int		precision;

	count = 0;
	if (nb >= 0)
		count += ft_format_putposnbr(values, nb);
	else
	{
		number = ft_itoa(nb);
		precision = values->precision + 1;
		if (values->minus)
			count += ft_print_minus_width(number, values, precision);
		else if (values->zero)
			count += ft_print_zeroes(number, values, precision);
		else
			count += ft_print_width(number, values, precision);
		free(number);
	}
	return (count);
}
