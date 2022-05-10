/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:35:59 by aespinos          #+#    #+#             */
/*   Updated: 2022/04/12 19:25:54 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

int		ft_atoi(const char *str);
typedef struct s_node
{
	char			val;
	struct s_node	*next;
}	t_node;
t_node	*ft_lstlast_n(t_node *lst);
t_node	*ft_lstnew_n(char c);
void	ft_lstadd_back_n(t_node **lst, t_node *new);
void	print_node(t_node **g_list);
#endif