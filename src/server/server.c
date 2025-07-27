/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusto <<aaugusto@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:19:14 by aaugusto          #+#    #+#             */
/*   Updated: 2025/07/27 16:41:53 by aaugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_size = 0;

char	*ft_printfree(char *str)
{
	str[g_size] = '\0';
	ft_putstr_fd("Message: ", 1);
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
	free (str);
	g_size = 0;
	return (NULL);
}

char	*ft_create(int size)
{
	char	*str;

	str = NULL;
	str = ft_calloc((size + 1), sizeof(char));
	if (!str)
		return (NULL);
	return (str);
}

void	handler_size(int sig)
{
	static int	size = 0;
	static int	bitcount = 0;
	
	if (sig == SIGUSR2)
		size = size << 1;
	else
		size = (size << 1) | 1;
	bitcount++;
	if (bitcount == 32)
	{
		g_size = size;
		ft_putstr_fd("Received size: ", 1);
		ft_putnbr_fd(g_size, 1);
		ft_putchar_fd('\n', 1);
		bitcount = 0;
		size = 0;
	}
}

void	handler_message(int sig)
{
	static char	c = 0;
	static int	i = 0;
	static char	*str = NULL;
	static int	j = 0;
	
	if (sig == SIGUSR2)
		c = c << 1;
	else	
		c = (c << 1) | 1;
	i++;
	if (i == 8)
	{
		if (str == NULL)
			str = ft_create(g_size);
		str[j++] = c;
		i = 0;
		c = 0;
	}
	if (j == g_size)
	{
		j = 0;
		str = ft_printfree(str);
		ft_putchar_fd('\n', 1);
	}
}

int	main(void)
{
	ft_putstr_fd("Server Access Key (PID): ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	while (1)
	{
		if (g_size == 0)
		{
			signal(SIGUSR1, handler_size);
			signal(SIGUSR2, handler_size);
		}
		else
		{
			signal(SIGUSR1, handler_message);
			signal(SIGUSR2, handler_message);
		}
	}
	return (0);
}
