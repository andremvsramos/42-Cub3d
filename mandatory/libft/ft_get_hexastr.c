/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_hexastr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 14:21:03 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Converts an unsigned long long integer to a hexadecimal string representation
 * using the specified base.
 *
 * @param nb    The unsigned long long integer to convert.
 * @param base  The base to use for the conversion (e.g., "0123456789abcdef").
 * @return      A dynamically allocated string representing
 * the hexadecimal value. The caller is responsible for freeing
 * the allocated memory.
 */
char	*ft_get_hexastr(unsigned long long nb, char *base)
{
	int		nb_length;
	char	*hexastr;

	nb_length = ft_getlength(nb, 16);
	hexastr = (char *)malloc(sizeof(char) * (nb_length + 1));
	if (!hexastr)
		return (0);
	hexastr[nb_length] = '\0';
	while (nb_length > 0)
	{
		hexastr[nb_length - 1] = base[nb % 16];
		nb /= 16;
		nb_length--;
	}
	return (hexastr);
}
