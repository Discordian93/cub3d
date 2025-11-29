/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:32:22 by ypacileo          #+#    #+#             */
/*   Updated: 2025/03/11 21:06:22 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>*/

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char		ch;
	char		*ptr;

	if (!s)
		return (NULL);
	ch = (char)c;
	ptr = (char *)s;
	while (*ptr != ch && *ptr != '\0')
		ptr++;
	if (*ptr == ch)
		return (ptr);
	else
		return (NULL);
}

/*int main() {
    const char *str = "la casa";
    char *p1 = ft_strchr(str, 'a');
	char *p2 = strchr(str,'a');

    printf("%s\n",p1);
	printf("%s\n",p2);
}*/
