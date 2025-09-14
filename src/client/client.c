/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusto <<aaugusto@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:27:42 by aaugusto          #+#    #+#             */
/*   Updated: 2025/08/09 10:47:58 by aaugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minitalk.h"

/**
 * @brief Prints an error message to the standard error output with colors.
 * 
 * @details Prints a colored "[ERROR]" tag followed by the given error message
 * to the error file descriptor (stderr). Color codes are handled via macros.
 * @param str The error message string to print.
 * @return * int Returns 1 on completion.
 */
static int	ft_print_error(char *str)
{
	ft_putstr_fd(RED "[ERROR]" RESET, 2);
	ft_putstr_fd(YELLOW, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(RESET, 2);
	return (1);
}

/**
  * @brief Sends a specific bit of a character to a process via signals.
  * 
  * @details Extracts the bit at the given position from the character and sends
  * SIGUSR1 if the bit is 1, or SIGUSR2 if the bit is 0, to the target process.
  * @param c The character to send.
  * @param bit The bit position to send (0-7).
  * @param pid The process ID of the recipient.
  * @return * void 
  */
void	ft_sendchar(char c, int bit, int pid)
{
	if ((((c >> bit) & 1) && 1) == 1)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
}

/**
 * @brief Sends a message to another process bit by bit using signals.
 * 
 * @details Sends each character bitwise, keeps state internally, 
 * and signals completion with SIGUSR2.
 * @param pid The process ID of the recipient.
 * @param str The message string to send. Pass NULL to continue sending message.
 * @return * void 
 */

void	ft_send_message(int pid, char *msg)
{
	static int				i = 0;
	static char				*tmp_msg;
	static int				bit = 0;

	if (msg != NULL)
		tmp_msg = msg;
	if (tmp_msg[i] != 0)
	{
		ft_sendchar(tmp_msg[i], bit, pid);
		if (++bit == 8)
		{
			bit = 0;
			i++;
		}
	}
	else
	{
		if (bit < 8)
		{
			kill(pid, SIGUSR2);
			bit++;
		}
	}
}

/**
 * @brief Signal handler core for sending messages.
 * 
 * @details On receiving SIGUSR2, the program exits successfully.
 * On receiving SIGUSR1, continues sending the message.
 * 
 * @param sig The signal number received.
 * @param info Pointer to siginfo_t containing signal sender info.
 * @param context Pointer to ucontext_t (unused).
 * @return * void 
 */
void	ft_handle_sig(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (sig == SIGUSR2)
		exit (EXIT_SUCCESS);
	if (sig == SIGUSR1)
		ft_send_message(info->si_pid, NULL);
}

/**
 * @brief Main function for the client program.
 * 
 * @details Sets up signal handlers for SIGUSR1 and SIGUSR2 to handle.
 * Validates command-line arguments: expects the server PID and a message.
 * Ensures the PID argument is numeric before starting the message sending.
 * Enters an infinite pause loop, waiting for signals.
 * 
 * @param argc Argument count.
 * @param argv Argument vector: argv[1] = server PID, argv[2] = message string.
 * @return * int 
 */
int	main(int argc, char **argv)
{
	struct sigaction	action;
	size_t				i;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = ft_handle_sig;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	if (argc != 3)
		return (ft_print_error("Usage: ./client <Pid_server> <Message>"));
	else
	{
		i = 0;
		if (strempty(argv[2]))
			return (1);
		while (argv[1][i])
		{
			if (!ft_isdigit(argv[1][i]))
				return (ft_print_error("[pid_server] Must be numeric."));
			i++;
		}
		ft_send_message(ft_atoi(argv[1]), argv[2]);
	}
	while (1)
		pause();
}
