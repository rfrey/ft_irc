/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 22:36:03 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/22 22:43:59 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "bircd.h"

int		chg_nickname(t_env *e, int cs, char *cmd)
{
	int		i;
	char	*new;
	char	*old;
	int		len;

	old = e->fds[cs].nickname;
	new = ft_strdup(&cmd[9]);
	len = ft_strlen(new);
	if (len > 9 || len < 1)
		return (cmd_msg_error(e, cs, "ERROR nickname must have 1 to 9 char"));
	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT && i != cs)
		{
			if (ft_strequ(new, e->fds[i].nickname))
				return (cmd_msg_error(e, cs, "ERROR nickname is already use"));
		}
		++i;
	}
	e->fds[cs].nickname = new;
	free(old);
	return (0);
}

int		who(t_env *e, int cs)
{
	int		i;

	ft_listpushback(&e->fds[cs].to_send, ft_strdup("\nWHO LIST :"));
	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT)
			ft_listpushback(&e->fds[cs].to_send, ft_strdup(e->fds[i].nickname));
		++i;
	}
	return (0);
}

int		interpret_cmd(t_env *e, int cs, char *cmd)
{
	if (ft_strequ(cmd, "quit"))
		return (1);
	else if (ft_strnequ(cmd, "nickname", 8))
		return (chg_nickname(e, cs, cmd));
	else if (ft_strequ(cmd, "who"))
		return (who(e, cs));
	else if (ft_strnequ(cmd, "msg", 3))
		return (send_private_msg(e, cs, cmd));
	return (0);
}
