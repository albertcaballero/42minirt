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

SRC_PARS = parsing/open_map.c parsing/check_numbers.c parsing/init_scene.c parsing/parse_lines.c parsing/init_objects.c
SRC_MAIN = minirt.c error_mngr.c utils.c
SRC = $(SRC_MAIN) $(SRC_PARS)

OBJS = $(addprefix temp/,$(SRC:.c=.o))

all: tmp make_lib make_mlx $(NAME)

$(NAME): $(OBJS) $(LIB) $(MLX)
	cc $(FLAGS) -L libft -lft -o $@ $^ -framework OpenGL -framework AppKit -lm -L minilibx -lmlx
	@echo "$(PURPLE)=====MINIRT COMPILED=====$(NC)"

temp/%.o: %.c minirt.h $(LIB) $(MLX) Makefile
	@mkdir -p $(dir $@)
	cc $(FLAGS) -c -o $@ $<

tmp:
	mkdir -p temp

make_lib:
	@$(MAKE) -C libft --no-print-directory

make_mlx:
	@$(MAKE) -C minilibx --no-print-directory

clean:
	@rm -f $(OBJS)
	@$(MAKE) fclean -C libft --no-print-directory
	@$(MAKE) fclean -C minilibx --no-print-directory
	@rm -rf $(DIR_O)
	@echo "$(RED)FDF OBJ DELETED$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)FDF ALL DELETED$(NC)"

re: fclean all

.PHONY: tmp make_lib make_mlx clean fclean re all
.SILENT: