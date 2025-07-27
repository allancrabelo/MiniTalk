/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusto <aaugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:19:14 by aaugusto          #+#    #+#             */
/*   Updated: 2025/07/27 07:22:22 by aaugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(void)
{
	ft_putstr_fd("Server Access Key (PID): ", 2);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	return (0);
}