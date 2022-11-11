/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:39:00 by pbizien           #+#    #+#             */
/*   Updated: 2022/11/11 18:50:11 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_free_s1(char *s1, char *s2)
{
	int		len;
	char	*output;

	if (!s2)
		return (s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	output = (char *)malloc((len + 1) * sizeof(char));
	if (output == NULL)
		return (NULL);
	ft_strcpy(s1, s2, output);
	free(s1);
	ft_bzero(s2, BUFFER_SIZE);
	return (output);
}

int	ft_contain_nl(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_end(char *remain, char *buffer)
{
	int	i;	

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!remain[0])
		ft_bzero(remain, BUFFER_SIZE);
	if (buffer[i])
		ft_memcpy(remain, buffer + i + 1, ft_strlen(buffer) - i);
	else
		ft_bzero(remain, BUFFER_SIZE);
	if (ft_contain_nl(buffer))
		ft_bzero(buffer + i + 1, ft_strlen(buffer) - i);
	return (buffer);
}

char	*ft_buff_to_zero(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
	{
		i++;
	}
	if (ft_contain_nl(buffer))
		ft_bzero(buffer + i + 1, ft_strlen(buffer) - i);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	remain[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*buffer;
	char		temp[BUFFER_SIZE + 1];
	int			read_bytes;

	buffer = NULL;
	read_bytes = 1;
	ft_bzero(temp, BUFFER_SIZE + 1);
	if (fd < 0 || fd > FOPEN_MAX)
		return (NULL);
	if (!remain[fd][0])
	{
		read_bytes = read(fd, temp, BUFFER_SIZE);
		if (read_bytes <= 0)
			return (NULL);
		buffer = ft_strjoin_free_s1(buffer, temp);
	}
	else
		buffer = ft_strjoin_free_s1(buffer, remain[fd]);
	while (!ft_contain_nl(buffer) && read_bytes > 0)
	{
		read_bytes = read(fd, temp, BUFFER_SIZE);
		buffer = ft_strjoin_free_s1(buffer, temp);
	}
	return (ft_end(remain[fd], buffer));
}

// int main()
// {
//     int fd;
//     char *str;

// 	fd = open("multiple_line_with_nl", O_RDONLY);
// 	str = get_next_line(fd);
// 	// printf("%s", str);
// 	printf("\n-----------------\n");
// 	free (str);
// 	str = get_next_line(fd);
// 	// printf("%s", str);
// 	free (str);
// 	// str = get_next_line(fd);
// 	// printf("%s", str);
// 	// free (str);
// 	// str = get_next_line(fd);
// 	// printf("%s", str);
// 	// free (str);
// 	// str = get_next_line(fd);
// 	// printf("%s", str);
// 	// free (str);
// 	close(fd);
// }
