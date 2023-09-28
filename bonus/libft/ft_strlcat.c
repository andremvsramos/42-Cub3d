/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 14:52:14 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Concatenate two strings safely with a size limit.
 *
 * @param dest The destination string to which the source string
 *             will be appended.
 * @param src  The source string to be appended to the destination string.
 * @param size The maximum size of the resulting string (including
 *             the null-terminator).
 *
 * @return The total length of the concatenated string (initial length of
 *         dest + length of src), up to the given size limit. If the resulting
 *         string exceeds the size limit, it returns the size limit + the
 *         length of src. Note that the destination string is modified.
 */
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	destlen;
	size_t	srclen;
	size_t	a;

	i = 0;
	if (!size)
		return (ft_strlen((char *)src));
	destlen = ft_strlen((char *)dest);
	srclen = ft_strlen((char *)src);
	a = destlen;
	if (size <= destlen)
		return (srclen + size);
	while (src[i] && i < size - destlen - 1)
		dest[a++] = src[i++];
	dest[a] = '\0';
	return (destlen + srclen);
}
