/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/22 17:11:27 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/22 22:35:03 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "bircd.h"

int		get_fd_by_nickname(t_env *e, char *nickname)
{
	int	i;

	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT
				&& ft_strequ(nickname, e->fds[i].nickname))
			return (i);
		i++;
	}
	return (-1);
}

int		cmd_msg_error(t_env *e, int cs, char *error)
{
	ft_listpushback(&e->fds[cs].to_send, ft_strdup(error));
	return (-1);
}

int		get_msg_data(char *cmd, char **nickname, char **msg)
{
	int		i;
	int		l;

	i = 3;
	l = 0;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		++i;
	while (cmd[i + l] && cmd[i + l] != ' ' && cmd[i + l] != '\t')
		++l;
	if (!l)
		return (-1);
	*nickname = ft_strsub(cmd, i, l);
	i += l;
	l = 0;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		++i;
	while (cmd[i + l])
		++l;
	if (!l)
	{
		free(*nickname);
		return (-1);
	}
	*msg = ft_strsub(cmd, i, l);
	return (0);
}

char	*get_full_msg(t_env *e, char *msg, int cs)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(e->fds[cs].nickname, " whisper to you : ");
	tmp2 = ft_strjoin(tmp, msg);
	free(tmp);
	free(msg);
	return (tmp2);
}

int		send_private_msg(t_env *e, int cs, char *cmd)
{
	char	*nickname;
	char	*msg;
	char	*tmp2;
	int		fd;

	nickname = NULL;
	msg = NULL;
	if (get_msg_data(cmd, &nickname, &msg))
		return (cmd_msg_error(e, cs, "ERROR : msg <nickname> <message>"));
	tmp2 = get_full_msg(e, msg, cs);
	if ((fd = get_fd_by_nickname(e, nickname)) == -1)
	{
		free(tmp2);
		free(nickname);
		return (cmd_msg_error(e, cs, "ERROR : nickname not found"));
	}
	free(nickname);
	if (e->fds[fd].type == FD_CLIENT)
		ft_listpushback(&e->fds[fd].to_send, ft_strdup(tmp2));
	else
		return (cmd_msg_error(e, cs, "ERROR : not a user"));
	free(tmp2);
	return (0);
}
