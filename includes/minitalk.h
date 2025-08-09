/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusto <<aaugusto@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:20:30 by aaugusto          #+#    #+#             */
/*   Updated: 2025/08/09 10:09:22 by aaugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

// Macros
# define _POSIX_C_SOURCE 200809L
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define BLUE		"\033[1;34m"
# define MAGENTA	"\033[1;35m"
# define CYAN		"\033[1;36m"
# define RESET		"\033[0m"

// Includes 
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <bits/types.h>
# include <stdbool.h>

// Functions
void	ft_putstr_fd(char *str, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(char *str);
int		ft_isdigit(int c);
size_t	ft_strlen(char *str);
bool	strempty(char *str);
#endif
