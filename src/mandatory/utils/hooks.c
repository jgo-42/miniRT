/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:08:41 by jgo               #+#    #+#             */
/*   Updated: 2023/06/12 19:28:22 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"
#include "minirt.h"
#include "utils.h"

void	hooks(void *param)
{
	t_meta	*meta;

	meta = param;
	if (mlx_is_key_down(meta->mlx_assets.mlx, MLX_KEY_ESCAPE))
		destroy(meta);
}