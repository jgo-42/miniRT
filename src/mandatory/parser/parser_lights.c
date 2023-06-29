/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:33:33 by sanghwal          #+#    #+#             */
/*   Updated: 2023/06/29 15:34:26 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "design_patterns.h"
#include "utils.h"

static bool	_vaildation_light(t_spot_light *light)
{
	if (light->type != LIGHT)
		return (false);
	if (!check_0_to_1(light->ratio)
		|| !check_rgba(light->rgba))
		return (false);
	return (true);
}

void	parser_light(char **line)
{
	t_meta			*meta;
	t_spot_light	*light;

	if (ft_arrlen((void **)line) != 4)
		error_handler(LIGHT_ERR);
	light = ft_malloc(sizeof(t_spot_light));
	light->type = LIGHT;
	light->light_point = parser_point3(line[1]);
	light->ratio = check_to_double(line[2]);
	light->rgba = parser_rgba(line[3]);
	meta = singleton();
	if (!_vaildation_light(light) || meta->spot_lights != NULL)
	{
		free(light);
		ft_free_all_arr(line);
		error_handler(LIGHT_ERR);
	}
	ft_lstadd_back(&(meta->spot_lights), ft_lstnew(light));
}
