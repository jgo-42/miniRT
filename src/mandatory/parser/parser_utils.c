/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:29:33 by sanghwal          #+#    #+#             */
/*   Updated: 2023/06/08 14:09:06 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"
#include "parser.h"

bool	check_0_to_1(double data)
{
	return (data >= 0.0 && data <= 1.0);
}

bool	check_rgb(t_rgb rgb)
{
	return ((rgb.r >= 0 && rgb.r <= 255) \
		&& (rgb.g >= 0 && rgb.g <= 255) \
		&& (rgb.b >= 0 && rgb.b <= 255));
}

bool	check_minus1_to_1(double data)
{
	return (data > -1.0 && data < 1.0);
}
