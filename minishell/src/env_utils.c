#include "minishell.h"

// Encuentra una variable en env por el nombre
int find_env_var(char **env, const char *name, int name_len) {
  int i;

  i = 0;
  while (env[i]) {
    if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
      return (i);
    i++;
  }
  return (-1);
}

void init_minimal_env(t_data *shell) {
  char **newenv;
  char *pwd;
  char *pat;
  char cwd[PATH_MAX]; // Buffer for current working directory
  size_t pwd_len;

  // Allocate the env array (with space for 3 pointers + NULL terminator)
  newenv = shell->env;
  if (!newenv)
    return; // Handle malloc failure (e.g., exit or error message)

  // No necesitamos liberar shell->env aqui si ya viene allocado de fuera o es
  // NULL, pero si init_minimal_env se llama, asumimos shell->env no
  // inicializado o re-inicializando. OJO: shell->env llega como argumento pero
  // newenv = shell->env?? El codigo original hacia: newenv = shell->env; if
  // (!newenv) return; free(shell->env); ?? Eso estaba mal si shell->env era
  // NULL. Asumiremos que shell->env se debe asignar.

  // CORRECCION: Asignar a shell->env directamente.

  shell->env = (char **)ft_calloc(sizeof(char *), 3); // 2 vars + NULL
  if (!shell->env)
    return;

  // printf("PATH ALLOCADO\n");
  pat = ft_strdup(
      "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
  if (!pat) {
    free(shell->env);
    shell->env = NULL;
    return;
  }
  // printf("PATH ajustado\n");

  // Get actual current working directory and allocate/set PWD
  if (getcwd(cwd, sizeof(cwd)) == NULL)
    ft_strcpy(cwd, "/");
  pwd_len = ft_strlen("PWD=") + ft_strlen(cwd) + 1;
  // printf("PWDALLOCADO\n");
  pwd = (char *)ft_calloc(sizeof(char), pwd_len);
  if (!pwd) {
    free(pat);
    free(shell->env);
    shell->env = NULL;
    return;
  }
  ft_strcpy(pwd, "PWD=");
  ft_strlcat(pwd, cwd, pwd_len);
  // printf("PWD AJUSTADO\n");
  // Set the env array
  shell->env[0] = pat;
  shell->env[1] = pwd;
  shell->env[2] = NULL; // NULL-terminate
                        // printf("%s\n%s\n", pat, pwd);
}

// Actualiza una env var
static void update_env_var(t_data *shell, char *var_assignment, int idx) {
  free(shell->env[idx]);
  shell->env[idx] = ft_strdup(var_assignment);
}

// Assigna una env var
void set_env_var(t_data *shell, char *var_assignment) {
  char *equal_sign;
  int name_len;
  int idx;

  equal_sign = ft_strrchr(var_assignment, '=');
  if (!equal_sign)
    return;
  name_len = equal_sign - var_assignment;
  idx = find_env_var(shell->env, var_assignment, name_len);
  if (idx >= 0)
    update_env_var(shell, var_assignment, idx);
  else
    add_env_var(shell, var_assignment);
}

// Crea el primer env que sera usado luego
char **create_first_env(char **environ, t_data *shell) {
  char **new_env;
  int i;
  int c;

  c = ft_stringlen(environ);
  // Si no hay environ, init_minimal_env NO retorna un char**, modifica
  // shell->env void. El codigo original llamaba init_minimal_env(shell) pero
  // luego seguia ejecutando...

  if (!environ || environ[0] == NULL) {
    init_minimal_env(shell);
    return (shell->env); // Retornamos el env creado
  }

  new_env = (char **)ft_calloc(sizeof(char *), c + 1); // +1 para NULL
  if (!new_env)
    return (NULL);
  i = 0;
  while (environ[i]) {
    // CORRECCION MEMORIA: Duplicar strings
    new_env[i] = ft_strdup(environ[i]);
    if (!new_env[i]) {
      // Fallo de alloc, limpiar todo
      while (--i >= 0)
        free(new_env[i]);
      free(new_env);
      return (NULL);
    }
    i++;
  }
  new_env[i] = NULL;
  return (new_env);
}

// Crea un env sin la variable eliminada
char **create_new_env(t_data *shell, int skip_idx, int count) {
  char **new_env;
  int i;
  int j;

  new_env = (char **)ft_calloc(sizeof(char *),
                               count + 1); // count aqui sera el tamaño nuevo?
  // count original era total. size nuevo sera count - 1?
  // En unset_env_var, count es el tamaño actual.
  // Queremos reservar count (que es igual a size actual) porque uno sera NULL?
  // Si count cuenta los elementos (excluyendo NULL finales o incluyendo?),
  // unset_env_var cuenta: while(shell->env[count]) count++;
  // So count es num elementos. El nuevo array tendra count-1 elementos + 1
  // NULL. calloc(count) da espacio para count elementos. (ej 3 elementos ->
  // indices 0,1,2). Si borramos 1, quedan 2 elementos. Necesitamos indices 0,1
  // + NULL(index 2). Total 3 ptrs. calloc(count) es correcto si count >= 1.

  // Mejor explicitos: (count) * sizeof(char*)

  if (!new_env)
    return (NULL);
  i = 0;
  j = 0;
  while (shell->env[i]) {
    if (i != skip_idx) {
      new_env[j] = shell->env[i];
      j++;
    } else {
      // IMPORTANTE: Liberar la memoria de la variable eliminada para evitar
      // leak
      free(shell->env[i]);
    }
    i++;
  }
  new_env[j] = NULL;
  return (new_env);
}

// Elimina una env var
void unset_env_var(t_data *shell, char *var_name) {
  int idx;
  int count;
  char **new_env;
  size_t name_len;

  if (!shell->env)
    return;

  name_len = ft_strlen(var_name);
  idx = find_env_var(shell->env, var_name, name_len);
  if (idx < 0)
    return;
  count = 0;
  while (shell->env[count])
    count++;

  // Si es el unico elemento, quedara vacio?
  new_env = create_new_env(shell, idx, count);
  if (!new_env)
    return;
  free(shell->env); // Liberamos array de punteros viejo. Los contenidos se
                    // movieron o liberaron en create_new_env.
  shell->env = new_env;
}

// Sale de data
int exit_var(t_data *data) {
  int i;

  if (!data->env)
    return (0);
  i = 0;
  // CORRECCION MEMORIA: Liberar strings individuales
  while (data->env[i]) {
    free(data->env[i]);
    i++;
  }
  free(data->env);
  data->env = NULL;
  return (0);
}
