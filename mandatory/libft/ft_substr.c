/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 14:59:42 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Create a substring of a given string.
 *
 * @param str   The original string.
 * @param start The starting index of the substring.
 * @param len   The length of the substring.
 *
 * @return A newly allocated string containing the substring, or an empty
 *         string if `start` is beyond the string length or `len` is zero.
 *         If memory allocation fails, NULL is returned.
 */
char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;

	if (!str)
		return (0);
	if (ft_strlen(str) <= start || !len)
		return (ft_strdup(""));
	if (ft_strlen(str) - start >= len)
		i = len + 1;
	else
		i = ft_strlen(str) - start + 1;
	substr = (char *)malloc(sizeof(char) * i);
	if (!substr)
		return (0);
	ft_strlcpy(substr, str + start, i);
	return (substr);
}
