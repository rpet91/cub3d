/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 14:20:06 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/10 09:41:07 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../cub3d.h"

char	*ft_strdup(char *str)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (result == NULL)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[i] != '\0')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
