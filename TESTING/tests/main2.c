#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Define tokens
#define TOKEN_PLUS '+'
#define TOKEN_MINUS '-'
#define TOKEN_MULTIPLY '*'
#define TOKEN_DIVIDE '/'
#define TOKEN_LPAREN '('
#define TOKEN_RPAREN ')'
#define TOKEN_INT '0'

// Define token structure
typedef struct {
    int type;
    int value;
} token_t;

// Define lexer function
void lexer(char* input, token_t* tokens) {
    int i = 0;
    int j = 0;
    while (input[i] != '\0') {
        if (isdigit(input[i])) {
            tokens[j].type = TOKEN_INT;
            tokens[j].value = input[i] - '0';
            j++;
        } else if (input[i] == TOKEN_PLUS) {
            tokens[j].type = TOKEN_PLUS;
            j++;
        } else if (input[i] == TOKEN_MINUS) {
            tokens[j].type = TOKEN_MINUS;
            j++;
        } else if (input[i] == TOKEN_MULTIPLY) {
            tokens[j].type = TOKEN_MULTIPLY;
            j++;
        } else if (input[i] == TOKEN_DIVIDE) {
            tokens[j].type = TOKEN_DIVIDE;
            j++;
        } else if (input[i] == TOKEN_LPAREN) {
            tokens[j].type = TOKEN_LPAREN;
            j++;
        } else if (input[i] == TOKEN_RPAREN) {
            tokens[j].type = TOKEN_RPAREN;
            j++;
        }
        i++;
    }
    tokens[j].type = '\0';
}

// Define parser function
int parse_expression(token_t* tokens, int* index);
int parse_factor(token_t* tokens, int* index);

int parse_term(token_t* tokens, int* index) {
    int left = parse_factor(tokens, index);
    while (tokens[*index].type == TOKEN_MULTIPLY || tokens[*index].type == TOKEN_DIVIDE) {
        int op = tokens[*index].type;
        (*index)++;
        int right = parse_factor(tokens, index);
        if (op == TOKEN_MULTIPLY) {
            left *= right;
        } else {
            left /= right;
        }
    }
    return left;
}

int parse_factor(token_t* tokens, int* index) {
    int value;
    if (tokens[*index].type == TOKEN_INT) {
        value = tokens[*index].value;
        (*index)++;
    } else if (tokens[*index].type == TOKEN_LPAREN) {
        (*index)++;
        value = parse_expression(tokens, index);
        (*index)++;
    }
    return value;
}

int parse_expression(token_t* tokens, int* index) {
    int left = parse_term(tokens, index);
    while (tokens[*index].type == TOKEN_PLUS || tokens[*index].type == TOKEN_MINUS) {
        int op = tokens[*index].type;
        (*index)++;
        int right = parse_term(tokens, index);
        if (op == TOKEN_PLUS) {
            left += right;
        } else {
            left -= right;
        }
    }
    return left;
}

// Define execute function
int execute(char* input) {
    token_t tokens[100];
    lexer(input, tokens);
    int index = 0;
    int result = parse_expression(tokens, &index);
    return result;
}

// Define main function
int main() {
    char input[100];
    printf("Enter an expression: ");
    fgets(input, 100, stdin);
    int result = execute(input);
    printf("Result: %d\n", result);
}