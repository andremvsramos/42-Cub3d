/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_putaddress.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 13:55:34 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Prints the formatted output with a zeroes flag for width alignment.
 *
 * @param hexastr   The hexadecimal string representation to be printed.
 * @param values    Pointer to the buffer structure.
 * @param precision The precision value for formatting.
 * @return          The number of characters printed.
 */
static int	ft_print_zeroes(char *hexastr, t_buffer *values, int precision)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen(hexastr);
	if (values->space || values->plus)
		len++;
	if (values->width && values->precision)
		count += ft_paddz1(hexastr, values, precision, len);
	else
		count += ft_paddz2(hexastr, values, len);
	count += ft_putstr(hexastr);
	return (count);
}

/**
 * Prints the formatted output with a width flag for alignment.
 *
 * @param hexastr   The hexadecimal string representation to be printed.
 * @param values    Pointer to the buffer structure.
 * @param precision The precision value for formatting.
 * @return          The number of characters printed.
 */
static int	ft_print_width(char *hexastr, t_buffer *values, int precision)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen(hexastr);
	if (values->space || values->plus)
		len++;
	if (ft_strncmp(hexastr, "(nil)", 6))
		len += 2;
	if (values->width && values->precision)
		count += ft_paddw1(hexastr, values, precision, len);
	else
		count += ft_paddw2(hexastr, values, len);
	count += ft_putstr(hexastr);
	return (count);
}

/**
 * Prints the formatted output with a minus flag for width
 * alignment (part 2).
 *
 * @param hexastr   The hexadecimal string representation to be printed.
 * @param values    Pointer to the buffer structure.
 * @param len       Length of the hexadecimal string.
 * @return          The number of characters printed.
 */
static int	ft_print_minus_width2(char *hexastr, t_buffer *values, int len)
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
	while ((values->width--) > len)
		count += write(1, " ", 1);
	return (count);
}

/**
 * Prints the formatted output with a minus flag for width alignment.
 *
 * @param hexastr   The hexadecimal string representation to be printed.
 * @param values    Pointer to the buffer structure.
 * @param precision The precision value for formatting.
 * @return          The number of characters printed.
 */
static int	ft_print_minus_width(char *hexastr, t_buffer *values, int precision)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen(hexastr);
	if (values->plus || values->space)
		precision++;
	if (values->width && values->precision)
		count += ft_paddmw1(hexastr, values, precision, len);
	else
		count += ft_print_minus_width2(hexastr, values, len);
	return (count);
}

/**
 * Formats and prints an address value to a buffer structure.
 *
 * @param values  Pointer to the buffer structure.
 * @param nb      The address value to be formatted and printed.
 * @return        The number of characters printed.
 */
int	ft_format_putaddress(t_buffer *values, unsigned long nb)
{
	int		count;
	int		precision;
	char	*base;
	char	*hexastr;

	count = 0;
	base = "0123456789abcdef";
	if (!nb)
		hexastr = ft_strdup("(nil)");
	else
		hexastr = ft_get_hexastr(nb, base);
	precision = values->precision + 2;
	if (values->minus)
		count += ft_print_minus_width(hexastr, values, precision);
	else if (values->zero)
		count += ft_print_zeroes(hexastr, values, precision);
	else
		count += ft_print_width(hexastr, values, precision);
	free(hexastr);
	return (count);
}
