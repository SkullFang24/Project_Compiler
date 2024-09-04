//Annas Ahmad 
//231-520655
//COMP-451-A
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    IDENTIFIER,
    OPERATOR,
    SEMICOLON,
    ERROR
} TokenType;

typedef struct {
    TokenType type;
    char value[6]; 
} Token;

int isValidIdentifierChar(char ch) {
    return isalnum(ch) || ch == '_';
}

void preprocess(char *input, char *output) {
    int i = 0, j = 0;

    while (input[i] != '\0') {
        if (!isspace(input[i])) {
            if (input[i] == ';') {
                output[j++] = '$';
            } else {
                output[j++] = input[i];
            }
        }
        i++;
    }

    output[j] = '\0';
}

void tokenize(char *input) {
    Token token;
    int i = 0;

    while (input[i] != '\0') {
        if (isalpha(input[i]) && isValidIdentifierChar(input[i])) {
            int j = 0;
            while (isValidIdentifierChar(input[i]) && j < 5) {
                token.value[j] = input[i];
                i++;
                j++;
            }
            token.value[j] = '\0';
            token.type = IDENTIFIER;
        }

        else if (strchr("+-*/", input[i]) != NULL) {
            token.type = OPERATOR;
            token.value[0] = input[i];
            token.value[1] = '\0';
            i++;
        }

        else if (input[i] == '$') {
            token.type = SEMICOLON;
            token.value[0] = '$';
            token.value[1] = '\0';
            i++;
        }

        else {
            token.type = ERROR;
            token.value[0] = input[i];
            token.value[1] = '\0';
            i++;
        }

        printf("Token: Type=%d, Value=%s\n", token.type, token.value);
    }
}

int main() {
    char input[100];
    char preprocessed[100];

    printf("Enter the arithmetic expression: ");
    fgets(input, sizeof(input), stdin);

    preprocess(input, preprocessed);

    tokenize(preprocessed);

    return 0;
}
