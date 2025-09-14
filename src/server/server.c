/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusto <<aaugusto@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:27:44 by aaugusto          #+#    #+#             */
/*   Updated: 2025/08/09 10:51:30 by aaugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minitalk.h"

/**
 * @brief Appends a character to a dynamically allocated string.
 * @details Allocates or reallocates memory to add character `c` at `str`.
 * Frees the old string and sends SIGUSR1 to the process with PID `pid` 
 * to acknowledge the update.
 * @param str The original string (can be NULL).
 * @param c The character to append.
 * @param pid PID of the process to send SIGUSR1 signal.
 * @return * char* A new string with the appended character.
 */
char	*add_char2str(char *str, char c, int pid)
{
	char	*new_str;
	size_t	str_len;
	size_t	i;

	i = 0;
	if (str == NULL)
	{
		new_str = (char *) malloc(sizeof(char));
		new_str[0] = '\0';
		str_len = 0;
	}
	else
		str_len = ft_strlen(str);
	new_str = (char *) malloc((str_len + 2) * sizeof(char));
	while (i < str_len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free (str);
	kill(pid, SIGUSR1);
	return (new_str);
}

/**
 * @brief Signal handler to receive messages bit-by-bit via SIGUSR1 and SIGUSR2.
 * 
 * @details Reconstructs characters from signals: SIGUSR1 | SIGUSR2 
 * Once a full character (8 bits) is received, it's appended to the message.
 * A null character ('\0') signals end of message, which is printed.
 * 
 * @param sig Signal received (SIGUSR1 or SIGUSR2).
 * @param info Signal info containing sender PID.
 * @param ctx Signal context (unused).
 * @return * void 
 */
void	ft_handle_sig(int sig, siginfo_t *info, void *ctx)
{
	static int		curr_bit;
	static char		curr_char;
	static char		*msg;

	(void) ctx;
	if (sig == SIGUSR1 || sig == SIGUSR2)
		if (sig == SIGUSR1)
			curr_char |= (1 << curr_bit);
	curr_bit++;
	if (curr_bit == 8)
	{
		if (curr_char == '\0')
		{
			ft_putstr_fd(msg, 2);
			free(msg);
			msg = NULL;
			kill(info->si_pid, SIGUSR2);
		}
		else
			msg = add_char2str(msg, curr_char, info->si_pid);
		curr_bit = 0;
		curr_char = 0;
	}
	else
		kill(info->si_pid, SIGUSR1);
}

/**
 * @brief Main function of the server program.
 * 
 * @details Sets up signal handlers for SIGUSR1 and SIGUSR2 using sigaction.
 * Retrieves and prints the server PID to standard output.
 * Enters an infinite pause loop waiting for signals indefinitely.
 * @return * int int Returns 0 on successful execution.
 */
int	main(void)
{
	struct sigaction	action;
	pid_t				srv_pid;

	srv_pid = getpid();
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = ft_handle_sig;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	ft_putstr_fd(GREEN "Server PID: " RESET, 1);
	ft_putnbr_fd (srv_pid, 1);
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
	return (0);
}
