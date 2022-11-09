#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 14

# endif

//includes

# include <unistd.h>
# include <stdlib.h>

// fonction principale

char *get_next_line(int fd);

// fonctions utils

int     ft_strlen(char *str);
void    *ft_calloc(size_t nmemb, size_t size);
void    ft_bzero(void *s, size_t n);

#endif