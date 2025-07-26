/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusto <<aaugusto@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:17:16 by aaugusto          #+#    #+#             */
/*   Updated: 2025/07/26 15:56:19 by aaugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_size(int pid, int size)
{
	int	i;

	i = 31;
	while (i >= 0)
	{
		if (size & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		usleep(100);
	}
}

void	send_message(int pid, char *str, int size)
{
	int	i;
	int	x;

	i = 0;
	while(i < size)
	{
		x = 8;
		while (x > 0)
		{
			if (str[i] & 0b10000000)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			x--;
			usleep(100);
		}
		i++;	
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;
	int		len;

	if (argc != 3)
		return (write(2,"Error! Usage: ./client <PID> <Message\n>", 39));
	pid = ft_atoi(argv[1]);
	str = argv[2];
	len = ft_strlen(str);
	send_size(pid, len);
	send_message(pid, str, len);
	return (0);
}