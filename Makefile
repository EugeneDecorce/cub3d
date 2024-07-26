# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user <user@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 13:50:03 by rdias-ba          #+#    #+#              #
#    Updated: 2024/07/26 08:15:08 by user             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 	cub3D
BONUS			= 	cub3D_bonus
LIBFT			= 	libft/libft.a
MLX				= 	minilibx-linux/libmlx.a
HEADERS			=	cub3d.h

# Files
BONUS_SRC		=	animation.c minimap.c mouse.c
FILES_SRC		=	main.c
FILES_UTILS		=	error.c map_utils.c textures_init.c string_utils.c mlx_utils.c free_utils.c math_utils.c movements.c is_blocking_utils.c dda_utils.c
FILES_PARSING	=	parsing.c texture_alloc.c color_alloc.c map_rules.c player.c
FILES_RENDERING	=	create_frame.c dda.c draw.c

# Directories
DIR_BONUS		=	bonus/
DIR_MLX			=	minilibx-linux/
DIR_FT			=	libft/
DIR_INC			=	headers/
DIR_MAIN		=	main/
DIR_SRC			=	srcs/
DIR_BONUS		=	bonus/
DIR_RENDERING	=	rendering/
DIR_PARSING		=	parsing/
DIR_EXTRA		=	bonus/
DIR_UTILS		=	utils/
DIR_OBJS		=	objs/
DIR_BONUS_OBJS	=	objs_bonus/

# Pathing

INCS			=	$(addprefix $(DIR_INC), $(HEADERS))

SRCS			=	$(addprefix $(DIR_SRC)$(DIR_MAIN)$(DIR_BONUS), $(BONUS_SRC)) \
					$(addprefix $(DIR_SRC)$(DIR_MAIN), $(FILES_SRC)) \
					$(addprefix $(DIR_SRC)$(DIR_MAIN)$(DIR_UTILS), $(FILES_UTILS)) \
					$(addprefix $(DIR_SRC)$(DIR_MAIN)$(DIR_PARSING), $(FILES_PARSING)) \
					$(addprefix $(DIR_SRC)$(DIR_MAIN)$(DIR_RENDERING), $(FILES_RENDERING)) \

OBJS			=	$(subst $(DIR_SRC), $(DIR_OBJS), $(SRCS:.c=.o))

# Commands

CC				= 	cc
CFLAGS			= 	-Wall -Wextra -Werror
INCLUDES 		= 	-I $(DIR_FT) -I $(DIR_INC) -I $(DIR_MLX)
DEPENDENCES 	= 	-L minilibx-linux -lmlx -lXext -lX11 -lm -L libft -lft
RM				= 	rm -rf

# Colors

BLACK=\033[30m
RED=\033[31m
GREEN=\033[32m
YELLOW=\033[33m
BLUE=\033[34m
PURPLE=\033[35m
CYAN=\033[36m
WHITE=\033[37m

# Text

ERASE=\033[2K\r
RESET=\033[0m
BOLD=\033[1m
FAINT=\033[2m
ITALIC=\033[3m
UNDERLINE=\033[4m

# Rules

all: makemlx makelibft $(NAME)

makemlx:
	@$(MAKE) -C $(DIR_MLX) --quiet --no-print-directory

makelibft:
	@$(MAKE) -C $(DIR_FT) --no-print-directory

$(MLX): makemlx

$(LIBFT): makelibft

$(NAME): $(OBJS) $(INCS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBFT) $(MLX) $(OBJS) -o $@ $(DEPENDENCES)
	@echo "$(ERASE)\n$(RED)$(BOLD)   executable $(NAME) created $(RESET)"
	@echo "$(ERASE)run $(BOLD)./$(NAME) path_to_map.cub$(RESET) to play.$(RESET)"

$(DIR_OBJS)%.o: $(DIR_SRC)%.c $(INCS) $(LIBFT) $(MLX) | $(DIR_OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c -g $< -o $@
	@echo "$(ERASE)$(BOLD)$(NAME)$(RESET)$(GREEN) compiling... $(RESET)$<"

$(DIR_OBJS):
	@mkdir -p $(DIR_OBJS) \
	$(DIR_OBJS)$(DIR_MAIN) \
	$(DIR_OBJS)$(DIR_MAIN)$(DIR_BONUS) \
	$(DIR_OBJS)$(DIR_MAIN)$(DIR_RENDERING) \
	$(DIR_OBJS)$(DIR_MAIN)$(DIR_PARSING) \
	$(DIR_OBJS)$(DIR_MAIN)$(DIR_RAYCASTING) \
	$(DIR_OBJS)$(DIR_MAIN)$(DIR_UTILS)
	@echo "$(ERASE)$(BOLD)$(NAME)$(RESET)$(GREEN) objects directory created.$(RESET)"

clean:
	@$(RM) $(OBJS)
	@$(RM) $(BONUS_OBJS)
	@$(RM) $(DIR_OBJS)
	@$(MAKE) clean -C $(DIR_FT) --no-print-directory
	@$(MAKE) clean -C $(DIR_MLX) --no-print-directory
	@echo "$(ERASE)$(BOLD)$(NAME)$(RESET)$(GREEN) objects deleted.$(RESET)";

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(DIR_FT) --no-print-directory
	@echo "$(ERASE)$(BOLD)libmlx.a$(RESET)$(GREEN) deleted.$(RESET)"

re: fclean all

.PHONY: all clean fclean re makemlx makelibft bonus
