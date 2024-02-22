/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:26:07 by evella            #+#    #+#             */
/*   Updated: 2024/02/22 16:29:13 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_handler(int sig, siginfo_t *siginfo, void *str);

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_sigaction = ft_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	pid = (int)getpid();
	ft_printf("PID = %d\n", pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
	}
	return (0);
}

void	ft_add_char(char c)
{
	static char	*str;
	static int	i;
	char		*newstr;
	char		*tmp;

	if (!str)
		str = ft_calloc(sizeof(char), 1);
	newstr = ft_calloc(sizeof(char), ft_strlen(str) + 2);
	ft_strcpy(newstr, str);
	tmp = str;
	str = newstr;
	free(tmp);
	str[i] = c;
	i++;
	if (c == 0)
	{
		ft_putstr(str);
		free(str);
		str = NULL;
		i = 0;
	}
}

void	ft_handler(int sig, siginfo_t *siginfo, void *str)
{
	static int	i;
	static int	bit;

	(void)str;
	if (sig == SIGUSR1)
	{
		bit = bit | 1 << (7 - i);
		i++;
	}
	else
		i++;
	if (i == 8)
	{
		ft_add_char(bit);
		i = 0;
		bit = 0;
	}
	usleep(100);
	kill(siginfo->si_pid, SIGUSR1);
}
