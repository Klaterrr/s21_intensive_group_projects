#ifndef LIB_H
#define LIB_H

// TODO: Add function prototypes and data structures here
int tokenizator(char *str);
int lexical_analyzer(char *str);

typedef struct {
    char *value;
    int type;
    /* types:   0 - functions, 1 - variables, 2 - numbers,
                3 - operators, 4 - separ*/
} Token;

Token *tokenize(const char *, int *num_tokens);
void print_formatted_expression(Token *tokens, int num_tokens);

#endif