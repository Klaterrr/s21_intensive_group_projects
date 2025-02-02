#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"
#include "stack.h"

#define MAX_STR_LEN 100
#define WIDTH 80
#define HEIGHT 25

int precedence(const Token *ch) {
    if (!strcmp(ch->value, "+") || !strcmp(ch->value, "-")) {
        return 1;
    } else if (!strcmp(ch->value, "*") || !strcmp(ch->value, "/")) {
        return 2;
    } else if (ch->type == 0)
        return 3;
    return 0;
}

void infixToPostfix(Token *infix, Token *postfix[], const int len1, int *len2) {
    Stack *stack = stack_init();

    int j = 0;  // Счётчик для постфиксной записи выражения.
    for (int i = 0; i < len1; i++) {
        if (infix[i].type == 2 || infix[i].type == 1) {
            strcpy(postfix[j]->value, infix[i].value);
            postfix[j++]->type = infix[i].type;
        } else if (infix[i].type == 0) {
            stack_push(stack, &infix[i]);
        } else if (!strcmp(infix[i].value, "(")) {
            stack_push(stack, &infix[i]);
        } else if (!strcmp(infix[i].value, ")")) {
            while (!stack_is_empty(stack) && strcmp(stack->items[stack->top]->value, "(")) {
                postfix[j++] = stack_pop(stack);
            }
            stack_pop(stack);  // Удаляем открывающую скобку из стека
        } else {
            while (!stack_is_empty(stack) && precedence(&infix[i]) <= precedence(stack->items[stack->top])) {
                postfix[j++] = stack_pop(stack);
            }
            stack_push(stack, &infix[i]);
        }
    }

    while (!stack_is_empty(stack)) {
        Token *temp = stack_pop(stack);

        strcpy(postfix[j]->value, temp->value);
        postfix[j++]->type = temp->type;
    }
    *len2 = j;
    // printf("\n");
}

void Calculate(const Token *postfix, Stack *stack) {
    double result = 0;
    if (!strcmp(postfix->value, "sin")) {
        double num = atof(stack_pop(stack)->value);
        result = sin(num);
    } else if (!strcmp(postfix->value, "cos")) {
        double num = atof(stack_pop(stack)->value);
        result = cos(num);
    } else if (!strcmp(postfix->value, "tan")) {
        double num = atof(stack_pop(stack)->value);
        result = tan(num);
    } else if (!strcmp(postfix->value, "ctg")) {
        double num = atof(stack_pop(stack)->value);
        result = 1.0 / tan(num);
    } else if (!strcmp(postfix->value, "sqrt")) {
        double num = atof(stack_pop(stack)->value);
        result = sqrt(num);
    } else if (!strcmp(postfix->value, "ln")) {
        double num = atof(stack_pop(stack)->value);
        result = log(num);
    } else {
        Token *first = stack_pop(stack);
        Token *second = stack_pop(stack);

        double num2 = atof(first->value);
        double num1 = atof(second->value);

        if (!strcmp(postfix->value, "+"))
            result = num1 + num2;
        else if (!strcmp(postfix->value, "-"))
            result = num1 - num2;
        else if (!strcmp(postfix->value, "*"))
            result = num1 * num2;
        else if (!strcmp(postfix->value, "/"))
            result = num1 / num2;
    }
    char str_res[16];
    sprintf(str_res, "%lf", result);
    Token *tok_res = (Token *)malloc(sizeof(Token));
    tok_res->value = (char *)malloc(20 * sizeof(char *));
    strcpy(tok_res->value, str_res);
    tok_res->type = 2;

    stack_push(stack, tok_res);
    // printf("\n");
}

double evaluatePostfix(Token *postfix[], const int len) {
    Stack *stack = stack_init();

    for (int i = 0; i < len; i++) {
        if (postfix[i]->type == 2 || postfix[i]->type == 1) {
            stack_push(stack, postfix[i]);
        } else {
            Calculate(postfix[i], stack);
        }
    }
    double result = atof(stack_pop(stack)->value);
    // printf("\n");

    return result;
}

#define MAX_TOKEN_SIZE 100
#define MAX_TOKEN_COUNT 100

void find_functions(Token *tokens, int *num_tokens, const char *str, int *current_position, int len) {
    strncpy(tokens[*num_tokens].value, str + (*current_position), len);
    tokens[*num_tokens].value[len] = '\0';
    tokens[*num_tokens].type = 0;
    (*current_position) += len;
    (*num_tokens)++;
}

void find_operators(Token *tokens, int *num_tokens, const char *str, int *current_position) {
    tokens[*num_tokens].type = 3;
    tokens[*num_tokens].value[0] = str[*current_position];
    tokens[*num_tokens].value[1] = '\0';
    (*current_position)++;
    (*num_tokens)++;
}

void find_numbers(Token *tokens, int *num_tokens, const char *str, int *current_position) {
    int start_position = *current_position;
    if (str[*current_position] == '-') {
        (*current_position)++;
    }
    while ((str[*current_position] >= '0' && str[*current_position] <= '9') ||
           str[*current_position] == '.') {
        (*current_position)++;
        if (str[*current_position] == '\0') {
            break;
        }
    }
    int num_length = *current_position - start_position;
    tokens[*num_tokens].value = (char *)malloc((num_length + 1) * sizeof(char));
    if (tokens[*num_tokens].value == NULL) {
        printf("Memory allocation failed\n");
    } else {
        memcpy(tokens[*num_tokens].value, str + start_position, num_length);
        tokens[*num_tokens].value[num_length] = '\0';
        tokens[*num_tokens].type = 2;
        (*num_tokens)++;
    }
}

void find_variables(Token *tokens, int *num_tokens, char *variable, const char *str, int *current_position) {
    strcpy(tokens[*num_tokens].value, variable);
    tokens[*num_tokens].type = 1;
    (*current_position)++;
    (*num_tokens)++;
}

void print_formatted_expression(Token *token, int num_tokens) {
    for (int i = 0; i < num_tokens; i++) {
        printf("%s ", token[i].value);
    }
    printf("\n");
}

Token *tokenize(const char *str, int *num_tokens) {
    *num_tokens = 0;
    Token *tokens = (Token *)malloc(sizeof(Token) * MAX_TOKEN_COUNT);
    if (str != NULL) {
        int current_position = 0;
        int open_parentheses = 0;
        int status = 1;
        while (((str[current_position] != '\0') && (*num_tokens < MAX_TOKEN_COUNT))) {
            tokens[*num_tokens].value = (char *)malloc(sizeof(char) * MAX_TOKEN_SIZE);
            const char *functions[] = {"sin", "cos", "tan", "ctg", "sqrt", "ln"};
            const int function_lengths[] = {3, 3, 3, 3, 4, 2};
            int function_found = 0;
            for (int f = 0; f < sizeof(functions) / sizeof(functions[0]); f++) {
                if (strncmp(str + current_position, functions[f], function_lengths[f]) == 0) {
                    find_functions(tokens, num_tokens, str, &current_position, function_lengths[f]);
                    function_found = 1;
                    break;
                }
            }

            if (!function_found) {
                if (strchr("+-*/()", str[current_position]) != NULL) {
                    if (str[current_position] == '(') {
                        open_parentheses++;
                    } else if (str[current_position] == ')') {
                        if (open_parentheses == 0) {
                            printf("Invalid expression\n");
                            status = 0;
                        }
                        open_parentheses--;
                    }
                    if (str[current_position] == '-' &&
                        (current_position == 0 || strchr("+-*/(", str[current_position - 1]) != NULL)) {
                        find_numbers(tokens, num_tokens, str, &current_position);
                    } else {
                        find_operators(tokens, num_tokens, str, &current_position);
                    }
                } else if ((str[current_position] >= '0' && str[current_position] <= '9') ||
                           (str[current_position] == '.' && str[current_position - 1] >= '0' &&
                            str[current_position - 1] <= '9')) {
                    find_numbers(tokens, num_tokens, str, &current_position);
                } else if (str[current_position] == 'x') {
                    find_variables(tokens, num_tokens, "x", str, &current_position);
                } else {
                    current_position++;
                }
            }

            if (*num_tokens > 1) {
                Token *prev_token = &tokens[*num_tokens - 2];
                Token *curr_token = &tokens[*num_tokens - 1];
                if ((prev_token->type == 2 && curr_token->type == 1) ||
                    (prev_token->type == 1 && curr_token->type == 0) ||
                    (prev_token->type == 2 && curr_token->type == 0) ||
                    (prev_token->type == 1 && curr_token->type == 1) ||
                    (prev_token->type == 1 && curr_token->type == 2) ||
                    (prev_token->type == 2 && curr_token->value[0] == '(') ||
                    (prev_token->type == 1 && curr_token->value[0] == '(')) {
                    for (int i = *num_tokens; i > *num_tokens - 1; i--) {
                        tokens[i] = tokens[i - 1];
                    }
                    tokens[*num_tokens - 1].value = (char *)malloc(sizeof(char) * 2);
                    strcpy(tokens[*num_tokens - 1].value, "*");
                    tokens[*num_tokens - 1].type = 3;
                    (*num_tokens)++;
                }
            }
        }
        if (open_parentheses != 0) {
            printf("Error opening parenthesis");
            status = 0;
        } else {
            print_formatted_expression(tokens, *num_tokens);
        }
    } else {
        printf("Memory allocation fault\n");
    }
    // for (int i = 0; i < *num_tokens; i++) {
    //     free(tokens[i].value);
    // }
    // free(tokens);
    return tokens;
}

// Реализация функции округления
int my_round(double x) { return (int)(x < 0.0 ? x - 0.5 : x + 0.5); }

void plot_sine(double results[]) {
    char graph[HEIGHT][WIDTH];

    // Инициализация массива точками
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            graph[i][j] = '.';
        }
    }

    // Заполнение графика синусоидой
    for (int i = 0; i < WIDTH; ++i) {
        // double x = i * 4 * M_PI / (WIDTH - 1);  // Масштабирование по оси X
        double y = results[i];
        int y_pos = my_round(12 - y * 12);  // Масштабирование и округление по оси Y
        if (y_pos >= 0 && y_pos < HEIGHT) {
            graph[y_pos][i] = '*';
        }
    }

    // Вывод графика на экран
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            putchar(graph[i][j]);
        }
        putchar('\n');
    }
}

int main() {
    int len2 = 0;

    char str[MAX_TOKEN_SIZE] = "cos(x)";
    scanf("%s", str);
    int len1 = MAX_TOKEN_COUNT;

    Token *infix = (Token *)malloc(sizeof(Token) * MAX_TOKEN_COUNT);
    for (int i = 0; i < MAX_TOKEN_COUNT; i++) infix[i].value = (char *)malloc(sizeof(char) * MAX_TOKEN_SIZE);

    infix = tokenize(str, &len1);

    Token *postfix[MAX_STR_LEN];
    for (int i = 0; i < MAX_STR_LEN; i++) {
        postfix[i] = (Token *)malloc(sizeof(Token));
        postfix[i]->value = (char *)malloc(MAX_STR_LEN * sizeof(char));
    }
    infixToPostfix(infix, postfix, len1, &len2);
    // printf("Результат: %lf\n", evaluatePostfix(postfix, len2));
    double result[WIDTH] = {};
    for (int i = 0; i < WIDTH; ++i) {
        double x = i * 4 * M_PI / (WIDTH - 1);
        for (int j = 0; j < len2; j++) {
            if (postfix[j]->type == 1) {
                // printf("%s ", postfix[j]->value);
                sprintf(postfix[j]->value, "%lf", x);
                // postfix[j]->type = 2;
                // printf("%s ", postfix[j]->value);
                // for (int k = 0; k < len2; k++) {
                //     printf("%s ", postfix[k]->value);
                // }
                // printf("\n");

                // postfix[j]->type = 1;
            }
        }
        result[i] = evaluatePostfix(postfix, len2);
        printf("%lf\n", result[i]);
    }
    plot_sine(result);
    // printf("Результат: %lf\n", result);

    for (int i = 0; i < 3; i++) {
        free(infix[i].value);
    }
    free(infix);
    for (int i = 0; i < len2; i++) {
        free(postfix[i]->value);
        free(postfix[i]);
    }

    return 0;
}