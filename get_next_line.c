/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:10:53 by vsharma           #+#    #+#             */
/*   Updated: 2023/10/14 17:31:21 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_rest_str(char *rest_str)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (rest_str[i] && rest_str[i] != '\n')
		i++;
	if (!rest_str[i])
	{
		free(rest_str);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(rest_str) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (rest_str[i])
	{
		str[j++] = rest_str[i++];
	}
	str[j] = '\0';
	free(rest_str);
	return (str);
}

char	*ft_get_line(char *rest_str)
{
	int		i;
	char	*str;

	i = 0;
	if (!rest_str[i])
		return (NULL);
	while (rest_str[i] && rest_str[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (rest_str[i] && rest_str[i] != '\n')
	{
		str[i] = rest_str[i];
		i++;
	}
	if (rest_str[i] == '\n')
	{
		str[i] = rest_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_buf_str(int fd, char *rest_str)
{
	char	*buf;
	int		bytes;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	bytes = 0;
	while (bytes != 1  && (!ft_strchr(rest_str, '\n')))
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buf);
			free(rest_str);
			return (NULL);
		}
		buf[bytes] = '\0';
		rest_str = ft_strjoin(rest_str, buf);
		if (!rest_str)
			return (NULL);
	}
	
	free(buf);
	return (rest_str);
}

char	*get_next_line(int fd)
{
	static char	*rest_str;
	char		*line;

	if (!rest_str)
		rest_str = ft_strdup("");
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest_str = ft_buf_str(fd, rest_str);
	if (!rest_str)
		return (NULL);
	line = ft_get_line(rest_str);
	rest_str = ft_rest_str(rest_str);
	return (line);
}

int	main(void)
{
	int		fd;
	int		i;
	char	*line;
	
	i = 0;
	fd = open("testfile1.txt", O_RDONLY);
	//printf("FD: %d\n", fd);
	if (fd == -1)
		return (1);
	while (i < 10)
	{
		line = get_next_line(fd);
		if (line)
		{
			printf("%s", line);
			free(line);
		}
		else
		{
			break ;
		}
		i++;
	}
	close(fd);
	return (0);
}
