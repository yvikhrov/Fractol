NAME = fractol

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/
LIB_PATH = ./

SRC_NAME =	cl.c \
			clamp.c \
			color.c \
			handle_input.c \
			image.c \
			init.c \
			loop.c \
			main.c \
			mix.c \
			parsing.c \
			timer.c \
			utility.c \
			vec2i.c
			
OBJ_NAME = $(SRC_NAME:.c=.o)
LIBS = libft libmlx

LIB_FOLDERS = $(addprefix $(LIB_PATH), $(LIBS))
LIB_INC = $(addsuffix /include, $(LIB_FOLDERS))

INC_PATH += $(LIB_INC)

FLAGS = -pedantic -Wall -Wextra -Werror
CC = clang
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIB =	./libft/libft.a \
		./libmlx/libmlx.a
INC = $(addprefix -I, $(INC_PATH))

FRAMEWORKS =  -framework OpenGL -framework Appkit -framework OpenCL

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_PATH)libft
	@make -C $(LIB_PATH)libmlx
	$(CC) $(INC) $(LIB) $(FRAMEWORKS) $(OBJ) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_PATH)
	@make -C $(LIB_PATH)libmlx clean
	@make -C $(LIB_PATH)libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_PATH)libft fclean
	@make -C $(LIB_PATH)libmlx fclean

re: fclean all

.PHONY: re fclean all clean