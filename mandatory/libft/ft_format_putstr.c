/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_putstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 14:14:49 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Prints a string with right alignment and optional padding.
 *
 * @param str        The string to be printed.
 * @param values     The buffer structure containing formatting information.
 * @return The total number of characters printed.
 */
static int	ft_print_width(char *str, t_buffer *values)
{
	int	count;

	count = 0;
	while (values->width > (int)ft_strlen(str))
	{
		count += write(1, " ", 1);
		values->width--;
	}
	count += ft_putstr(str);
	free(str);
	return (count);
}

/**
 * Prints a string with left alignment and optional padding.
 *
 * @param str        The string to be printed.
 * @param values     The buffer structure containing formatting information.
 * @return The total number of characters printed.
 */
static int	ft_print_minus_width(char *str, t_buffer *values)
{
	int	count;

	count = 0;
	{
		count += ft_putstr(str);
		while (values->width > (int)ft_strlen(str))
		{
			count += write(1, " ", 1);
			values->width--;
		}
	}
	free(str);
	return (count);
}

/**
 * Formats and prints a string.
 *
 * @param values     The buffer structure containing formatting information.
 * @param str        The string to be printed.
 * @return The total number of characters printed.
 */
int	ft_format_putstr(t_buffer *values, char *str)
{
	int		count;
	char	*aux;

	count = 0;
	if (!str)
		aux = ft_strdup("(null)");
	else
	{
		aux = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
		if (!aux)
			return (0);
		ft_strlcpy(aux, str, ft_strlen(str) + 1);
	}
	if (values->point)
		ft_strlcpy(aux, str, values->precision + 1);
	if (values->minus == 1)
		count += ft_print_minus_width(aux, values);
	else
		count += ft_print_width(aux, values);
	return (count);
}
