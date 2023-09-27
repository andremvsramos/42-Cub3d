/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/27 23:55:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Extracts the width or precision values from the format buffer and stores
 * them in the corresponding fields of the t_buffer struct.
 *
 * @param values  A pointer to the t_buffer struct to store the extractedvalues.
 * @param buffer  The format buffer containing the width or precision specifier.
 * @return        The number of characters consumed from the buffer.
 */
static int	ft_get_values(t_buffer *values, char *buffer)
{
	if (!values->point)
	{
		values->width = ft_atoi(buffer);
		return (ft_getlength(values->width, 10) - 1);
	}
	else
	{
		values->precision = ft_atoi(buffer);
		return (ft_getlength(values->precision, 10) - 1);
	}
}

/**
 * Reads the format buffer and populates the corresponding fields in the
 * t_buffer struct.
 *
 * @param buffer  The format buffer to be parsed.
 * @param values  A pointer to the t_buffer struct to
 * store the parsed values.
 */
static void	ft_read_buffer(char *buffer, t_buffer *values)
{
	while (*buffer)
	{
		if (*buffer == '-')
			values->minus = 1;
		else if (*buffer == '+')
			values->plus = 1;
		else if (*buffer == ' ')
			values->space = 1;
		else if (*buffer == '0')
			values->zero = 1;
		else if (*buffer == '#')
			values->hash = 1;
		else if (*buffer == '.')
			values->point = 1;
		else if ((*buffer >= '1' && *buffer <= '9'))
			buffer += ft_get_values(values, buffer);
		buffer++;
	}
}

/**
 * Initializes the fields of a t_buffer struct with default values.
 *
 * @param values  A pointer to the t_buffer struct to be initialized.
 */
static void	ft_init_format_buffer(t_buffer *values)
{
	values->conversion_type = 0;
	values->space = 0;
	values->zero = 0;
	values->plus = 0;
	values->minus = 0;
	values->hash = 0;
	values->point = 0;
	values->width = 0;
	values->precision = 0;
}

/**
 * Parses the format specifier and extracts the relevant information into a
 * t_buffer struct.
 *
 * @param str   The pointer to the format string.
 * @param args  The va_list containing the arguments.
 * @return      The result of calling ft_check_type_format with the
 * extracted information.
 */
int	ft_get_format_buffer(const char **str, va_list args)
{
	t_buffer	values;
	char		*buffer;
	int			i;

	i = 0;
	ft_init_format_buffer(&values);
	while (!ft_strchr(TYPE, (*str)[i]))
		i++;
	buffer = ft_substr(*str, 0, i);
	ft_read_buffer(buffer, &values);
	(*str) += i;
	values.conversion_type = **str;
	free(buffer);
	return (ft_check_type_format(args, &values));
}
