/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bircd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 18:05:59 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/22 22:38:45 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIRCD_H
# define BIRCD_H

# include <sys/select.h>
# include "list.h"

# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2

# define BUF_SIZE	4096

# define MAX(a,b)	((a > b) ? a : b)

# define USAGE		"Usage: %s port\n"

typedef struct	s_fd
{
	int		type;
	void	(*fct_read)();
	void	(*fct_write)();
	char	buf_read[BUF_SIZE + 1];
	int		buf_read_len;
	t_list	*to_send;
	char	*nickname;
}				t_fd;

typedef struct	s_env
{
	t_fd	*fds;
	int		port;
	int		maxfd;
	int		max;
	int		r;
	fd_set	fd_read;
	fd_set	fd_write;
}				t_env;

void			ft_ferror(char *msg);
void			init_env(t_env *e);
void			get_opt(t_env *e, int ac, char **av);
void			main_loop(t_env *e);
void			srv_create(t_env *e, int port);
void			srv_accept(t_env *e, int s);
void			client_read(t_env *e, int cs);
void			client_write(t_env *e, int cs);
void			clean_fd(t_fd *fd);
void			init_fd(t_env *e);
void			do_select(t_env *e);
void			check_fd(t_env *e);
int				interpret_cmd(t_env *e, int cs, char *cmd);
int				send_private_msg(t_env *e, int cs, char *cmd);
int				cmd_msg_error(t_env *e, int cs, char *error);

#endif
