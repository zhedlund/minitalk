/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:56:00 by zhedlund          #+#    #+#             */
/*   Updated: 2023/11/19 20:28:25 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void send_bit(pid_t pid, int bit)
{
    if (bit == 1)
        kill(pid, SIGUSR1);
    else
        kill(pid, SIGUSR2);
    usleep(42);
}

void send_message(pid_t pid, const char *msg)
{
    unsigned char	c;
	int				i;
	
	while (*msg != '\0')
	{		
		c = *msg;
        i = 7;
        while (i >= 0)
		{
            send_bit(pid, (c >> i) & 1);
            i--;
        }
        msg++;
    }
    i = 7;
    while (i >= 0)
	{
        send_bit(pid, 0);
        i--;
    }
}

int main(int argc, char **argv)
{
    if (argc != 3)
	{
        ft_putendl_fd("Usage: <server PID> <message>", 1);
        exit(1);
    }
    pid_t server_pid;
	const char *message;
	
	server_pid = atoi(argv[1]);
	message = argv[2];
    send_message(server_pid, message);
    return 0;
}