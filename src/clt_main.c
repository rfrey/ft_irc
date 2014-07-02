/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clt_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 16:37:24 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/17 15:31:23 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "client.h"
#include "libft.h"

int		main(int argc, char **argv)
{
	int		sock;

	if (argc == 3)
		sock = create_client(argv[1], ft_atoi(argv[2]));
	else
	{
		ft_printf("usage : %s ip port\n", argv[0]);
		return (1);
	}
	if (sock == -1)
		return (1);
	prompt(sock);
	close(sock);
	ft_printf("SUCCESS : Disconnected from server.\n");
	return (0);
}
