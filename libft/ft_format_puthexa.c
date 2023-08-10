/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_puthexa.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 14:07:00 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Prints a hexadecimal number with leading zeroes and a specified
 * width and precision, considering the alignment strategy of the
 * buffer structure.
 *
 * @param hexastr    The hexadecimal string representation to be printed.
 * @param values     Pointer to the buffer structure.
 * @param precision  The precision value.
 * @param base       The base character for hexadecimal conversion.
 * @return           The number of characters printed.
 */
static int	ft_p0(char *hexastr, t_buffer *values, int precision, char base)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen(hexastr);
	if (values->hash)
		len += 2;
	if (values->width && values->precision)
	{
		while ((values->width--) > precision + len)
			count += write(1, " ", 1);
		if (values->hash && hexastr[0] != '0')
		{
			count += write(1, "0", 1);
			count += ft_putchar(base + 23);
		}
		while ((values->precision--) > len)
			count += write(1, "0", 1);
	}
	else
		count += ft_phexa01(hexastr, values, len, base);
	count += ft_putstr(hexastr);
	return (count);
}

/**
 * Prints a hexadecimal number with a specified width and precision,
 * considering the alignment strategy of the buffer structure.
 *
 * @param hexastr    The hexadecimal string representation to be printed.
 * @param values     Pointer to the buffer structure.
 * @param precision  The precision value.
 * @param base       The base character for hexadecimal conversion.
 * @return           The number of characters printed.
 */
static int	ft_pw(char *hexastr, t_buffer *values, int precision, char base)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen(hexastr);
	if (values->hash && hexastr[0] != '0')
		len += 2;
	if (values->width && values->precision)
	{
		while ((values->width--) > precision)
			count += write(1, " ", 1);
		if (values->hash && hexastr[0] != '0')
		{
			count += write(1, "0", 1);
			count += ft_putchar(base + 23);
		}
		while ((values->precision--) > (int)ft_strlen(hexastr))
			count += write(1, "0", 1);
	}
	else
		count += ft_phexaw1(hexastr, values, len, base);
	count += ft_putstr(hexastr);
	return (count);
}

/**
 * Prints a hexadecimal number with a specified width and precision,
 * considering the alignment strategy of the buffer structure.
 *
 * @param hexastr    The hexadecimal string representation to be printed.
 * @param values     Pointer to the buffer structure.
 * @param precision  The precision value.
 * @param base       The base character for hexadecimal conversion.
 * @return           The number of characters printed.
 */
static int	ft_pmw(char *hexastr, t_buffer *values, int precision, char base)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen(hexastr);
	if (values->hash && hexastr[0] != '0')
	{
			count += write(1, "0", 1);
			count += ft_putchar(base + 23);
			len += 2;
			precision += 2;
	}
	if (values->width && values->precision)
	{
		while ((values->precision--) > (int)ft_strlen(hexastr))
			count += write(1, "0", 1);
		count += ft_putstr(hexastr);
		while ((values->width--) > precision)
			count += write(1, " ", 1);
	}
	else
		count += ft_phexamw1(hexastr, values, len);
	return (count);
}

/**
 * Formats and prints an unsigned long long integer as a hexadecimal value.
 *
 * @param values    Pointer to the buffer structure.
 * @param nb        The unsigned long long integer to be printed.
 * @return          The number of characters printed.
 */
int	ft_format_puthexa(t_buffer *values, unsigned long long nb)
{
	int		count;
	char	*hexastr;
	char	*base;
	int		precision;

	count = 0;
	if (values->conversion_type == 'x')
		base = "0123456789abcdef";
	if (values->conversion_type == 'X')
		base = "0123456789ABCDEF";
	hexastr = ft_get_hexastr(nb, base);
	precision = values->precision;
	if (values->minus)
		count += ft_pmw(hexastr, values, precision, base[10]);
	else if (values->zero)
		count += ft_p0(hexastr, values, precision, base[10]);
	else
		count += ft_pw(hexastr, values, precision, base[10]);
	free(hexastr);
	return (count);
}
