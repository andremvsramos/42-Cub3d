/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 14:37:40 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Compare memory blocks.
 *
 * This function compares the values of two memory blocks, pointed to by s1
 * and s2, up to a specified number of bytes (n). It treats the memory blocks
 * as arrays of unsigned characters (unsigned char*) to ensure proper byte-wise
 * comparison.
 *
 * @param s1 A pointer to the first memory block to compare.
 * @param s2 A pointer to the second memory block to compare.
 * @param n The number of bytes to compare.
 * @return An integer indicating the comparison result:
 *         - If s1 is greater than s2, the return value will be a positive
 * integer.
 *         - If s1 is less than s2, the return value will be a negative
 * integer.
 *         - If s1 is equal to s2, the return value will be zero.
 */
int	ft_memcmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
