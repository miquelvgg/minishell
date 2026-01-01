# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/18 09:24:22 by mvives-s          #+#    #+#              #
#    Updated: 2026/01/01 17:57:37 by epascual         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# Nombre de la biblioteca
NAME    = libft.a

# Herramientas
CC      = gcc
AR      = ar rcs
RM      = rm -rf
CFLAGS  = -Wall -Wextra -Werror

# Directorio de objetos: usa OBJDIR si viene de make -C, sino obj/
OBJ_DIR = $(if $(OBJDIR),$(OBJDIR),obj)

# Lista **manual** de tus .c en libs/libft
# (según tree.txt de tu proyecto) :contentReference[oaicite:0]{index=0}
SRCS = ft_atoi.c        ft_bzero.c     ft_calloc.c    ft_extfun.c     \
       ft_extprint.c    ft_isalnum.c   ft_isalpha.c   ft_isascii.c    \
       ft_isdigit.c     ft_isprint.c   ft_itoa.c      ft_memchr.c     \
       ft_memcmp.c      ft_memcpy.c    ft_memmove.c   ft_memset.c     \
       ft_printf.c      ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c  \
       ft_putstr_fd.c   ft_split.c     ft_strchr.c    ft_strcmp.c     \
       ft_strdup.c      ft_striteri.c  ft_strjoin.c   ft_strlcat.c    \
       ft_strlcpy.c     ft_strlen.c    ft_strmapi.c   ft_strncmp.c    \
       ft_strnstr.c     ft_strrchr.c   ft_strtrim.c   ft_substr.c     \
       ft_tolower.c     ft_toupper.c   ft_get_next_line.c             \
	   ft_strcpy.c

# Cada foo.c → OBJ_DIR/foo.o
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)


# 1) Crear carpeta de objetos y luego la biblioteca
all: dirs $(OBJ_DIR)/$(NAME)

# 2) Asegura que exista el directorio
dirs:
	@mkdir -p $(OBJ_DIR)

# 3) Empaqueta todos los .o en OBJ_DIR/libft.a
$(OBJ_DIR)/$(NAME): $(OBJS)
	@$(AR) $@ $^

# 4) Compila cada .c desde libs/libft/ a OBJ_DIR/*.o
$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@


# Borra sólo los .o
clean:
	$(RM) $(OBJ_DIR)

# Borra .o **y** la librería .a
fclean: clean
	$(RM) $(OBJ_DIR)/$(NAME)

# Reconstruye de cero
re: fclean all

.PHONY: all dirs clean fclean re
