/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 14:54:45 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Apply a function to each character of a string, creating a new string with
 * the results.
 *
 * @param s The input string.
 * @param f The function to apply to each character.
 *
 * @return A new dynamically allocated string resulting from applying the
 *         given function to each character of the input string. If the input
 *         string or the function is NULL, it returns NULL. Note that the
 *         returned string must be freed to avoid memory leaks.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*a;

	i = 0;
	if (!s || !f)
		return (0);
	a = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!a)
		return (0);
	while (s[i])
	{
		a[i] = f(i, s[i]);
		i++;
	}
	a[i] = '\0';
	return (a);
}
