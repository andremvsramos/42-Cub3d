/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_multifd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 15:16:56 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Read data from a file descriptor into a buffer and concatenate it with the
 * existing stash, handling line breaks.
 *
 * @param fd      The file descriptor from which to read the data.
 * @param buffer  The buffer to store the read data.
 * @param stash   The existing stash to which the read data will
 *                be concatenated.
 *
 * @return The updated stash containing the concatenated data, or NULL if an
 *         error occurs during reading or memory allocation.
 *
 * @note This function appends the read data to the existing stash, handling
 *       line breaks.
 *       The stash is dynamically allocated and should be freed after use.
 */
static char	*ft_get_line(int fd, char *buffer, char *stash)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (0);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!stash)
			stash = ft_strdup("");
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

/**
 * Get the stash portion of a line, which contains characters after the first
 * occurrence of the newline character ('\n'). The stash is extracted from
 * the line and returned as a new dynamically allocated string.
 *
 * @param line The input line.
 *
 * @return The stash portion of the line as a new dynamically allocated string,
 *         or NULL if no stash is found or if memory allocation fails.
 *
 * @note The original line is modified, replacing the newline character ('\n')
 *       with the null terminator ('\0').
 *
 * @example
 *   char *line = "Hello, world!\nHow are you?\n";
 *   char *stash = ft_get_stash(line);
 *   // stash points to a new string containing "How are you?\n"
 *   // line is modified to "Hello, world!\0"
 *   // Remember to free the stash string after use.
 */
static char	*ft_get_stash(char *line)
{
	int		i;
	char	*stash;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (0);
	stash = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (stash[0] == '\0')
	{
		free(stash);
		stash = 0;
	}
	line[i + 1] = '\0';
	return (stash);
}

/**
 * Read the next line from a file descriptor, handling multiple file
 * descriptors simultaneously. Each file descriptor maintains its own
 * stash to handle lines that span across multiple read calls.
 *
 * @param fd The file descriptor from which to read the line.
 *
 * @return The next line read from the file descriptor, or NULL if an
 *         error occurs or the end of file is reached. The returned
 *         line is dynamically allocated and should be freed after use.
 *
 * @note This function uses a static array of stashes to store the
 *       remaining portions of lines for each file descriptor. It is
 *       the responsibility of the caller to manage the memory allocated
 *       for the returned line.
 */
char	*get_next_line_multifd(int fd)
{
	char		*buffer;
	char		*line;
	static char	*stash[4096];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (0);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	line = ft_get_line(fd, buffer, stash[fd]);
	free(buffer);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = 0;
		return (stash[fd]);
	}
	stash[fd] = ft_get_stash(line);
	return (line);
}
