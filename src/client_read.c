/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 17:53:59 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/22 18:21:28 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include "bircd.h"
#include "libft.h"

void	add_to_send(t_env *e, int cs)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(e->fds[cs].nickname, " says : ");
	tmp2 = ft_strjoin(tmp, e->fds[cs].buf_read);
	i = 0;
	while (i < e->maxfd)
	{
		if ((e->fds[i].type == FD_CLIENT)
			&& (i != cs))
		{
			ft_listpushback(&e->fds[i].to_send, ft_strdup(tmp2));
		}
		i++;
	}
	free(tmp);
	free(tmp2);
}

void	close_connection(t_env *e, int cs)
{
	close(cs);
	clean_fd(&e->fds[cs]);
	printf("client #%d gone away\n", cs);
}

void	client_read(t_env *e, int cs)
{
	int		r;
	char	buf[BUF_SIZE + 1];

	r = recv(cs, buf, BUF_SIZE, 0);
	if (r <= 0)
		close_connection(e, cs);
	else
	{
		ft_memcpy(&(e->fds[cs].buf_read[e->fds[cs].buf_read_len]), buf, r);
		e->fds[cs].buf_read_len += r;
		if (e->fds[cs].buf_read[e->fds[cs].buf_read_len - 1] == '\0')
		{
			if (e->fds[cs].buf_read[0] == '/')
			{
				if (interpret_cmd(e, cs, &e->fds[cs].buf_read[1]) == 1)
					close_connection(e, cs);
			}
			else
				add_to_send(e, cs);
			e->fds[cs].buf_read_len = 0;
		}
	}
}
