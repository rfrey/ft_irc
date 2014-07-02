/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 17:58:12 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/21 17:20:08 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include "bircd.h"

void			srv_create(t_env *e, int port)
{
	int					s;
	struct sockaddr_in	sin;
	struct protoent		*pe;

	if (!((pe = (struct protoent*)getprotobyname("tcp"))))
		ft_ferror("getprotobyname error");
	if ((s = socket(PF_INET, SOCK_STREAM, pe->p_proto)) == -1)
		ft_ferror("socket error");
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	if ((bind(s, (struct sockaddr*)&sin, sizeof(sin))) == -1)
		ft_ferror("bind error");
	if ((listen(s, 42)) == -1)
		ft_ferror("listen error");
	e->fds[s].type = FD_SERV;
	e->fds[s].fct_read = srv_accept;
	e->fds[s].to_send = NULL;
}
