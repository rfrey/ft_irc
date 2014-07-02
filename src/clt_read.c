/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clt_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 21:56:17 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/22 22:42:08 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include "list.h"
#include "libft.h"
#include "client.h"

void	read_prompt(t_list **to_send)
{
	static char		buf[BUF_SIZE];
	static int		buf_len = 0;

	buf_len += read(STDIN_FILENO, &buf[buf_len], BUF_SIZE - buf_len);
	if (buf[buf_len - 1] == '\n')
	{
		buf[buf_len - 1] = '\0';
		if (ft_strlen(buf) > 0)
			ft_listpushback(to_send, ft_strdup(buf));
		buf_len = 0;
		ft_printf("irc > ");
	}
}

int		send_buffer(t_list **to_send, int sock)
{
	char	*tmp;

	while (*to_send)
	{
		tmp = (char *)ft_listpop(to_send);
		send(sock, tmp, ft_strlen(tmp) + 1, 0);
		if (tmp[0] == '/')
			return (interpret_cmd(&tmp[1]));
		free(tmp);
	}
	return (0);
}

void	read_incomming(int sock)
{
	static char	buf[BUF_SIZE];
	static int	buf_len = 0;
	int			r;
	int			i;

	r = recv(sock, &buf[buf_len], BUF_SIZE - buf_len, 0);
	if (r == 0)
	{
		ft_printf("Disconnect by the server.\n");
		exit(EXIT_FAILURE);
	}
	i = buf_len;
	buf_len += r;
	while (i < buf_len)
	{
		if (!buf[i])
		{
			if (ft_strlen(buf))
				ft_putendl(buf);
			ft_memcpy(buf, &buf[i + 1], buf_len - i - 1);
			buf_len = buf_len - i - 1;
		}
		++i;
	}
}

void	prompt(int sock)
{
	fd_set	fds_read;
	fd_set	fds_write;
	t_list	*to_send;

	to_send = NULL;
	FD_ZERO(&fds_read);
	FD_ZERO(&fds_write);
	ft_printf("irc > ");
	while (1)
	{
		FD_SET(0, &fds_read);
		FD_SET(sock, &fds_read);
		FD_SET(sock, &fds_write);
		select(sock + 1, &fds_read, &fds_write, NULL, NULL);
		if (FD_ISSET(0, &fds_read))
			read_prompt(&to_send);
		if (to_send && FD_ISSET(sock, &fds_write))
		{
			if (send_buffer(&to_send, sock))
				break ;
		}
		if (FD_ISSET(sock, &fds_read))
			read_incomming(sock);
	}
}
