NAME = RTv1

CC = gcc -g

SRC_DIR = ./src/
SRC_LIST = main.c ft_paint_object.c ft_pixel_color.c ft_ray_trace_object.c \
		ft_operation_key.c ft_vector_function.c ft_vector_function_2.c \
		ft_init_function.c ft_init_function_2.c ft_init_object.c scene_object.c

SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJECTS_DIR = ./objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJECTS = $(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST))

HEADER_DIR = ./includes/
HEADER_LIST = rtv1.h object.h manual.h key.h
HEADER = $(addprefix $(HEADER_DIR), $(HEADER_LIST))

INCLUDES = -I $(HEADER_DIR) -I $(LIBFT_DIR)

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ../libft/
LIBRARIES = $(LIBFT) $(MLX)

MLX = ../minilibx_macos/libmlx.a -framework OpenGL -framework AppKit
# MLX = ../minilibx_macos/libmlx.a -L /path/to/lib libstuff.dylib OpenGL\
#  -L /path/to/lib libstuff.dylib AppKit
#MLX = ../minilibx/libmlx.a -lXext -lX11 -lm 

FLAGS = -Wall -Wextra -Werror -std=c99 -O3
#FLAGS = -Wall -Wextra -Werror -std=c99 -O3 -lpthread

.PHONY: all clean fclean re FAKE

all: $(NAME)

$(NAME):$(LIBFT) $(OBJECTS_DIR) $(OBJECTS)
		$(CC) $(FLAGS) -o $(NAME) $(OBJECTS) $(LIBRARIES)
		@echo "\033[32m$(NAME): was created\033[0m"

$(OBJECTS_DIR):
		@mkdir -p $(OBJECTS_DIR)
		@echo "\033[32m$(NAME): $(OBJECTS_DIR)directory was created\033[0m"

$(OBJECTS_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
		@$(CC) $(FLAGS) -c $(INCLUDES) -o $@ $<

$(LIBFT): FAKE
		@$(MAKE) -C $(LIBFT_DIR)

clean:
		@rm -rf $(OBJECTS_DIR)
		@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
		@/bin/rm -f $(NAME)
		@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
# minilibx_macos/libmlx.a -framework OpenGL -framework AppKit
# MLX = ./minilibx/libmlx.a -lXext -lX11 -lm // for linux GNU
# -L ../minilibx -lmlx -framework OpenGL -framework AppKit
# MLX = ./minilibx/libmlx.a -lXext -lX11 -lm // for linux GNU
# INCLUDES = -I$(HEADER_DIR) -I$(LIBFT_HEADERS) -I$(MINILIBX_HEADERS)
# $(CC) $(FLAGS) -c -I$(HEADERS_DIRECTORY) -o $@ $<
# $(CC) $(FLAGS) -MD -c $(INCLUDES) -o $@ $<
#-fsanitize=address
# $(CC) $(FLAGS) -o $(NAME) $(OBJECTS) $(INCLUDES) $(LIBRARIES)
