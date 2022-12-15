# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 12:24:11 by bhagenlo          #+#    #+#              #
#    Updated: 2022/12/14 16:19:18 by bhagenlo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

SRCS := minirt.c parse.c 3d.c ray.c color.c utils.c
MAIN = main.c
OBJS = $(SRCS:.c=.o)
MO = main.o
TESTS = test.c test_main.c
TOBJS = $(TESTS:.c=.o)
TEST = $(NAME)_test

CC := cc
CFLAGS := -Wall -Wextra  #-Werror # -I../LeakSanitizer/include -L../LeakSanitizer -llsan -lc++

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

$(BREW) : 
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

$(MLX42) : 
	git clone https://github.com/codam-coding-college/MLX42.git

$(LMLX) : $(MLX42) $(BREW)
	brew update
	brew install glfw
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

lsan : CFLAGS += -I../LeakSanitizer/include -L../LeakSanitizer -llsan -lc++
lsan :
	$(MAKE) all
	./$(NAME)

test : $(TESTS) $(SRCS)
	$(CC) $(TESTS) $(SRCS) $(LINK_FLAGS) -o $(TEST)
	./$(TEST)

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