#include "main.h"

// ������������� ��������� ������� (CP1251)
void init_console_encoding() {
    SetConsoleCP(1251);         // ������������� ���� � CP1251
    SetConsoleOutputCP(1251);   // ������������� ����� � CP1251
    setlocale(LC_ALL, "Russian_Russia.1251");
}

// ����� ������ � CP1251
void print_cp1251(const char* str) {
    #ifdef _WIN32
    printf("%s", str);
    #else
    // ��� Linux/Unix ����������� ����������� (�� ����� ������������� �� Windows)
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
    print_cp1251("������� ��������� (��������: 5 + 3): ");
    
    if (!fgets(input, sizeof(input), stdin)) {
        print_cp1251("������ ������ �����\n");
        return;
    }

    char** tokens = parse_input(input);
    if (!tokens || !tokens[0] || !tokens[1] || !tokens[2]) {
        print_cp1251("�������� ������ �����. �����������: ����� �������� �����\n");
        free_tokens(tokens);
        return;
    }

    long num1 = strtol(tokens[0], NULL, 10);
    long num2 = strtol(tokens[2], NULL, 10);
    int op_index = find_operation(operations, tokens[1]);

    if (op_index == -1) {
        printf("����������� ��������: %s\n", tokens[1]);
    } else {
        int result = operations[op_index].operation(num1, num2);
        printf("���������: %d\n", result);
    }

    free_tokens(tokens);
}

int main(void) {
    main_menu();
    return 0;
}