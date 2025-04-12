#include "main.h"

int sum(int a, int b) {
    if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b)) {
        print_cp1251("Ошибка: переполнение при сложении\n");
        return 0;
    }
    return a + b;
}

int subtract(int a, int b) {
    if ((b < 0 && a > INT_MAX + b) || (b > 0 && a < INT_MIN + b)) {
        print_cp1251("Ошибка: переполнение при вычитании\n");
        return 0;
    }
    return a - b;
}