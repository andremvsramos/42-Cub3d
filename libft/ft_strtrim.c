/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 14:58:52 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Trim leading and trailing characters from a string.
 *
 * @param str The string to trim.
 * @param set The set of characters to trim.
 *
 * @return A newly allocated string with leading and trailing characters
 *         from `set` removed. If no trimming is needed, a copy of the
 *         original string is returned.
 *         If memory allocation fails, NULL is returned.
 */
char	*ft_strtrim(char const *str, char const *set)
{
	char			*strtrim;
	unsigned int	start;
	unsigned int	end;

	start = 0;
	if (!str)
		return (0);
	end = ft_strlen(str);
	while (str[start] && ft_strchr((char *)set, str[start]))
		start++;
	while (end > start && ft_strchr((char *)set, str[end - 1]))
		end--;
	strtrim = ft_substr(str, start, (end - start));
	return (strtrim);
}
