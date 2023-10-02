/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 14:49:19 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Locate the first occurrence of a character in a string.
 *
 * @param str The string in which to search for the character.
 * @param c   The character to be located.
 *
 * @return A pointer to the first occurrence of the character in the string.
 *         If the character is not found, it returns NULL.
 */
char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != (unsigned char)c)
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (((char *)str) + i);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	printf("%s\n", strchr("teste", 1024));
	printf("%s\n", ft_strchr("teste", 1024));
	return (0);
}*/
