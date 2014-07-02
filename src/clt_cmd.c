/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clt_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 20:28:16 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/22 17:36:43 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "client.h"

void	cmd_unknow(char *cmd)
{
	ft_printf("ERROR : unknow command : '%s'.\n", cmd);
}

int		interpret_cmd(char *cmd)
{
	if (ft_strequ(cmd, "quit"))
		return (1);
	if (ft_strnequ(cmd, "nickname", 8))
		return (0);
	if (ft_strequ(cmd, "who"))
		return (0);
	if (ft_strnequ(cmd, "msg", 3))
		return (0);
	else
		cmd_unknow(cmd);
	return (0);
}
