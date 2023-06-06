# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/02 20:10:46 by jgo               #+#    #+#              #
#    Updated: 2023/06/06 18:04:10 by jgo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include ./make_config/com/ColorRules.mk
include ./make_config/src/Rules.mk

all bonus clean fclean re:
	$(MAKE) TOPDIR=`pwd` -C ext $@
	$(MAKE) TOPDIR=`pwd` -C lib $@
	$(MAKE) TOPDIR=`pwd` -C src $@

norm:
	norminette src/

.PHONY: all clean fclean re bonus norm
