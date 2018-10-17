.PHONY: all clean fclean re

CC = gcc -g

FLAGS = -Wall -Wextra -Werror

CPP_FLAGS = -Iinclude

NAME = corewar

SRC_PATH = ./src
LIB_PATH = ./lib
INC_PATH = ./inc
OBJ_PATH = ./obj
OBJLIB_PATH = ./obj


SRC_NAME =	main.c tools.c		insert_instructions.c 	collect_champ.c \
			collect_inputs.c	play.c 					collecting_tools.c \
			init_process.c		check_instruction.c \
			add.c				aff.c \
			and.c				fork.c \
			ld.c				ldi.c \
			lfork.c				live.c \
			lld.c				lldi.c \
			or.c				st.c \
			sti.c				sub.c \
			xor.c				zjmp.c \
			ocp.c 				set_ramvalue.c \
			get_dir.c			get_indir.c \
			get_reg.c			process.c \
			memclear.c			purge_process.c \
			get_name_champ.c	ft_strjoin.c \
			sound.c

LIB_NAME = 	ft_putchar.c ft_putstr.c ft_strdup.c \
			ft_atoi.c ft_memalloc.c ft_memalloc_c.c \
			ft_putnbr.c ft_strcmp.c ft_strcpy.c  \
			ft_strlen.c ft_strstr.c pos_in_str.c ft_memset.c  ft_strcat.c \
			ft_puttable.c ft_strchr.c \
			ft_memcpy.c pos_str_tab.c \
			ft_putstr_fd.c ft_bzero.c ft_putchar_fd.c ft_isdigit.c \
			ft_atoi_base.c ft_put3str.c ft_isnumber.c ft_putstrnbrstr.c \
			ft_putnbrstrnbr.c \

INC_NAME = corewar.h

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJLIB_NAME = $(LIB_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
LIB = $(addprefix $(LIB_PATH)/, $(LIB_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))
OBJLIB = $(addprefix $(OBJLIB_PATH)/,$(OBJLIB_NAME))

all: $(NAME)

$(NAME): $(OBJ) $(OBJLIB)
	@$(CC) $(FLAGS) $(OBJ) $(OBJLIB) -o $(NAME)
	@echo "\033[1;34mcorewar\t\t\033[1;33mCreation\t\033[0;32m[OK]\033[0m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(FLAGS) -I./inc -o $@ -c $<

$(OBJLIB_PATH)/%.o: $(LIB_PATH)/%.c
	@mkdir $(OBJLIB_PATH) 2> /dev/null || true
	@$(CC) $(FLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH) $(OBJLIB)
	@echo "\033[1;34mcorewar\t\t\033[1;33mCleaning obj\t\033[0;32m[OK]\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[1;34mcorewar\t\t\033[1;33mCleaning lib\t\033[0;32m[OK]\033[0m"

re: fclean all
