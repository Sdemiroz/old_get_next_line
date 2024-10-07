/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:27:11 by sdemiroz          #+#    #+#             */
/*   Updated: 2024/05/27 23:34:34 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*join_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

char	*sep_buf(char *in)
{
	char	*out;
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (in[x] && in[x] != '\n')
		x++;
	if (!in[x])
	{
		free (in);
		return (NULL);
	}
	out = ft_calloc((ft_strlen(in) - x + 1), sizeof(char));
	if (!out)
		return (NULL);
	while (in[x])
		out[y++] = in[++x];
	out[y] = '\0';
	free (in);
	return (out);
}

char	*get_out(char *buffer)
{
	int		x;
	char	*res;

	x = 0;
	if (!buffer[x])
		return (NULL);
	while (buffer[x] && buffer[x] != '\n')
		x++;
	if (ft_strchr(buffer, '\n'))
		res = ft_calloc(x + 2, sizeof(char));
	else
		res = ft_calloc(x + 1, sizeof(char));
	x = 0;
	while (buffer[x] && buffer[x] != '\n')
	{
		res[x] = buffer[x];
		x++;
	}
	if (buffer[x] && buffer[x] == '\n')
		res[x++] = '\n';
	return (res);
}

char	*get_text(int fd, char *res)
{
	char	*buffer;
	int		cc;

	cc = 1;
	if (!res)
		res = ft_calloc(1, sizeof(char));
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (cc > 0)
	{
		cc = read(fd, buffer, BUFFER_SIZE);
		if (cc == -1)
		{
			free (buffer);
			free (res);
			return (NULL);
		}
		buffer[cc] = '\0';
		res = join_free(res, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free (buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char		*buffer[OPEN_MAX];
	char			*out;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = get_text(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	out = get_out(buffer[fd]);
	buffer[fd] = sep_buf(buffer[fd]);
	return (out);
}