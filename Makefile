# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mekundur <mekundur@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 19:34:04 by mekundur          #+#    #+#              #
#    Updated: 2024/09/04 14:53:53 by mekundur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
HEADER = fdf.h
LIBFT = ./libft/libft.a
MLX42 = ./MLX42/build/libmlx42.a
SOURCES = main.c get_map_data.c draw_map.c dda.c 

OBJECTS = $(SOURCES:.c=.o)

all : $(NAME) 

$(LIBFT) :
	@echo "<Compiling libft>"
	@make -C ./libft

$(MLX42) :
	@if [ ! -d "MLX42" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	@cd MLX42 && cmake -B build && cmake --build build -j4

%.o: %.c Makefile $(LIBFT) $(MLX42) 
	@cc -c -g -Werror -Wall -Wextra $< -o $@ 

$(NAME) : $(HEADER) $(MLX42) $(LIBFT) $(OBJECTS) Makefile
	@echo "Creating the program <fdf>"
	@cc -g -Werror -Wall -Wextra $(OBJECTS) $(LIBFT) $(MLX42) -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)

clean :
	@echo "Removing object files"
	@rm -f $(OBJECTS)
	@make clean -C ./libft	
	@make clean -C ./MLX42/build

fclean : clean 
	@echo "Removing the executable <fdf>"
	@rm -f fdf
	@make fclean -C ./libft

re : fclean all

.PHONY: all, clean, fclean, re
