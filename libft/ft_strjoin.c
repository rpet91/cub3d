/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 13:51:05 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/05 17:15:57 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (result == NULL)
	{
		free(s1);
		return (NULL);
	}
	ft_strcpy(result, s1);
	ft_strcpy(result + len1, s2);
	free(s1);
	return (result);
}
