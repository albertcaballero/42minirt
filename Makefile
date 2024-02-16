RED     =   \033[38;5;161m
GREEN   =   \033[38;5;154m
YELLOW  =   \033[38;5;227m
BLUE    =   \033[38;5;81m
PURPLE  =   \033[38;5;93m
PINK    =   \033[38;5;219m
NC      =   \033[0m

NAME = minirt
FLAGS = -Wall -Wextra -Werror -O3
LIB = libft/libft.a
MLX = minilibx/libmlx.a

HEADER_FILES = minirt.h vectors.h
HEADERS = $(addprefix inc/,$(HEADER_FILES))
INCLUDES = -I libft/ -I inc/ -I minilibx/

SRC_PARS = parsing/open_map.c parsing/check_numbers.c parsing/init_scene.c parsing/parse_lines.c parsing/init_objects.c
SRC_MAIN = minirt.c error_mngr.c utils.c
SOURCES = $(SRC_MAIN) $(SRC_PARS)
SRC = $(addprefix src/,$(SOURCES))

OBJS = $(addprefix temp/,$(SRC:.c=.o))

all: tmp make_lib make_mlx $(NAME)

$(NAME): $(OBJS) $(LIB) $(MLX)
	cc $(FLAGS) -I inc/ -L libft -lft -o $@ $^ -framework OpenGL -framework AppKit -lm -L minilibx -lmlx
	@echo "$(PURPLE)=====MINIRT COMPILED=====$(NC)"

temp/%.o: %.c $(LIB) $(MLX) $(HEADERS) Makefile
	@mkdir -p $(dir $@)
	cc $(FLAGS) $(INCLUDES) -c -o $@ $<

tmp:
	mkdir -p temp

make_lib:
	@$(MAKE) -C libft --no-print-directory

make_mlx:
	@$(MAKE) -C minilibx --no-print-directory

clean:
	@rm -rf temp
	@$(MAKE) fclean -C libft --no-print-directory
	@$(MAKE) fclean -C minilibx --no-print-directory
	@echo "$(RED)MINIRT OBJ DELETED$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)MINIRT ALL DELETED$(NC)"

re: fclean all

.PHONY: tmp make_lib make_mlx clean fclean re all