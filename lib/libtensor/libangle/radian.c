/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:22:08 by jgo               #+#    #+#             */
/*   Updated: 2023/06/10 15:38:34 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "angle.h"

double	degree_to_radian(double degree)
{
	return (degree * (M_PI / 180.0));
}
