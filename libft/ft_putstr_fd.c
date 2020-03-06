/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 09:49:38 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/05 17:11:19 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putstr_fd(char *str, int fd)
{
	int		len;

	if (str == NULL)
		return ;
	len = ft_strlen(str);
	write(fd, str, len);
}
