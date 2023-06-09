/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:13:07 by sanghwal          #+#    #+#             */
/*   Updated: 2023/06/08 17:02:16 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

static double	integer_part(char *str, int len)
{
	double	temp_d;
	char	*temp_s;
	int		i;

	if (len == 0)
		return (0.0);
	i = 0;
	temp_s = ft_malloc(len + 1);
	temp_s[len] = '\0';
	while (i < len)
	{
		temp_s[i] = str[i];
		i++;
	}
	temp_d = (double)ft_atoi(temp_s);
	free(temp_s);
	return (temp_d);
}

static double	fractional_part(char *str)
{
	double	temp_d;
	int		i;

	temp_d = (double)ft_atoi(str);
	i = ft_strlen(str);
	while (i--)
		temp_d *= 0.1;
	return (temp_d);
}

double	atod(char *str)
{
	double	temp1;
	double	temp2;
	char	*dot;

	dot = ft_strchr(str, '.');
	if (dot == NULL || *(dot + 1) == '\0')
		return (integer_part(str, ft_strlen(str)));
	temp1 = integer_part(str, dot - str);
	temp2 = fractional_part(dot + 1);
	if (temp1 < 0)
		temp2 *= -1;
	return (temp1 + temp2);
}