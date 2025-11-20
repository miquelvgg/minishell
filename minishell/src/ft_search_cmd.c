#include "minishell.h"

#ifdef  M_EXTER_FUNC

// Función personalizada para construir paths (similar a snprintf pero específica)
void build_path(char *dest, size_t dest_size, const char *dir, const char *command) {
    size_t dir_len ;
    size_t cmd_len ;
	char *p;
    
	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(command);
    // Verificar que hay espacio suficiente: dir + "/" + command + null terminator
    if (dir_len + 1 + cmd_len + 1 > dest_size) {
        dest[0] = '\0'; // Buffer demasiado pequeño
        return;
    }
    p= dest;
    // Copiar el directorio
    const char *src_dir = dir;
    while (*src_dir) {
        *p++ = *src_dir++;
    }
    // Añadir el separador /
    *p++ = '/';
    // Copiar el comando
    const char *src_cmd = command;
    while (*src_cmd) {
        *p++ = *src_cmd++;
    }
    // Terminar la cadena
    *p = '\0';
}

// Función personalizada para tokenizar PATH (reemplaza strtok)
char *custom_strtok(char *str, const char *delim, char **saveptr) {
    if (str != NULL) {
        *saveptr = str;
    }
    
    if (*saveptr == NULL || **saveptr == '\0') {
        return NULL;
    }
    
    // Saltar delimitadores iniciales
    while (**saveptr && strchr(delim, **saveptr) != NULL) {
        (*saveptr)++;
    }
    
    if (**saveptr == '\0') {
        return NULL;
    }
    
    char *start = *saveptr;
    
    // Encontrar el próximo delimitador
    while (**saveptr && strchr(delim, **saveptr) == NULL) {
        (*saveptr)++;
    }
    
    if (**saveptr != '\0') {
        *(*saveptr)++ = '\0';
    }
    
    return start;
}

int is_external_command(char *command)
{
    // Si el comando ya contiene '/', verificar directamente
    if (strchr(command, '/') != NULL) {
        struct stat st;
        return (stat(command, &st) == 0 && st.st_mode & S_IXUSR);
    }
    
    char *path_env = getenv("PATH");
    if (path_env == NULL) {
        return 0;
    }
    
    // Hacer una copia del PATH para no modificar el original
    char *path_copy = malloc(strlen(path_env) + 1);
    if (path_copy == NULL) {
        return 0;
    }
    strcpy(path_copy, path_env);
    
    char *saveptr = NULL;
    char *dir ;
    int found = 0;
	char full_path[1024];
    
	dir = custom_strtok(path_copy, ":", &saveptr);
    while (dir != NULL) {
       // Usar nuestra función personalizada en lugar de sprintf
        build_path(full_path, sizeof(full_path), dir, command);
        if (full_path[0] != '\0') { // Solo si build_path tuvo éxito
            struct stat st;
            if (stat(full_path, &st) == 0 && st.st_mode & S_IXUSR) {
                found = 1;
                break;
            }
        }
        dir = custom_strtok(NULL, ":", &saveptr);
    }
    free(path_copy);
    return found;
}

// Versión alternativa más simple si prefieres evitar strtok completamente
int is_ext_comm_sim(char *command)
{
    // Si el comando ya contiene '/', verificar directamente
    if (strchr(command, '/') != NULL) {
        struct stat st;
        return (stat(command, &st) == 0 && st.st_mode & S_IXUSR);
    }
    
    char *path_env = getenv("PATH");
    if (path_env == NULL) {
        return 0;
    }
    
    char *path = path_env;
    int found = 0;
    
    while (*path != '\0') {
        // Encontrar el próximo ':' o fin de cadena
        char *colon = strchr(path, ':');
        size_t dir_len;
        
        if (colon != NULL) {
            dir_len = colon - path;
        } else {
            dir_len = strlen(path);
        }
        
        // Construir el path completo manualmente
        char full_path[1024];
        char *p = full_path;
        
        // Copiar el directorio
        const char *src_dir = path;
        for (size_t i = 0; i < dir_len && i < sizeof(full_path) - 1; i++) {
            *p++ = *src_dir++;
        }
        
        // Añadir '/' si hay espacio
        if (p < full_path + sizeof(full_path) - 1) {
            *p++ = '/';
        }
        
        // Copiar el comando
        const char *src_cmd = command;
        while (*src_cmd != '\0' && p < full_path + sizeof(full_path) - 1) {
            *p++ = *src_cmd++;
        }
        
        // Terminar la cadena
        *p = '\0';
        
        // Verificar si el archivo existe y es ejecutable
        struct stat st;
        if (stat(full_path, &st) == 0 && st.st_mode & S_IXUSR) {
            found = 1;
            break;
        }
        
        // Avanzar al siguiente directorio en PATH
        if (colon == NULL) {
            break;
        }
        path = colon + 1;
    }
    
    return found;
}
#endif