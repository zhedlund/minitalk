/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:56:00 by zhedlund          #+#    #+#             */
/*   Updated: 2023/11/18 18:50:13 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*int kill(pid_t pid, int sig);

    kill(): used to send any signal to any process group or process.

        If pid is positive, then signal sig is sent to pid.

        If pid equals 0, then sig is sent to every process in the process group of the current process.

        If pid equals -1, then sig is sent to every process for which the calling process has permission to send signals, except for process 1 (init), but see below.

        f pid is less than -1, then sig is sent to every process in the process group -pid.

        If sig is 0, then no signal is sent, but error checking is still performed.
*/

#include "minitalk.h"

/*void	send_msg(pid_t pid, unsigned char c)
{
	int				i;
	
	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				perror("kill SIGUSR2");
                exit(EXIT_FAILURE);
			}
			else
			{
				if (kill(pid, SIGUSR1) == -1)
				{
					perror("kill SIGUSR1");
                	exit(EXIT_FAILURE);
				}
			}
		}
		usleep(100);
		i--;
	}
}

int	main(int argc, char **argv)
{
	pid_t		pid;
	const char	*msg;
	int			i;
	
	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client <pid> <message>\n", 1);
		exit(0);
	}
	pid = ft_atoi(argv[1]);
	msg = argv[2];
	i = 0;
	while (msg[i])
		send_msg(pid, msg[i++]);
	send_msg(pid, '\0');
	return (0);
}*/

void send_character(pid_t pid, unsigned char c) {
    int i;
    for (i = 7; i >= 0; i--) {
        if ((c >> i) & 1) {
            if (kill(pid, SIGUSR2) == -1) {
                perror("kill SIGUSR2");
                exit(EXIT_FAILURE);
            }
        } else {
            if (kill(pid, SIGUSR1) == -1) {
                perror("kill SIGUSR1");
                exit(EXIT_FAILURE);
            }
        }
        usleep(100); // Adjust this delay as needed
    }
}

void send_msg(pid_t pid, const char *msg) {
    while (*msg != '\0') {
        send_character(pid, *msg);
        msg++;
    }
    // Send null character to signal end of message
    send_character(pid, '\0');
}

int main(int argc, char **argv) {
    pid_t pid;
    const char *msg;
    
    if (argc != 3) {
        ft_putstr_fd("Usage: ./client <pid> <message>\n", 1);
        exit(EXIT_FAILURE);
    }
    
    pid = ft_atoi(argv[1]);
    msg = argv[2];

    send_msg(pid, msg);

    return 0;
}