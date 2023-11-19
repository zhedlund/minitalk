/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:03:25 by zhedlund          #+#    #+#             */
/*   Updated: 2023/11/19 20:28:10 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk.h"

void signal_handler(int signal)
{
    static char received_chars[BUFFER];
    static int bit_count = 0;
    static int char_index = 0;

    if (signal == SIGUSR2)
        received_chars[char_index] <<= 1;
	else if (signal == SIGUSR1)
	{
        received_chars[char_index] <<= 1;
        received_chars[char_index] |= 1;
    }
	bit_count++;
    if (bit_count == 8)
	{
        if (received_chars[char_index] == '\0')
		{
            ft_putendl_fd("\n>>>>> Message received: \n", 1);
			ft_putendl_fd(received_chars, 1);
            ft_memset(received_chars, 0, sizeof(received_chars));
			char_index = 0;
        }
		else
			char_index++;
    	bit_count = 0;
	}
}

int main(void)
{
    struct sigaction act;
	
	act.sa_handler = signal_handler;
    sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
    if (sigaction(SIGUSR1, &act, NULL) < 0
		|| sigaction(SIGUSR2, &act, NULL) < 0)
	{
        ft_putstr_fd("An error occured", 1);
        exit(1);
    }
    ft_putstr_fd("\nServer running with PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
    while (1)
        sleep(1);
    return (0);
}