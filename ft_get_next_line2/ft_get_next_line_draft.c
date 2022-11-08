#include "ft_get_next_line.h"
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*output;

	output = malloc(nmemb * size);
	if (!output)
		return (NULL);
	ft_bzero(output, nmemb * size);
	return (output);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_and_free(char  *s1, char const *s2)
{
	int		len;
	char	*output;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	output = (char *)ft_calloc((len + 1), sizeof(char));
	if (output == NULL)
		return (NULL);
	while (s1 != NULL && s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	j = i;
	i = 0;
	free(s1);
	while (s2[i])
	{
		output[j] = s2[i];
		i++;
		j++;
	}
	output[j] = '\0';
	return (output);
}

int	ft_contain_nl(char *str)
{
	int	i;

	i = 0;
	if(str == NULL)
		return 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char *ft_strclean(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] && str[i]!='\n')
		i++;
	while (str[i])
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

char	*ft_strdup(const char *s)
{
	char	*str_dup;
	int		i;

	i = 0;
	if (!s)
	{
		return NULL;
	}
	
	str_dup = (char *)ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if(!str_dup)
		return NULL;
	while (s[i])
	{
		str_dup[i] = s[i];
		i++;
	}
	str_dup[i] = '\0';
	return (str_dup);
}

char *ft_str_residual(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (i == ft_strlen(str))
		return (NULL);
	return (ft_strdup(str + i + 1));
	}

char	*get_next_line(int fd)
{
	static char *residu = NULL;
	char *str;
	char *str_temp;
	static int read_test = BUFFER_SIZE;

	str_temp = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!str_temp)
		return (NULL);
	str = ft_strdup(residu);
	printf("\n residu vaut %s\n", residu);
	while (read_test == BUFFER_SIZE && !ft_contain_nl(residu) && !ft_contain_nl(str_temp))
	{
		printf("on rentre");
		read_test = read(fd, str_temp, BUFFER_SIZE);
		printf("\ntest vaut %d\n", read_test);
		if (read_test == -1)
			return (NULL);
		str = ft_strjoin_and_free(str, str_temp);		
	}
	free(str_temp);
	free(residu);
	residu = ft_str_residual(str);
	//printf("\n residu vaut %s \n", residu);
	ft_strclean(str);
	return (str);
}

int	main()
{
	int fd;
	char *str;

	fd = open("to_be_read.txt", O_RDONLY);
	if (fd == -1)
		printf("erreur d'ouverture");
	str = get_next_line(fd);
	printf("\n STR1 %s\n", str);
	printf("\n -------------------------- \n");
	free(str);
	str = get_next_line(fd);
	printf("\n STR2 %s\n", str);
	printf("\n -------------------------- \n");
	free(str);
	str = get_next_line(fd);
	printf("\n STR3 %s\n", str);
	printf("\n -------------------------- \n");
	free(str);
	str = get_next_line(fd);
	printf("\n STR4 %s\n", str);
	printf("\n -------------------------- \n");
	free(str);
	str = get_next_line(fd);
	printf("\n STR5 %s\n", str);
	printf("\n -------------------------- \n");
	free(str);
	str = get_next_line(fd);
	printf("\n STR6 %s\n", str);
	printf("\n -------------------------- \n");
	free(str);
	str = get_next_line(fd);
	printf("\n STR7 %s\n", str);
	printf("\n -------------------------- \n");
	free(str);
	str = get_next_line(fd);
	printf("\n STR8 %s\n", str);
	printf("\n -------------------------- \n");
	free(str);
	str = get_next_line(fd);
	printf("\n STR9 %s\n", str);
	printf("\n -------------------------- \n");
	free(str);
	str = get_next_line(fd);
	printf("\n STR10 %s\n", str);
	printf("\n -------------------------- \n");
	free(str);
	close(fd);
}
