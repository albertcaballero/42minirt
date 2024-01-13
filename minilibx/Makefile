RED     =   \033[38;5;161m
GREEN   =   \033[38;5;154m
YELLOW  =   \033[38;5;227m
BLUE    =   \033[38;5;81m
PURPLE  =   \033[38;5;93m
PINK    =   \033[38;5;219m
NC      =   \033[0m

NAME		=	libmlx.a

SRC_C	=	mlx_shaders.c mlx_xpm.c mlx_int_str_to_wordtab.c
SRC_M	= 	mlx_new_image.m mlx_new_window.m mlx_init_loop.m

OBJ_DIR	=	./obj/
OBJ_C	=	$(addprefix $(OBJ_DIR)src_c/, $(SRC_C:%.c=%.o))
OBJ_M	=	$(addprefix $(OBJ_DIR)src_m/, $(SRC_M:%.m=%.o))

CFLAGS	+=	-O2 -Wno-deprecated-declarations -DSTRINGPUTX11

all		:
	@$(MAKE) $(NAME)

$(OBJ_DIR)src_c/%.o: %.c Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)src_m/%.o: %.m Makefile
	@mkdir -p $(dir $@)
	@$(CC) -MT $@ $(CFLAGS) -MMD -MP -c $< -o $@


$(NAME)::	$(OBJ_C) $(OBJ_M)
	@ar -crs $@ $(OBJ_C) $(OBJ_M)
	# @#ranlib $@
	@echo "$(GREEN)MLX COMPILED$(NC)"
$(NAME)::
	@echo -n

clean	:
	@rm -rf $(OBJ_DIR) *~
	@rm -f mlx_app
	@echo "$(RED)MLX OBJS DELETED$(NC)"

fclean	:
	@$(MAKE) clean
	@$(RM) $(NAME)
	@echo "$(RED)MLX EXEC DELETED$(NC)"

re: fclean all

.PHONY:	all clean fclean re