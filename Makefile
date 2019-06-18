NM = ft_nm
OTOOL = ft_otool

OBJ = obj/
SRC = src/

CC = gcc
CFLAGS += -Wall -Werror -Wextra
CFLAGS += -I includes/ -I libft/

LIBFT_PATH = libft/
LIBFT = libft/libft.a

SRCS_NM = main.c load_file.c start_process.c
SRCS_OTOOL = main.c
SRCS_CMN = error.c

NM_OBJ = $(addprefix $(OBJ)$(NM)/, $(SRCS_NM:.c=.o))
OTOOL_OBJ = $(addprefix $(OBJ)$(OTOOL)/, $(SRCS_OTOOL:.c=.o))
CMN_OBJ = $(addprefix $(OBJ), $(SRCS_CMN:.c=.o))

all: $(NM) $(OTOOL)

$(NM): $(NM_OBJ) $(CMN_OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(LIBFT) -o $@ $^

$(OTOOL): $(OTOOL_OBJ) $(CMN_OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(LIBFT) -o $@ $^

$(NM_OBJ): $(OBJ)$(NM)/%.o: $(SRC)$(NM)/%.c
	@echo "Compiling nm objects..."
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "Done!"

$(OTOOL_OBJ): $(OBJ)$(OTOOL)/%.o: $(SRC)$(OTOOL)/%.c
	@echo "Compiling otool objects..."
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "Done!"

$(CMN_OBJ): $(OBJ)%.o: $(SRC)/%.c
	@echo "Compiling commun objects..."
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "Done!"

$(LIBFT):
	@echo "Compiling libft objects..."
	@make -C $(LIBFT_PATH)
	@echo "Done!"

clean:
	@make clean -C  $(LIBFT_PATH)
	@rm -rf $(NM_OBJ)
	@rm -rf $(OTOOL_OBJ)

fclean: clean
	@rm -rf $(NM) $(OTOOL)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

norminette:
	norminette inc/ src/
