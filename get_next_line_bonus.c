/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenaoui <mbenaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 20:21:08 by mbenaoui          #+#    #+#             */
/*   Updated: 2021/12/11 14:46:29 by mbenaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*print_ligne(char *s)
{
	int		i;
	char	*b;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	b = malloc(sizeof(char) * (i + 2));
	if (!b)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		b[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		b[i++] = '\n';
	b[i] = '\0';
	return (b);
}

char	*read_s(int fd, char *ru)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	i = 1;
	while (i != 0)
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i == -1)
		{
			free (str);
			return (NULL);
		}
		str[i] = '\0';
		ru = ft_strjoin(ru, str);
		if (ft_strchr(str, '\n'))
			break ;
	}
	free (str);
	return (ru);
}

char	*next_ligne(char *s)
{
	char	*d;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\0')
	{
		free (s);
		return (NULL);
	}
	d = malloc(sizeof(char) * (ft_strlen(s) - i + 1));
	if (!d)
		return (NULL);
	i++;
	while (s[i])
		d[k++] = s[i++];
	d[k] = '\0';
	free (s);
	return (d);
}

char	*get_next_line(int fd)
{
	static char	*str[65536];
	char		*dest;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	str[fd] = read_s(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	dest = print_ligne(str[fd]);
	str[fd] = next_ligne(str[fd]);
	if (dest[0] == '\0')
	{
		free(str[fd]);
		free(dest);
		return (NULL);
	}
	return (dest);
}
