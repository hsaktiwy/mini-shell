#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum
{
    OP_MINUS = '-',
    OP_PLUS = '+',
    OP_MULTIPLICATION = 'x',
    OP_DEVISION = '/',
    OP_MODULO = '%',
    OP_NUMBER = '0',
    OP_OPEN_PARENTIZE = '(',
    OP_CLOSE_PARENTIZE = ')'
}Token_type;

typedef struct ta_token{
    Token_type type;
    int value;
}token;

int   lex(token *t_token, char *input){
    int i;
    int j;

    i = 0;
    j = 0;
    while(input[i])
    {
        while(input[i] && input[i] == ' ')
            i++;
        if(input[i] && isdigit(input[i]))
        {
            int value = 0 + input[i++] - '0';
            while (isdigit(input[i]))
                value = value * 10 + input[i++] - '0';
            t_token[j].value = value;
            t_token[j].type = OP_NUMBER;
            j++;
        }else if (input[i] == OP_MINUS){
            t_token[j].type = OP_MINUS;
            j++;
        }else if (input[i] == OP_PLUS){
            t_token[j].type = OP_PLUS;
            j++;
        }else if (input[i] == OP_MULTIPLICATION){
            t_token[j].type = OP_MULTIPLICATION;
            j++;
        }else if (input[i] == OP_DEVISION){
            t_token[j].type = OP_DEVISION;
            j++;
        }else if (input[i] == OP_MODULO){
            t_token[j].type = OP_MODULO;
            j++;
        }else if (input[i] == OP_OPEN_PARENTIZE){
            t_token[j].type = OP_OPEN_PARENTIZE;
            j++;
        }else if (input[i] == OP_CLOSE_PARENTIZE){
            t_token[j].type = OP_CLOSE_PARENTIZE;
            j++;
        }else{
            printf("invalide argument\n");
            return (0);
        }
        if (input[i])
            i++;
    }
    t_token[j].type = '\0';
    return (1);
}
// definition
int parse_expression(token *t_token, int *index);
// pars_fact
int parse_fact(token *t_token, int *index)
{
    int value;

    // printf("F_INDEX=%d\n",*index);
    if (t_token[*index].type == OP_NUMBER)
    {
        value = t_token[*index].value;
        (*index)++;
        // printf("F_1_INDEX=%d\n",*index);
    }else if (t_token[*index].type == OP_OPEN_PARENTIZE)
    {
        (*index)++;
        value = parse_expression(t_token, index);
        (*index)++;
        // printf("F_2_INDEX=%d\n",*index);
    }
    // printf("F_INDEX=%d\n",*index);
    return (value);
}
// term
int parse_term(token *t_token, int *index)
{
    // printf("T_INDEX=%d\n",*index);
    int left = parse_fact(t_token, index);

    // printf("T_INDEX=%d\n",*index);
    while (t_token[*index].type == OP_DEVISION || t_token[*index].type == OP_MODULO ||  t_token[*index].type == OP_MULTIPLICATION)
    {
        int op = t_token[*index].type;
        (*index)++;
        int right = parse_fact(t_token, index);
        if (op == OP_DEVISION)
            left /= right;
        else if (op == OP_MULTIPLICATION)
            left *= right;
        else
            left %= right;
    }
    return (left);
}
// expresion
int parse_expression(token *t_token, int *index)
{
    // printf("E_INDEX=%d\n",*index);
    int left = parse_term(t_token, index);

    // printf("E_INDEX=%d\n",*index);
    while(t_token[*index].type == OP_PLUS || t_token[*index].type == OP_MINUS)
    {
        int op = t_token[*index].type;
        (*index)++;
        int right = parse_term(t_token, index);
        if(op == OP_PLUS)
            left += right;
        else 
            left -= right;
    }
    return (left);
}

void display(token *token)
{
    int i;
    i = 0;
    while (token[i].type)
    {
        printf("token.type : %c\n",token[i].type);
        printf("token.value : %d\n",token[i].value);
        i++;
    }
}

void    executer(char *input)
{
    token t_token[100];
    int index;

    if (lex(t_token, input))
    {
        display(t_token);
        index = 0;
        printf("%d\n", parse_expression(t_token, &index));
    } 
}

int main()
{
    char *input;

    while(1)
    {
        input = readline("Gave me Exp: ");
        if (input)
            executer(input);
        add_history(input);
    }
}