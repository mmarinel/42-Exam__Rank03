# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: earendil <earendil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/26 11:02:25 by earendil          #+#    #+#              #
#    Updated: 2022/08/26 14:02:07 by earendil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET		:= "\033[0m"
BLACK		:= "\033[30m"
RED			:= "\033[31m"
GREEN		:= "\033[32m"
YELLOW		:= "\033[33m"
BLUE		:= "\033[34m"
MAGENTA		:= "\033[35m"
CYAN		:= "\033[36m"
WHITE		:= "\033[37m"
BOLDBLACK	:= "\033[1m\033[30m"
BOLDRED		:= "\033[1m\033[31m"
BOLDGREEN	:= "\033[1m\033[32m"
BOLDYELLOW	:= "\033[1m\033[33m"
BOLDBLUE	:= "\033[1m\033[34m"
BOLDMAGENTA	:= "\033[1m\033[35m"
BOLDCYAN	:= "\033[1m\033[36m"
BOLDWHITE	:= "\033[1m\033[37m"

CC:= @gcc
CFLAGS:= -Wall -Werror -Wextra
LIBS := -lm
PROJ_DIR := $(PWD)

NAME := micropaint
OBJS_DIR:= bin
OBJS:= $(addprefix $(OBJS_DIR)/, $(shell find . -name "*.c" -print | sed 's/\.c/\.o/g' | sed 's/\.\///'))
INCLUDES:= $(shell find . -name "*.h" -print)
TESTER_DIR := ../../examRank-03_Tester/micro_paint/
TESTING_TIME = 60

RMF:= @/bin/rm -rf
MKD:= @mkdir -p
MAKE_REC:= @make --no-print-directory --silent --ignore-errors

exam: .BUILD

test:
	@$(MAKE_REC) .TEST 2>/dev/null

testall:
	@$(MAKE_REC) .TESTALL 2>/dev/null

all:
	@$(MAKE_REC) -C ..

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@printf "Moving compressed source code to Tester directory\n\033[0;37m"
	@cat micropaint.h > micro_paint.c && cat micropaint.c >> micro_paint.c && cat utils.c >> micro_paint.c
	@mv micro_paint.c $(TESTER_DIR)
	@cd $(TESTER_DIR) && touch micropaint.h && cd $(PROJ_DIR)
	@printf "file moved!\n\033[0;37m"
	@echo "\033[0;35mProject done!\n\n\033[0;37m"

$(shell echo $(OBJS_DIR))/%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< $(LIBS) -o $@

fclean: clean
	@printf "removing program executable $(NAME)\n\033[0;37m"
	$(RMF) -f $(NAME)
	$(RMF) -f coutput
	$(RMF) -f output
	@printf "\033[0;35mExecutable removed!\n\n\033[0;37m"

clean:
	@printf "removing Object files $(OBJS)\n\033[0;37m"
	$(RMF) $(OBJS_DIR)
	@printf "\033[0;35mObject files removed!\n\n\033[0;37m"

re: fclean all

.BUILD:
	$(MKD) $(OBJS_DIR)
	@printf "\e[1;33mMaking project $(NAME) \n\033[0;37m"
	@$(MAKE_REC) $(NAME)

.TEST: fclean exam
	@$(RMF) filetto
	@echo ": + q to exit\nremove this lines now" >> filetto
	@vim filetto
	@./$(NAME) filetto;
	@$(RMF) filetto
	@echo $(CYAN) "\nTests done!\n" $(RESET)

.TESTALL: fclean exam
	@$(RMF) filetto
	@echo $(CYAN)"Running tester for $(TESTING_TIME) secs\n"$(RESET)\
	"You can set your desired testing time in the TESTING_TIME makefile variable (default is 60 secs)\
	\n(original tester doesn't stop until it finds an error)\n"
	@cd $(TESTER_DIR) && timeout $(TESTING_TIME)s ./test.sh && cd $(PROJ_DIR)
	@echo $(CYAN) "\nTests done!\n" $(RESET)