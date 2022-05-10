/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:30:17 by aespinos          #+#    #+#             */
/*   Updated: 2022/05/09 17:00:31 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

t_node	*g_list;

int	write_data(char data, int n, int pid)
{
	if (n == 8)
	{
		if (data)
			ft_lstadd_back_n(&g_list, ft_lstnew_n(data));
		else if (!data)
		{
			print_node(&g_list);
			g_list = 0;
			write(1, "\n", 1);
			kill(pid, SIGUSR2);
		}
		return (1);
	}
	kill(pid, SIGUSR1);
	return (0);
}

static void	ft_signal(int sig, siginfo_t *info, void *context)
{
	static char	data;
	static int	n;
	int			pid;

	context = 0;
	pid = info->si_pid;
	if (sig == SIGUSR1)
		data = data | 1;
	n++;
	if (write_data(data, n, pid) == 1)
	{
		n = 0;
		data = 0;
		return ;
	}
	else
		data = data << 1;
}

int	main(void)
{
	struct sigaction	s;

	s.sa_sigaction = ft_signal;
	s.sa_flags = SA_SIGINFO;
	printf("%d\n", getpid());
	sigaction(SIGUSR1, &s, 0);
	sigaction(SIGUSR2, &s, 0);
	while (1)
		pause();
	return (0);
}
