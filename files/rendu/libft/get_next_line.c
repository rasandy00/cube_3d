#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

static char	*read_buffer(int fd, char *stash, char *buffer)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(stash), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!stash)
			stash = ft_strdup("");
		if (!stash)
			return (NULL);
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		free(temp);
		if (!stash)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

static char	*extract_line(char *stash)
{
	char	*line;
	size_t	i;
	size_t	len;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	len = i;
	line = ft_calloc(len + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*update_stash(char *stash)
{
	char	*new_stash;
	size_t	i;
	size_t	j;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	i++;
	new_stash = ft_calloc(ft_strlen(stash) - i + 1, sizeof(char));
	if (!new_stash)
		return (free(stash), NULL);
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	stash = read_buffer(fd, stash, buffer);
	free(buffer);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = update_stash(stash);
	return (line);
}