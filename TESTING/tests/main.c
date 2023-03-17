#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/history.h>
#include <readline/readline.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100

typedef enum {
    TK_IDENTIFIER,
    TK_KEYWORD,
    TK_OPERATOR,
    TK_CONSTANT,
    TK_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;

const char *keywords[] = {
    "int", "char", "float", "double", "void", "if", "else", "for", "while", "do", "switch", "case", "break", "default", "return"
};

const char *operators[] = {
    "+", "-", "*", "/", "=","%", "==", "!=", ">=", "<=", ">", "<", "&&", "||"
};

int is_keyword(const char *value) {
    int i;
    for (i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(keywords[i], value) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_operator(const char *value) {
    int i;
    for (i = 0; i < sizeof(operators) / sizeof(operators[0]); i++) {
        if (strcmp(operators[i], value) == 0) {
            return 1;
        }
    }
    return 0;
}

Token get_next_token(FILE *file) {
    Token token;
    char c, value[MAX_TOKEN_LENGTH];
    int i = 0;

    // Skip whitespace
    while ((c = fgetc(file)) != EOF && isspace(c));

    if (c == EOF) {
        token.type = TK_UNKNOWN;
        token.value[0] = '\0';
        return token;
    }

    value[i++] = c;

    if (isalpha(c) || c == '_') {
        while ((c = fgetc(file)) != EOF && (isalnum(c) || c == '_')) {
            value[i++] = c;
        }
        value[i] = '\0';
        ungetc(c, file);
        if (is_keyword(value)) {
            token.type = TK_KEYWORD;
        } else {
            token.type = TK_IDENTIFIER;
        }
    } else if (isdigit(c)) {
        while ((c = fgetc(file)) != EOF && isdigit(c)) {
            value[i++] = c;
        }
        if (c == '.') {
            value[i++] = c;
            while ((c = fgetc(file)) != EOF && isdigit(c)) {
                value[i++] = c;
            }
        }
        value[i] = '\0';
        ungetc(c, file);
        token.type = TK_CONSTANT;
    } else {
        while ((c = fgetc(file)) != EOF && !isspace(c) && !isdigit(c) && !isalpha(c)) {
            value[i++] = c;
        }
        value[i] = '\0';
        ungetc(c, file);
        if (is_operator(value)) {
            token.type = TK_OPERATOR;
        } else {
            token.type = TK_UNKNOWN;
        }
    }

    strcpy(token.value, value);

    return token;
}


void lex(FILE *fp) {
    int c;
    char buffer[1024];
    int buffer_pos = 0;

    while ((c = fgetc(fp)) != EOF) {
        // Ignore whitespace
        if (isspace(c)) {
            continue;
        }
        // Check if the character is a letter
        else if (isalpha(c)) {
            // Add the character to the buffer
            buffer[buffer_pos++] = c;
            // Read more letters into the buffer
            while ((c = fgetc(fp)) != EOF && isalnum(c)) {
                buffer[buffer_pos++] = c;
            }
            // Null-terminate the buffer
            buffer[buffer_pos] = '\0';
            // Check if the lexeme is a keyword
            if (is_keyword(buffer)) {
                printf("keyword: %s\n", buffer);
            } else {
                printf("identifier: %s\n", buffer);
            }
            // Reset the buffer position
            buffer_pos = 0;
            // Put back the last character read (which was not a letter)
            ungetc(c, fp);
        }
        // Check if the character is a digit
        else if (isdigit(c)) {
            // Add the character to the buffer
            buffer[buffer_pos++] = c;
            // Read more digits into the buffer
            while ((c = fgetc(fp)) != EOF && isdigit(c)) {
                buffer[buffer_pos++] = c;
            }
            // Null-terminate the buffer
            buffer[buffer_pos] = '\0';
            printf("number: %s\n", buffer);
            // Reset the buffer position
            buffer_pos = 0;
            // Put back the last character read (which was not a digit)
            ungetc(c, fp);
        }
        // Check if the character is a special symbol
        else {
            // Add the character to the buffer
            buffer[buffer_pos++] = c;
            // Read more special symbols into the buffer
            while ((c = fgetc(fp)) != EOF && is_operator((char *)&c)) {
                buffer[buffer_pos++] = c;
            }
            // Null-terminate the buffer
            buffer[buffer_pos] = '\0';
            if (is_operator(buffer))
                printf("operator: %s\n", buffer);
            else
                printf("Unknown: %s\n", buffer);
            // Reset the buffer position
            buffer_pos = 0;
            // Put back the last character read (which was not a special symbol)
            ungetc(c, fp);
        }
    }
}
int main(int argc, char **argv) {
    FILE *file;
    Token token;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("fopen");
        return 1;
   
    }
    lex(file);
}