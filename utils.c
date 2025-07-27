#include "minitalk.h"

int	ft_atoi(char *str)
{
	int	sign;
	int	result;
	int	i;

	sign = 1;
	result = 0;
	i = 0;
	while(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int i, int fd)
{
	if (i < 0)
	{
		ft_putchar_fd('-', fd);
		i *= -1;
	}

	if (i > 9)
		ft_putnbr_fd(i / 10, fd);
	ft_putchar_fd(i % 10 + '0', fd);
}