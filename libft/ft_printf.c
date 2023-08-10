/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 15:21:34 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Check and handle the format specifier in the printf-like function.
 *
 * This function checks the conversion type specified in the t_buffer struct
 * and performs the appropriate action based on the type. The supported types
 * and corresponding actions are:
 * - 's': Print a string (char *) argument
 * - 'c': Print a character (int) argument
 * - 'd' or 'i': Print a signed decimal integer argument
 * - 'u': Print an unsigned decimal integer argument
 * - 'x' or 'X': Print a hexadecimal integer argument (lowercase or uppercase)
 * - 'p': Print a pointer address argument
 *
 * @param args   The va_list containing the variable arguments.
 * @param values The t_buffer struct containing the format and buffer
 *               information.
 *
 * @return The number of characters successfully printed.
 */
int	ft_check_type_format(va_list args, t_buffer *values)
{
	int	count;

	count = 0;
	if (values->conversion_type == 's')
		count += ft_format_putstr(values, va_arg(args, char *));
	if (values->conversion_type == 'c')
		count += ft_format_putchar(values, va_arg(args, int));
	if (values->conversion_type == 'd' || values->conversion_type == 'i')
		count += ft_format_putnbr(values, va_arg(args, int));
	if (values->conversion_type == 'u')
		count += ft_format_putunsignnbr(values, va_arg(args, unsigned int));
	if (values->conversion_type == 'x' || values->conversion_type == 'X')
		count += ft_format_puthexa(values, va_arg(args, unsigned int));
	if (values->conversion_type == 'p')
		count += ft_format_putaddress(values, va_arg(args, unsigned long));
	return (count);
}

/**
 * Check and handle the format specifier in the printf-like function.
 *
 * This function checks the provided format specifier and performs the
 * appropriate action based on the specifier. The supported specifiers and
 * corresponding actions are:
 * - 's': Print a string (char *) argument
 * - 'c': Print a character (int) argument
 * - 'd' or 'i': Print a signed decimal integer argument
 * - 'u': Print an unsigned decimal integer argument
 * - 'x' or 'X': Print a hexadecimal integer argument (lowercase or uppercase)
 * - 'p': Print a pointer address argument
 *
 * @param c    The format specifier character.
 * @param args The va_list containing the variable arguments.
 *
 * @return The number of characters successfully printed.
 */
static int	ft_check(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 's')
		count += ft_putstr(va_arg(args, char *));
	if (c == 'c')
		count += ft_putchar(va_arg(args, int));
	if (c == 'd' || c == 'i')
		count += ft_putnbr(va_arg(args, int));
	if (c == 'u')
		count += ft_putunsignednbr(va_arg(args, unsigned int));
	if (c == 'x' || c == 'X')
		count += ft_puthexa(va_arg(args, unsigned int), c);
	if (c == 'p')
		count += ft_putaddress(va_arg(args, unsigned long));
	return (count);
}

/**
 * Custom printf implementation that supports basic format specifiers.
 *
 * This function formats and prints output to the standard output stream based
 * on the format string provided. It supports the following format specifiers:
 * - %d or %i: Signed decimal integer
 * - %s: String of characters
 * - %c: Single character
 * - %%: Print a '%' character
 *
 * Additional flags and modifiers are not supported in this implementation.
 *
 * @param str The format string containing the text and format specifiers.
 * @param ... Additional arguments corresponding to the format specifiers.
 *
 * @return The number of characters successfully printed.
 */
int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (*str == '%')
				count += write(1, "%", 1);
			else if (ft_strchr(TYPE, *str))
				count += ft_check(*str, args);
			else if (ft_strchr(FLAGS, *str) || ft_isdigit(*str))
				count += ft_get_format_buffer(&str, args);
		}
		else
			count += ft_putchar(*str);
		str++;
	}
	va_end(args);
	return (count);
}

/* int	main(void)
{
	int	i = 0;

	i = ft_printf("|%c|\n", 'P');
	printf("%d\n", i);
	i = ft_printf("|%10c|\n", 'P');
	printf("%d\n", i);
	i = ft_printf("|%-10c|\n", 'P');
	printf("%d\n", i);
	i = ft_printf("|%10-c|\n", 'P');
	printf("%d\n", i);
	i = ft_printf("|%10x|\n", 42);
	printf("%d\n", i);
    i = ft_printf("|%#10x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("|%10#x|\n", 42);
	printf("%d\n", i);
	i = printf("1|%10x|\n", 42);
	printf("%d\n", i);
    i = printf("2|%#10x|\n", 42);
	printf("%d\n", i);
	i = printf("3|%-10x|\n", 42);
	printf("%d\n", i);
    i = printf("4|%-#10x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("1|%10x|\n", 42);
	printf("%d\n", i);
    i = ft_printf("2|%#10x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("3|%-10x|\n", 42);
	printf("%d\n", i);
    i = ft_printf("4|%-#10x|\n", 42);
	printf("%d\n", i);
	i = printf("5|%010x|\n", 42);
	printf("%d\n", i);
    i = printf("6|%0#10x|\n", 42);
	printf("%d\n", i);
    i = printf("7|%#010x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("5|%010x|\n", 42);
	printf("%d\n", i);
    i = ft_printf("6|%0#10x|\n", 42);
	printf("%d\n", i);
    i = ft_printf("7|%#010x|\n", 42);
	printf("%d\n", i);
	i = printf(".10x - |%.10x|\n", 42);
	printf("%d\n", i);
	i = ft_printf(".10x - |%.10x|\n", 42);
	printf("%d\n", i);
    i = printf("10.x - |%10.x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("10.x - |%10.x|\n", 42);
	printf("%d\n", i);
	i = printf("#.5x - |%#.5x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("#.5x - |%#.5x|\n", 42);
	printf("%d\n", i);
	i = printf("#10.x - |%#10.x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("#10.x - |%#10.x|\n", 42);
	printf("%d\n", i);
	i = printf("#.1x - |%#.1x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("#.1x - |%#.1x|\n", 42);
	printf("%d\n", i);
    i = printf("#1.x - |%#1.x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("#1.x - |%#1.x|\n", 42);
	printf("%d\n", i);
	i = printf(".3x - |%.3x|\n", 42);
	printf("%d\n", i);
	i = ft_printf(".3x - |%.3x|\n", 42);
	printf("%d\n", i);
    i = printf("4.x - |%4.x|\n", 42);
	printf("%d\n", i);
	i = printf("4.x - |%4.x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("|%X|\n", 42);
	printf("%d\n", i);
    i = ft_printf("|%#X|\n", 10);
	printf("%d\n", i);
	return(0);
} */
