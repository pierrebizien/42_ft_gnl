/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 09:44:46 by pbizien           #+#    #+#             */
/*   Updated: 2022/11/09 14:05:22 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int ft_contain_nl(char *str)
{
    int i;

    i = 0;
    if(!str)
    {
        return (0);
    }
    while (str[i])
    {
        if (str[i] == '\n')
            return (1);
        i++;
    }
    return (0);   
}

char *ft_join_and_free(char *str, char *temp)
{
    char    *buff;
    int     i;
    int     j;

    buff = malloc((ft_strlen(str) + ft_strlen(temp) + 1) * sizeof(char));
    if (!buff)
        return (NULL);
    i = 0;
    j = 0;
    while (str && str[j])
    {
        buff[i] = str[j];
        i++;
        j++;
    }
    j = 0;
    // printf("\ntemp vaut %s\n", temp);
    while (temp[j])
    {
        buff[i] = temp[j];
        i++;
        j++;
    }
    buff[i] = '\0';
    free(str);
    // printf("\n BUFF vaut %s\n", buff);
    return (buff);
}

char *ft_output(char *str)
{
    int len;
    char *output;
    int i;
    
    len = 0;
    i = 0;
    if (!str || !(*str))
        return (NULL);
    while (str[len] && str[len] != '\n')
        len++;
	// printf("len vaut %d\n", len);
    output = malloc(len + 2 * sizeof(char));
    if (!output)
        return (NULL);
    while (i <= len)
    {
        output[i] = str[i];
        i++;
    }
	output[i] = 0;
	// printf("ICI %s", output);
    return (output);
}

char	*ft_clean(char *str)
{
	int 	len;
	char 	*new_str;
	int		i;

	len = 0;
    if (!str)
	{
    	return (NULL);
	}
	while (str[len] && str[len] != '\n')
        len++;
	
	if (!str[len])
		len--;
	new_str = malloc(ft_strlen(str) - len + 1 * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	// printf("\n\nLE CHAR A LEN VAUT %c hehe\n\n", str[len]);
	while (str[len + 1])
	{
		new_str[i] = str[len + 1];
		len++;
		i++;
	}
	new_str[i] = 0;
	free (str);
	return (new_str);
}

char	*get_next_line(int fd)
{
    static char     *str = NULL;
    char            *temp;
    char            *output;

    temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    if (!temp)
        return (NULL);
    // printf("\n1/ str vaut %s\n", str);
    while (!ft_contain_nl(str) && read(fd, temp, BUFFER_SIZE) > 0)
    {
        str = ft_join_and_free(str, temp);
        ft_bzero(temp, BUFFER_SIZE + 1);
    }
    // printf("\n2/ str vaut %s\n", str);
    free(temp);
    output = ft_output(str);
    str = ft_clean(str);
	if (output)
    	return (output);
	else
		return (NULL);
}

// int main()
// {
//     int fd;
//     char *temp;

//     fd = open("tbr", O_RDONLY);
//     temp = get_next_line(fd);
//     printf("Printf 1 %s", temp);
//     free(temp);
//     temp = get_next_line(fd);
//     printf("Printf 2 %s", temp);
//     free(temp);
//     temp = get_next_line(fd);
//     printf("Printf 3 %s", temp);
//     free(temp);
//     temp = get_next_line(fd);
//     printf("Printf 4 %s", temp);
//     free(temp);
//     temp = get_next_line(fd);
//     printf("Printf 5 %s", temp);
//     free(temp);
//     // temp = get_next_line(fd);
//     // printf("Printf 6 %s", temp);
//     // free(temp);
//     close(fd);
// }