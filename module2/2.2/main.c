#include "main.h"

// Инициализация кодировки консоли (CP1251)
void init_console_encoding() {
    SetConsoleCP(1251);         // Устанавливаем ввод в CP1251
    SetConsoleOutputCP(1251);   // Устанавливаем вывод в CP1251
    setlocale(LC_ALL, "Russian_Russia.1251");
}

// Вывод текста в CP1251
void print_cp1251(const char* str) {
    #ifdef _WIN32
    printf("%s", str);
    #else
    // Для Linux/Unix потребуется конвертация (но здесь ориентируемся на Windows)
    printf("%s", str);
    #endif
}

void free_tokens(char** tokens) {
    if (tokens) {
        for (int i = 0; i < MAX_TOKENS; i++) {
            free(tokens[i]);
        }
        free(tokens);
    }
}

char** parse_input(const char* input) {
    char** tokens = calloc(MAX_TOKENS, sizeof(char*));
    if (!tokens) return NULL;

    char* copy = _strdup(input);
    char* token = strtok(copy, " \t\n");
    
    for (int i = 0; i < MAX_TOKENS && token; i++) {
        tokens[i] = _strdup(token);
        token = strtok(NULL, " \t\n");
    }
    
    free(copy);
    return tokens;
}

int find_operation(const dict* operations, const char* op_symbol) {
    if (!op_symbol) return -1;
    
    for (int i = 0; operations[i].name; i++) {
        if (strcmp(operations[i].name, op_symbol) == 0) {
            return i;
        }
    }
    return -1;
}

void main_menu(void) {
    init_console_encoding();
    
    const dict operations[] = {
        {"+", sum},
        {"-", subtract},
        {NULL, NULL}
    };

    char input[INPUT_BUFFER_SIZE];
    print_cp1251("Введите выражение (например: 5 + 3): ");
    
    if (!fgets(input, sizeof(input), stdin)) {
        print_cp1251("Ошибка чтения ввода\n");
        return;
    }

    char** tokens = parse_input(input);
    if (!tokens || !tokens[0] || !tokens[1] || !tokens[2]) {
        print_cp1251("Неверный формат ввода. Используйте: число оператор число\n");
        free_tokens(tokens);
        return;
    }

    long num1 = strtol(tokens[0], NULL, 10);
    long num2 = strtol(tokens[2], NULL, 10);
    int op_index = find_operation(operations, tokens[1]);

    if (op_index == -1) {
        printf("Неизвестная операция: %s\n", tokens[1]);
    } else {
        int result = operations[op_index].operation(num1, num2);
        printf("Результат: %d\n", result);
    }

    free_tokens(tokens);
}

int main(void) {
    main_menu();
    return 0;
}