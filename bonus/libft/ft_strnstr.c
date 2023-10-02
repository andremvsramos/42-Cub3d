/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 14:57:11 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Locate a substring within a string, limited to a specified number of
 * characters.
 *
 * @param big    The string to search in.
 * @param little The substring to search for.
 * @param n      The maximum number of characters to search.
 *
 * @return If `little` is an empty string, `big` is returned; if `little` is
 *         found within `big` within the first `n` characters, a pointer to
 *         the first occurrence of `little` within `big` is returned;
 *         otherwise, NULL is returned. The comparison is case-sensitive.
 */
char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	if (!n)
		return (0);
	while (big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < n)
		{
			if (big[i + j] == '\0' && little[j] == '\0')
				return ((char *)big + i);
			j++;
		}
		if (little[j] == '\0')
			return ((char *)big + i);
		i++;
	}
	return (0);
}
