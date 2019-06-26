NM = 			ft_nm
OTOOL = 		ft_otool

OBJ = 			obj/
SRC = 			src/

CC = gcc
CFLAGS += 		-g3 -Wall -Werror -Wextra
CFLAGS += 		-I includes/ -I libft/

LIBFT_PATH = 	libft/
LIBFT = 		libft/libft.a

SRCS_NM =		main.c start_process_nm.c  \
				process_fat_header_32.c process_fat_header_64.c\
				process_archive.c process_header_64.c process_header_32.c symbol_nm.c segment_nm.c

SRCS_OTOOL =	main.c start_process_otool.c process_fat_header_32.c process_fat_header_64.c \
				process_archive.c process_header_64.c process_header_32.c segment_otool.c

SRCS_CMN =		error.c arch.c sizeof_header.c print_address.c swap_bits.c \
				load_file.c get_header.c get_arch.c cpu.c sort.c

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
	@echo "Cleaning the repo..."
	@make clean -C  $(LIBFT_PATH)
	@rm -rf $(NM_OBJ)
	@rm -rf $(OTOOL_OBJ)
	@rm -rf $(CMN_OBJ)

fclean: clean
	@echo "Cleaning the repo..."
	@rm -rf $(NM) $(OTOOL)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

norminette:
	norminette inc/ src/
