/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:26:04 by evella            #+#    #+#             */
/*   Updated: 2024/02/22 17:07:48 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_state;

void	ft_error(void)
{
	printf("WRONG PID\n");
	exit(0);
}

void	ft_putbit(unsigned char c, int pid)
{
	int	i;

	i = 128;
	while (i > 0)
	{
		while (!g_state)
		{
		}
		usleep(50);
		if (c / i >= 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_error();
			c = c % i;
		}
		else
			if (kill(pid, SIGUSR2) == -1)
				ft_error();
		i /= 2;
		g_state = 0;
	}
}

void	ft_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		printf("Acknowledgement received\n");
		g_state = 1;
	}
}

int	main(int argc, char **argv)
{
	int				server_pid;
	int				i;
	unsigned char	*str;

	if (argc != 3)
	{
		ft_printf("USAGE : ./client [SERVER PID] [STRING TO PASS]");
		return (1);
	}
	g_state = 1;
	i = 0;
	server_pid = ft_atoi(argv[1]);
	str = (unsigned char *)argv[2];
	signal(SIGUSR1, ft_handler);
	while (str[i])
	{
		ft_putbit(str[i], server_pid);
		i++;
	}
	if (!str[i])
	{
		ft_putbit(str[i], server_pid);
		exit(0);
	}
}
