/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:30:17 by aespinos          #+#    #+#             */
/*   Updated: 2022/04/12 20:22:52 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

t_node	*g_list;

int	write_data(char data, int n)
{
	if (n == 8)
	{	
		if (data)
			ft_lstadd_back_n(&g_list, ft_lstnew_n(data));
		else if (!data)
		{
			print_node(&g_list);
			g_list = 0;
			printf("\n");
		}
		return (1);
	}
	return (0);
}

static void	ft_signal(int sig, siginfo_t *info, void *context)
{
	static char	data;
	static int	n;
	int			pid;
	
	pid = info->si_pid;
	
	if (sig == SIGUSR1)
	{
		kill(pid, SIGUSR1);
		data = data | 1;
	}
	else
		kill(pid, SIGUSR2);
	n++;
	if (write_data(data, n) == 1)
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
	t_node				*linea;

	s.sa_sigaction = ft_signal;
	s.sa_flags = SA_SIGINFO;
	printf("%d\n", getpid());
	sigaction(SIGUSR1, &s, 0);
	sigaction(SIGUSR2, &s, 0);
	while (1)
		pause();
	return (0);
}
