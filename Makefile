# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pharatyk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 16:34:32 by pharatyk          #+#    #+#              #
#    Updated: 2018/11/06 16:34:34 by pharatyk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select
SRCS = $(shell find ./seleksrc/ -maxdepth 1 -type f -name '*.c')
CC = gcc #-g3 -fsanitize=address #-ltermcap #-Wall -Wextra -Werror -fsanitize=address
BOOST = -lncurses
CFLAGS = -I ./libft/includes -I ./selekludes
OBJ = $(SRCS:.c=.o)
CURR_NBR = 0
NBR_SRCS = $(shell find ./seleksrc/ -maxdepth 1 -type f -name '*.c' | wc -l)
COLS=$(shell tput cols)

####################_OPTIONS_########################
DINO=0
STYLE=1
CLEANSONORE=1
#####################################################

all: lib $(NAME)

simple: $(NAME)

lib:
	@make -C ./libft/

$(NAME): $(OBJ)
	@number=1;
	@if [[ $(COLS) -gt 38 && $(DINO) -eq 1 ]] ; then \
		printf "\033[2J\e[90m                                       \n                                       \n                                       \n                    ##*########        \n                    ###########        \n                    ###########        \n                    #########          \n         ##       #######              \n         ####  ########## #            \n         ################              \n          ##############               \n             ##########                \n               ### ###                 \n               #    ##                 \e[0m\n" ; \
	fi ;

	@if [[ $(COLS) -gt 48 && $(STYLE) -eq 1 ]] ; then \
		printf "  \e[90mOOOOOO  \e[92m100%% \e[91m|\e[0m" ; \
		while [[ $$number -le $(REAL_PRCT) ]] ; do \
			printf "\e[102m \e[0m" ; \
			((number = number + 1)) ; \
		done ; \
		printf "\e[91m|\e[0m\n" ; \
		printf "  \e[92mSELECT         \e[91m[\e[92mDONE\e[91m]\e[0m\n" ; \
	elif [[ ($(COLS) -gt 25) && $(COLS) -lt 48 && $(STYLE) -eq 1 ]] ; then \
		printf "  \e[92m100%% \e[91m|\e[0m" ; \
		while [[ $$number -le $(REAL_PRCT) ]] ; do \
			printf "\e[102m \e[0m" ; \
			((number = number + 1)) ; \
		done ; \
		printf "\e[91m|\e[0m\n" ; \
		printf "  \e[92mSELECT         \e[91m[\e[92mDONE\e[91m]\e[0m\n" ;\
	elif [ $(STYLE) -eq 1 ] ; then \
		printf "  \e[91m|\e[0m" ; \
		while [[ $$number -le $(REAL_PRCT) ]] ; do \
			printf "\e[102m \e[0m" ; \
			((number = number + 1)) ; \
		done ; \
		printf "\e[91m|\e[0m\n" ; \
		printf "  \e[92mSELECT         \e[91m[\e[92mDONE\e[91m]\e[0m\n" ;\
	else \
		echo "Compilation OK" ; \
		echo "SELECT  COMPILED" ; \
	fi ;

	@$(CC) $(BOOST) -o $(NAME) $(OBJ) libft/libft.a

clean:
	@make clean -C ./libft/
	@rm -f $(OBJ)
	@if [[ $(STYLE) -eq 1 && $(CLEANSONORE) -eq 1 ]] ; then \
		printf "  \e[92mCLEAN           \e[91m[\e[92mDONE\e[91m]\e[0m\n" ; \
	elif [ $(CLEANSONORE) -eq 1 ] ; then \
		echo "CLEANED" ; \
	fi ;

fclean: clean
	@make fclean -C ./libft/
	@rm -f $(NAME)
	@if [[ $(STYLE) -eq 1 && $(CLEANSONORE) -eq 1 ]] ; then \
		printf "  \e[92mFCLEAN          \e[91m[\e[92mDONE\e[91m]\e[0m\n" ; \
	elif [ $(CLEANSONORE) -eq 1 ] ; then \
		echo "ALL CLEANED" ; \
	fi ;

re: fclean all

%.o: %.c
	@$(eval CURR_NBR=$(shell echo "$(CURR_NBR) + 1" | bc))
	@$(eval TRUNC_PERCENT=$(shell echo "($(COLS) * $(CURR_NBR)) / $(NBR_SRCS) / 1.5" | bc))
	@$(eval PERCENT=$(shell echo "(100 * $(CURR_NBR)) / $(NBR_SRCS)" | bc))
	@$(eval REAL_PRCT=$(shell echo "($(COLS) / 1.5)" | bc))

	@if [[ $(shell echo "$(CURR_NBR) % 2" | bc) -eq 0 && $(COLS) -gt 38 && $(DINO) -eq 1 ]] ; then \
		printf "\033[2J                                       \n\e[97m                                       \n\e[97m                                       \n\e[97m                                       \n\e[97m       -         -   \e[90m##*#######        \n\e[97m             -       \e[90m##########        \n\e[97m                 -   \e[90m#####.....        \n\e[97m       -   \e[90m#        #####              \n\e[97m           \e[90m##    ##########            \n\e[97m      -     \e[90m##############             \n\e[97m         -  \e[90m#############              \n\e[97m              \e[90m#########                \n\e[97m                \e[90m##  ##                 \n\e[97m                     \e[90m#                 \e[0m\n" ; \
	elif [[ $(shell echo "$(CURR_NBR) % 2" | bc) -eq 1 && $(COLS) -gt 38 && $(DINO) -eq 1 ]] ; then \
		printf "\033[2J                                       \n\e[97m                                       \n\e[97m                                       \n\e[97m                                       \n\e[97m         -          \e[90m##*#######         \n\e[97m               -    \e[90m##########         \n\e[97m       -   -        \e[90m#####.....         \n\e[97m          \e[90m#        #####               \n\e[97m       -  \e[90m##    ##########             \n\e[97m          \e[90m##############               \n\e[97m     -     \e[90m#############               \n\e[97m       -     \e[90m#########                 \n\e[97m               \e[90m###  ##                 \n\e[97m               \e[90m#                       \e[0m\n" ; \
	elif [ $(DINO) -eq 1 ] ; then \
		printf "\033[2J" ; \
	fi ;

	@if [[ $(shell echo "$(CURR_NBR) % 6" | bc) -eq 5 && $(COLS) -gt 48 && $(STYLE) -eq 1 ]] ; then \
		printf "  \e[90mOOOOO\e[96m0\e[0m" ; \
	elif [[ $(shell echo "$(CURR_NBR) % 6" | bc) -eq 0 && $(COLS) -gt 48 && $(STYLE) -eq 1 ]] ; then \
		printf "  \e[96m0\e[90mOOOOO\e[0m" ; \
	elif [[ $(shell echo "$(CURR_NBR) % 6" | bc) -eq 1 && $(COLS) -gt 48 && $(STYLE) -eq 1 ]] ; then \
		printf "  \e[90mO\e[96m0\e[90mOOOO\e[0m" ; \
	elif [[ $(shell echo "$(CURR_NBR) % 6" | bc) -eq 2 && $(COLS) -gt 48 && $(STYLE) -eq 1 ]] ; then \
		printf "  \e[90mOO\e[96m0\e[90mOOO\e[0m" ; \
	elif [[ $(shell echo "$(CURR_NBR) % 6" | bc) -eq 3 && $(COLS) -gt 48 && $(STYLE) -eq 1 ]] ; then \
		printf "  \e[90mOOO\e[96m0\e[90mOO\e[0m" ; \
	elif [[ $(shell echo "$(CURR_NBR) % 6" | bc) -eq 4 && $(COLS) -gt 48 && $(STYLE) -eq 1 ]] ; then \
		printf "  \e[90mOOOO\e[96m0\e[90mO\e[0m" ; \
	fi ;

	@if [[ $(COLS) -gt 25 && $(STYLE) -eq 1 ]] ; then \
		printf "  \e[92m%3d%% \e[91m|\e[0m" `echo "$(PERCENT)" | bc` ; \
	elif [ $(STYLE) -eq 1 ] ; then \
		printf "  \e[91m|\e[0m" ; \
	fi ;

	@number=1; \
	while [[ $$number -le $(REAL_PRCT) ]] ; do \
	if [[ $$number -le $(TRUNC_PERCENT) && $(STYLE) -eq 1 ]]; then \
		printf "\e[102m \e[0m" ; \
	elif [ $(STYLE) -eq 1 ] ; then\
		printf " " ; \
	fi ; \
	((number = number + 1)) ; \
	done ;

	@if [ $(STYLE) -eq 1 ] ; then \
		printf " \e[91m|\e[0m\r" ; \
	elif [[ $(STYLE) -eq 0 && $(shell echo "$(CURR_NBR) % 3" | bc) -eq 0 ]]; then \
		printf "Compiling .  \r" ; \
	elif [[ $(STYLE) -eq 0 && $(shell echo "$(CURR_NBR) % 3" | bc) -eq 1 ]]; then \
		printf "Compiling .. \r" ; \
	elif [[ $(STYLE) -eq 0 && $(shell echo "$(CURR_NBR) % 3" | bc) -eq 2 ]]; then \
		printf "Compiling ...\r" ; \
	fi ;

	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: all clean fclean re lib simple
