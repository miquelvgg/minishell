# Executable name
NAME = minishell
CC = cc

# Compiler flags
CFLAGS = -Wall -Werror -Wextra -MD -MP	# Estass flags son importantes
BFLAGS = -g -fsanitize=address
RDFLAG = -lreadline

#Libs
LIBFT_DIR = libft

# Directories
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = libs
INC_DIR = Includes
DEPS_DIR = deps

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(DEPS_DIR)/%.d)
CLIB = .a #Determina tipo de libreria para si windows o linux

# Rules
all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIB_DIR)/$(LIBFT_DIR)$(CLIB)
	$(CC) $(CFLAGS) -v -o $@ $^ -I $(INC_DIR) 

#	$(CC) $(CFLAGS) -v -o $@ $^ -I $(INC_DIR) -l:$(LIBFT_DIR)/$(LIBFT_DIR)$(CLIB)

$(LIB_DIR)/$(LIBFT_DIR)$(CLIB):
	@make -C $(LIBFT_DIR) # Compile libft library
	@mkdir -p $(LIB_DIR) # Create libs directory if it doesn't exist
	@cp -a $(LIBFT_DIR)/$(LIBFT_DIR)$(CLIB) $(LIB_DIR)/ # Copy the library to libs

$(INC_DIR):
	@mkdir -p $(INC_DIR) # Create Includes directory if it doesn't exist
	@cp -a $(LIBFT_DIR)/$(INC_DIR)/*.h $(INC_DIR) # Copy the header files to Includes

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c makefile
	@mkdir -p $(OBJ_DIR)  # Create object directory if it doesn't exist
	@mkdir -p $(DEPS_DIR)  # Create dependencies directory if it doesn't exist
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(DEPS_DIR)/$*.d -I $(INC_DIR) # Compile source file to object file and generate .d file

# Include dependency files
-include $(DEP_FILES)

norm:
	norminette $(Includes) $(SRC_DIR)# $(LIBFT_DIR)

mem:	# por que tiene valgrind si en las flags esta sanitizer?
	valgrind --track-origins=yes --show-leak-kinds=all --leakcheck=full ./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)  # Remove object files
	@rm -rf $(LIB_DIR) # Remove libs
	@rm -rf $(DEPS_DIR) # Remove libs
	@make fclean -C $(LIBFT_DIR)  # Clean libft

fclean: clean
	@rm -f $(NAME)  # Remove the executable

re: fclean all  # Rebuild the project

.PHONY: all clean fclean re
