#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>
#include <windows.h>

#define INPUT_BUFFER_SIZE 256
#define MAX_TOKENS 3

typedef struct dict {
    const char* name;
    int (*operation)(int, int);
} dict;

// Функции для работы с консолью
void init_console_encoding();
void print_cp1251(const char* str);

// Математические операции
int sum(int a, int b);
int subtract(int a, int b);

// Логика калькулятора
void main_menu(void);
char** parse_input(const char* input);
int find_operation(const dict* operations, const char* op_symbol);
void free_tokens(char** tokens);

#endif // MAIN_H