#include "mini_shell.h"

void    s_free(void *value)
{
    free(value);
}

void    free_token(void *value)
{
    t_token *token;

    token = value;
    if (token->type == IN_REDIRECT || token->type == OUT_REDIRECT
        || token->type == HERE_DOC || token->type == APPEND_REDIRECT)
    {
        free(((t_file *)token->value)->a_file);
        free(token->value);
    }else if (token->type == COMMAND)
    {
        ft_lstclear(&((t_cmd *)token->value)->arg, s_free);
        free(((t_cmd *)token->value)->cmd);
        free(token->value);
    }
    free(token);
}

void    free_tokens(t_list **list)
{
    ft_lstclear(list, free_token);
}