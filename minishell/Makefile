# Executable name
NAME = minishell
CC = cc

# Compiler flags
CFLAGS = -MD -MP -Wall -Werror -Wextra # Estas flags son importantes
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
SRC_FILES = $(SRC_DIR)/actions_utils.c \
$(SRC_DIR)/builtin_cmd.c \
$(SRC_DIR)/builtinhandler.c \
$(SRC_DIR)/cd.c \
$(SRC_DIR)/echo.c \
$(SRC_DIR)/env.c \
$(SRC_DIR)/envsorter.c \
$(SRC_DIR)/env_utils.c \
$(SRC_DIR)/env_utils_helper.c \
$(SRC_DIR)/errors.c \
$(SRC_DIR)/exacti_exec.c \
$(SRC_DIR)/exacti_ext.c \
$(SRC_DIR)/exaction.c \
$(SRC_DIR)/exacti_util.c \
$(SRC_DIR)/exitbuiltin.c \
$(SRC_DIR)/expand_utils.c \
$(SRC_DIR)/export.c \
$(SRC_DIR)/ft_actions.c \
$(SRC_DIR)/ft_expan.c \
$(SRC_DIR)/ft_isspace.c \
$(SRC_DIR)/ft_signal.c \
$(SRC_DIR)/ft_syntax.c \
$(SRC_DIR)/ft_token.c \
$(SRC_DIR)/ft_tools.c \
$(SRC_DIR)/hdoc_nam_rand.c \
$(SRC_DIR)/hdoc_exp_norm.c \
$(SRC_DIR)/hdoc_norm.c \
$(SRC_DIR)/hdoc_read_norm.c \
$(SRC_DIR)/initfd.c \
$(SRC_DIR)/input.c \
$(SRC_DIR)/main.c \
$(SRC_DIR)/mshell.c \
$(SRC_DIR)/pipas.c \
$(SRC_DIR)/pwd.c \
$(SRC_DIR)/selexecutor.c \
$(SRC_DIR)/token_utils.c \
$(SRC_DIR)/unset.c

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(DEPS_DIR)/%.d)
CLIB = .a #Determina tipo de libreria para si windows o linux

# Rules
all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIB_DIR)/$(LIBFT_DIR)$(CLIB)
	@$(CC) $(CFLAGS) -o $@ $^ -I $(INC_DIR) $(RDFLAG)
	@echo Minishell compilado.
#	$(CC) $(CFLAGS) -o $@ $^ -I $(INC_DIR) -l:$(LIBFT_DIR)/$(LIBFT_DIR)$(CLIB)

$(LIB_DIR)/$(LIBFT_DIR)$(CLIB):
	@make -C $(LIBFT_DIR) -s # Compile libft library
	@mkdir -p $(LIB_DIR) # Create libs directory if it doesn't exist
	@cp -a $(LIBFT_DIR)/$(OBJ_DIR)/$(LIBFT_DIR)$(CLIB) $(LIB_DIR)/ # Copy the library to libs

$(INC_DIR):
	@mkdir -p $(INC_DIR) # Create Includes directory if it doesn't exist
	@cp -a $(LIBFT_DIR)/$(INC_DIR)/*.h $(INC_DIR) # Copy the header files to Includes

# Compile source file to object file and generate .d file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	@mkdir -p $(OBJ_DIR)  # Create object directory if it doesn't exist
	@mkdir -p $(DEPS_DIR)  # Create dependencies directory if it doesn't exist
	@$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(DEPS_DIR)/$*.d -I $(INC_DIR) 

# Include dependency files
-include $(DEP_FILES)

norm:
	norminette $(Includes) $(SRC_DIR)# $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)  # Remove object files
	@rm -rf $(LIB_DIR) # Remove libs
	@rm -rf $(DEPS_DIR) # Remove libs
	@make fclean -C $(LIBFT_DIR) -s # Clean libft
	@echo Minishell Eliminado

test:
	clear
	make
	./$(NAME)

fclean: clean
	@rm -f $(NAME)  # Remove the executable

re: fclean all  # Rebuild the project

.SILENT: all clean
.PHONY: all clean fclean re
