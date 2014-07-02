/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 17:55:31 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/20 18:07:25 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/resource.h>
#include "bircd.h"

void		init_env(t_env *e)
{
	int				i;
	struct rlimit	rlp;
	int				ret;

	if ((ret = getrlimit(RLIMIT_NOFILE, &rlp)) == -1)
		ft_ferror("getrlimit error");
	e->maxfd = rlp.rlim_cur;
	if (!((e->fds = (t_fd*)malloc(sizeof(*e->fds) * e->maxfd))))
		ft_ferror("malloc error");
	i = 0;
	while (i < e->maxfd)
	{
		clean_fd(&e->fds[i]);
		i++;
	}
}
