/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 21:32:20 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/14 21:34:34 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getenv(char **envp, char *get)
{
	int		i;
	int		len;

	len = ft_strlen(get);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(get, envp[i], len) && envp[i][len] == '=')
			return (&(envp[i][len + 1]));
		i++;
	}
	return (NULL);
}
