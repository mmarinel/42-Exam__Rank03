# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: earendil <earendil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/26 11:02:25 by earendil          #+#    #+#              #
#    Updated: 2022/08/26 12:06:14 by earendil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	gcc -Wall -Werror -Wextra minipaint.c utils.c -lm -o minipaint
	cat minipaint.h > mini_paint.c && cat minipaint.c >> mini_paint.c && cat utils.c >> mini_paint.c
	mv mini_paint.c ../../examRank-03_Tester/mini_paint/
	cd ../../examRank-03_Tester/mini_paint/ && touch minipaint.h

fclean:
	rm minipaint