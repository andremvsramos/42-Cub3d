/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 14:57:58 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Locate the last occurrence of a character in a string.
 *
 * @param str The string to search in.
 * @param c   The character to search for.
 *
 * @return If the character `c` is found in the string `str`, a pointer to
 *         the last occurrence of `c` within `str` is returned; otherwise, NULL
 *         is returned.
 *         The comparison is performed using an unsigned char.
 */
char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (unsigned char)c)
			return (((char *)str) + i);
		i--;
	}
	return (0);
}
