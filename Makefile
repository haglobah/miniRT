# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 12:24:11 by bhagenlo          #+#    #+#              #
#    Updated: 2023/02/01 14:17:29 by bhagenlo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

SRCS := hit.c minirt.c lexer.c parser.c ray.c color.c utils.c print.c \
		math.c memory.c utils_2.c\
		parser_utils.c parser_items_1.c parser_items_3.c parser_items_2.c \
		vector_math_1.c vector_math_2.c vector_math_3.c  parser_data_1.c \
		parser_data_2.c
MAIN = main.c
OBJS = $(SRCS:.c=.o)
MO = main.o
TESTS = test.c test_main.c
TOBJS = $(TESTS:.c=.o)
TEST = $(NAME)_test

CC := cc
CFLAGS := -Wall -Wextra # -Wno-gnu-include-next -ILeakSanitizer -LLeakSanitizer -llsan -lc++ #-Werror

LIBFT := libft
LFT := $(LIBFT)/libft.a

MLX42 := MLX42
LMLX := $(MLX42)/libmlx42.a
MLXFLAGS := -I include -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"

BREW := /Users/$(USER)/.brew

RM := rm -rf

all : $(NAME)

$(LIBFT) :
	git clone https://github.com/haglobah/libft.git

$(LFT) : $(LIBFT)
	$(MAKE) -C $(LIBFT)

$(LSAN) :
	if [ ! -d "LeakSanitizer"]; then git clone https://github.com/mhahnFr/LeakSanitizer.git; fi
	$(MAKE) -C LeakSanitizer

$(BREW) : 
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

$(MLX42) : 
	git clone https://github.com/codam-coding-college/MLX42.git

$(LMLX) : $(MLX42) $(BREW)
	$(MAKE) -C $(MLX42)

$(NAME) : $(MAIN) $(SRCS) Makefile minirt.h $(LFT) $(LMLX)
	$(CC) $(CFLAGS) $(MAIN) $(SRCS) $(LFT) $(LMLX) $(MLXFLAGS) -o $(NAME)

clean :
	@$(RM) $(OBJS) $(MO) $(TOBJS)

fclean : clean
	@$(RM) $(NAME) $(TEST)

re : fclean
	@$(MAKE) all

run : all
	./$(NAME) test.rt

ex : all
	./$(NAME) ex1.rt

c : all
	./$(NAME) cyl.rt

lsan : $(LSAN)
lsan :
	$(MAKE) all
#	./$(NAME) test.rt

test : 
	$(MAKE) run &
	sleep 0.1
	$(MAKE) ex &
	sleep 0.1
	$(MAKE) c

checkup :
	echo "Testing..."
	$(MAKE) test
	echo "Checking for memory leaks..."
	$(MAKE) lsan
	echo "Did you read the subject again, and have checked/asked for common mistakes?"
	norminette *.c $(NAME).h

submit :
ifdef REPO
	git remote add submit $(REPO)
	git remote -v
else
	@echo -e "You have to provide a repo:\n\n     make REPO=<the vogsphere repo> submit\n"
endif

.PHONY: all clean fclean re run test checkup submit