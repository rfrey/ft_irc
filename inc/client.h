/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 16:55:21 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/20 22:56:37 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# define BUF_SIZE	4096

int		interpret_cmd(char *cmd);
int		create_client(char *ip, int port);
void	prompt(int sock);

int		wait_msg(char *msg, int fd);

void	send_text(char *txt, int sock);

#endif
