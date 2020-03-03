/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 09:49:38 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/07 10:58:27 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <unistd.h>

void	ft_putstr_fd(char *str, int fd)
{
	int		len;

	if (str == NULL)
		return ;
	len = ft_strlen(str);
	write(fd, str, len);
}
