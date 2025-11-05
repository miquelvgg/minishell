# minishell
Our own terminal 42 project.

# TO DO

## Organizacion
Tokenizacion
- [ ] Parseo de token
- [ ] Elimina significado especial
- [ ] Expande significado especial
- [ ] Shell expansion
- [ ] Redireccion
Ejecucion
- [ ] Ejecutar comando
- [ ] Interpretar operadores
- [ ] Espera exit status de comando
- [ ] Hace exit statuss disponible para inspeccion o proceso
## Subject
- [ ] Entrada
- [ ] Historial
- [ ] Global de la senyal
- [ ] Redirecciones
- [ ] Pipes |
- [ ] Entorno
- [ ] $?
- [ ]
## Interactivos
- [ ] cntr-C
- [ ] cntr-D
- [ ] cntr-\
## builtins
- [ ] echo -n
- [ ] cd
- [ ] pwd
- [ ] export
- [ ] unset
- [x] env
- [ ] exit
## Isdefinition
Son funciones que comprueban y devuelven booleanos.
- [x] metacharacter
- [ ] word
- [ ] token
- [ ] filename
- [x] blank
- [x] whitespace
- [ ] Control operator
- [ ] Redirection operator
## Extras
- [ ] &&
- [ ] ||
- [ ] *

# Funciones permitidas

## Funciones estudiadas anteriormente
### Librerías estándar de C (stdio.h, stdlib.h, string.h)
- printf: Imprime texto formateado en la salida estándar.
- malloc: Asigna un bloque de memoria dinámica.
- free: Libera la memoria asignada previamente por malloc.
- exit: Termina la ejecución del programa.
- strerror: Devuelve una cadena de texto que describe un código de error.
- perror: Imprime un mensaje de error en la salida estándar de error.

### Librerías de entrada/salida (unistd.h, sys/wait.h, fcntl.h)
- write: Escribe datos en un descriptor de archivo.
- access: Comprueba los permisos de un archivo.
- open: Abre un archivo y devuelve un descriptor.
- read: Lee datos de un descriptor de archivo.
- close: Cierra un descriptor de archivo.
- fork: Crea un nuevo proceso hijo.
- wait: Espera a que un proceso hijo termine.
- waitpid: Espera a un proceso hijo específico.
- execve: Reemplaza el proceso actual con un nuevo programa.
- dup: Duplica un descriptor de archivo.
- dup2: Duplica un descriptor de archivo en un número específico.
- pipe: Crea un canal de comunicación unidireccional.

## Funciones nuevas
### [Readline](https://man7.org/linux/man-pages/man3/readline.3.html) (readline/readline.h, readline/history.h)
- readline: Lee una línea desde la entrada de usuario con funciones de edición e historial.
- rl_clear_history: Borra todo el historial de comandos.
- rl_on_new_line: Mueve el cursor a una nueva línea de la consola.
- rl_replace_line: Reemplaza el texto en la línea de edición actual.
- rl_redisplay: Redibuja la línea de edición actual.
- add_history: Agrega una línea al historial de comandos.

### Librerías de procesos y señales (sys/wait.h, signal.h)
- wait3: Espera a un proceso hijo y obtiene información detallada.
- wait4: Similar a wait3, con opciones adicionales.
- signal: Establece el manejo de una señal.
- sigaction: Examina o cambia la acción de una señal.
- kill: Envía una señal a un proceso.

### Librerías de sistema de archivos y directorios (unistd.h, sys/stat.h, dirent.h)
- getcwd: Obtiene la ruta del directorio de trabajo actual.
- chdir: Cambia el directorio de trabajo.
- stat: Obtiene información sobre un archivo.
- lstat: Similar a stat, pero sin seguir enlaces simbólicos.
- fstat: Obtiene información sobre un archivo a través de su descriptor.
- unlink: Elimina un nombre de archivo.
- opendir: Abre un directorio.
- readdir: Lee la siguiente entrada de un directorio abierto.
- closedir: Cierra un directorio.

## Librerías de terminal y entorno (unistd.h, termios.h, sys/ioctl.h, termcap.h, stdlib.h)
- isatty: Comprueba si un descriptor de archivo es una terminal.
- ttyname: Obtiene el nombre del dispositivo de terminal.
- ttyslot: Busca el número de entrada de la terminal en un archivo de configuración.
- ioctl: Controla un dispositivo de E/S.
- getenv: Obtiene el valor de una variable de entorno.
- tcsetattr: Establece los atributos del terminal.
- tcgetattr: Obtiene los atributos del terminal.
- tgetent: Inicializa la base de datos de capacidades de la terminal.
- tgetflag: Obtiene el valor de una capacidad booleana de la terminal.
- tgetnum: Obtiene el valor de una capacidad numérica de la terminal.
- tgetstr: Obtiene el valor de una capacidad de cadena de la terminal.
- tgoto: Mueve el cursor en la terminal usando una cadena de capacidad.
- tputs: Escribe una cadena de capacidad de la terminal.

[Explicacion de cada funcion y su cabecera](https://42-cursus.gitbook.io/guide/3-rank-03/minishell/functions)

# Comandos utiles

## Bash
ls -l /proc/$$/fd : Sirve para ver todos los filedescriptors abiertos en un momento.
## Git
git checkout 'rama' : Cambia de rama
git pull : Recoje cambios 
git log : Dice los comits realizados
git reset 'id comit' : Deshace todo lo de despues de ese comit
git merge 'rama' : Une la rama a este checkout.

# Errores habituales

En lugar de usar el infile y outfile, usa el infile y un temporal que despues escribas en el outfile para evitar errores en el caso de que el infile sea igual que el outfile.

No poner 42headers hasta terminar el proyecto.

Hacer una carpeta para las cosas que sirven para ambas

> file echo "hola" << start > file1 | echo "adios" << end > file2

Hacer un .h por persona y uno de librerias para evitar merge conflict.
