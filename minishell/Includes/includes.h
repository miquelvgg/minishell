/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:50:45 by epascual          #+#    #+#             */
/*   Updated: 2025/12/29 18:50:46 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

// Includes de las librerias necesarias por el readme

// Pipex
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "libft.h"
# include "eloi.h"
# include "micky.h"
# include "Structs.h"

// Terminal y entorno
# include <termios.h>
# include <sys/ioctl.h>
# include <termcap.h>

// Archivos y directorios
# include <dirent.h>
# include <sys/stat.h>

// Senyales

# include <signal.h>

// Readline

# include <readline/readline.h>
# include <readline/history.h>

#endif
