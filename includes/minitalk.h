/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusto <<aaugusto@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 06:58:22 by aaugusto          #+#    #+#             */
/*   Updated: 2025/07/30 06:58:46 by aaugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int i, int fd);
void	*ft_calloc(size_t nmemb, size_t size);
#endif