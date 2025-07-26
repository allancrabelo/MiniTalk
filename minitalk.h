#ifndef MINITALK_H
# define MINITALK_H

// Includes 
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>

//Macros
# define _POSIX_C_SOURCE 200809L

// Functions
int		ft_atoi(char *str);
int		ft_strlen(char *str);
void	ft_putstr_fd(char *str, int fd);

# endif