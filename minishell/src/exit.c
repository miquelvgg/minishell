#include "minishell.h"



void ft_exit(void)
{
    unblock_signal(SIGINT);
    unblock_signal(SIGQUIT);
    return;
}