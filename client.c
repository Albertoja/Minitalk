/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:30:28 by aespinos          #+#    #+#             */
/*   Updated: 2022/04/13 17:30:14 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static void	ending(int a)
{
	int	i;

	i = 0;
	while (i++ < 8)
	{
		kill(a, SIGUSR2);
		usleep(1000);
	}
}

static void	send_data(int a, char *str)
{
	char	c;
	int		i;
	int		cont;

	cont = 0;
	while (str[cont] != '\0')
	{
		i = 8;
		c = str[cont++];
		while (i--)
		{
			if ((c >> i) % 2 != 0)
				kill(a, SIGUSR1);
			else
				kill(a, SIGUSR2);
			usleep(10);
		}
	}
	ending(a);
}

void received_signal(int a)
{
	static int	cont;
	static int	intro;
	
	if (intro == 0)
	{
		printf("Señales recibidas:");
		intro = 1;
	}
	if(a == SIGUSR1)
	{
		printf("0");
		cont++;
	}
	
	if (cont == 7)
	{
		printf("\n");
		cont = 0;
	}
	if(a == SIGUSR2)
	{
		printf("1");
		cont++;
	}
}

// void	leaks(void)
// {
// 	system("leaks a.out");
// }

int	main(int argc, char **argv)
{
	//atexit(leaks);
	if (argc != 3 || !ft_atoi(argv[1]))
	{
		return (1);
	}
	signal(SIGUSR1, received_signal);
	signal(SIGUSR2, received_signal);
	send_data(ft_atoi(argv[1]), argv[2]);
	while(1)
		pause();
	return (0);
}
