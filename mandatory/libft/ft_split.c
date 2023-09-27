/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 14:48:43 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Check if a character is a separator.
 *
 * @param a The character to be checked.
 * @param c The separator character.
 *
 * @return 1 if the character is a separator, 0 otherwise.
 */
int	check_separator(const char a, char c)
{
	if (a == c)
		return (1);
	return (0);
}

/**
 * Count the number of strings separated by a delimiter character in a string.
 *
 * @param str The string in which to count the strings.
 * @param c   The delimiter character.
 *
 * @return The number of strings separated by the delimiter character.
 */
int	count_strings(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] && check_separator(str[i], c))
			i++;
		if (str[i])
			count++;
		while (str[i] && !check_separator(str[i], c))
			i++;
	}
	return (count);
}

/**
 * Calculate the length of a string until a delimiter character is
 * encountered.
 *
 * @param str The string for which the length is calculated.
 * @param c   The delimiter character.
 *
 * @return The length of the string until the delimiter character is
 * encountered.
 */
int	ft_strlen_sep(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && !check_separator(str[i], c))
		i++;
	return (i);
}

/**
 * Extract a word from a string based on a delimiter character.
 *
 * @param str The string from which the word is extracted.
 * @param c   The delimiter character.
 *
 * @return The extracted word as a dynamically allocated string (char*).
 *         The caller is responsible for freeing the allocated memory.
 */
char	*ft_word(const char *str, char c)
{
	int		len_word;
	int		i;
	char	*word;

	len_word = ft_strlen_sep(str, c);
	i = 0;
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

/**
 * Split a string into an array of substrings based on a
 * delimiter character.
 *
 * @param str The string to be split.
 * @param c   The delimiter character.
 *
 * @return An array of strings (char**) containing the substrings.
 * The last element is set to NULL.
 */
char	**ft_split(const char *str, char c)
{
	char	**strings;
	int		i;
	int		wdcount;

	i = 0;
	if (!str)
		return (0);
	wdcount = count_strings(str, c);
	strings = (char **)malloc(sizeof(char *) * (wdcount + 1));
	while (*str)
	{
		while (*str && check_separator(*str, c))
			str++;
		if (*str)
		{
			strings[i] = ft_word(str, c);
			i++;
		}
		while (*str && !check_separator(*str, c))
			str++;
	}
	strings[i] = 0;
	return (strings);
}
/*
int	main(int ac, char **av)
{
	int		index;
	char	**split;
	(void)ac;
	split = ft_split(av[1], ' ');
	if (!split)
	{
		free(split);
		return (0);
	}
	index = 0;
	while (split[index])
	{
		printf("%s\n", split[index]);
		index++;
	}
	free(split);
	return (0);
}
*/
