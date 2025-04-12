#include "main.h"

// Установка русской кодировки консоли
void setRussianEncoding() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
}

// Очистка буфера ввода
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Получение целочисленного ввода с проверкой
int get_int_input(const char *prompt, int *value) {
    char input[100];
    while (1) {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            clear_input_buffer();
            return 0;
        }
        
        if (sscanf(input, "%d", value) == 1) {
            return 1;
        }
        
        printf("Ошибка: требуется ввести целое число. Попробуйте снова.\n");
    }
}

// Получение строкового ввода с проверкой
int get_string_input(const char *prompt, char *buffer, int max_length) {
    printf("%s", prompt);
    if (fgets(buffer, max_length, stdin) == NULL) {
        return 0;
    }
    
    // Удаляем символ новой строки
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    } else {
        clear_input_buffer();
    }
    return 1;
}

void push(Node **head, char new_firstname[20], char new_secondname[20],
          char new_otchestvo[20], char new_age[5], char new_phone_number[12],
          char new_work_place[20], char new_work_post[20], char new_media[50]) {
    Node *tmp = (Node *)malloc(sizeof(Node));
    if (tmp == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    
    strncpy(tmp->firstname, new_firstname, 20);
    strncpy(tmp->secondname, new_secondname, 20);
    strncpy(tmp->otchestvo, new_otchestvo, 20);
    strncpy(tmp->phone_number, new_phone_number, 12);
    strncpy(tmp->work_place, new_work_place, 20);
    strncpy(tmp->work_post, new_work_post, 20);
    strncpy(tmp->media, new_media, 50);
    strncpy(tmp->age, new_age, 5);
    
    tmp->next = (*head);
    tmp->primary_key = (*head == NULL) ? 1 : (*head)->primary_key + 1;
    (*head) = tmp;
}

Node *find_person(Node *head, int primary_key) {
    Node *ptr = head;
    while (ptr != NULL) {
        if (ptr->primary_key == primary_key) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

Node *find_prev_person(Node *head, int primary_key) {
    if (head == NULL || head->primary_key == primary_key) {
        return NULL;
    }
    
    Node *prev = head;
    while (prev->next != NULL) {
        if (prev->next->primary_key == primary_key) {
            return prev;
        }
        prev = prev->next;
    }
    return NULL;
}

void delete_from_structure(Node **head, int primary_key) {
    if (*head == NULL) {
        printf("Телефонная книга пуста\n");
        return;
    }
    
    Node *prev = find_prev_person(*head, primary_key);
    if (prev == NULL || prev->next == NULL) {
        printf("Контакт с индексом %d не найден\n", primary_key);
        return;
    }
    
    Node *to_delete = prev->next;
    prev->next = to_delete->next;
    free(to_delete);
    printf("Контакт успешно удален\n");
}

void pop(Node **head) {
    if (*head == NULL) {
        printf("Телефонная книга пуста\n");
        return;
    }
    
    Node *temp = *head;
    *head = (*head)->next;
    free(temp);
    printf("Первый контакт успешно удален\n");
}

void printList(Node *head) {
    if (head == NULL || (head->primary_key == 0 && head->next == NULL)) {
        printf("\nТелефонная книга пуста\n");
        return;
    }
    
    printf("\n=== Содержимое телефонной книги ===\n");
    Node *ptr = head;
    while (ptr != NULL) {
        if (ptr->primary_key != 0) {
            printf("\nИндекс: %d\n", ptr->primary_key);
            printf("Имя: %s\n", ptr->firstname);
            printf("Фамилия: %s\n", ptr->secondname);
            printf("Отчество: %s\n", ptr->otchestvo);
            printf("Возраст: %s\n", ptr->age);
            printf("Телефон: %s\n", ptr->phone_number);
            printf("Место работы: %s\n", ptr->work_place);
            printf("Должность: %s\n", ptr->work_post);
            printf("Соцсети: %s\n", ptr->media);
            printf("----------------------------");
        }
        ptr = ptr->next;
    }
    printf("\n==================================\n");
}

void delete_person_choice(Node **head) {
    int selected_primary_key;
    if (!get_int_input("\nВведите индекс контакта для удаления (0 - отмена): ", &selected_primary_key)) {
        printf("Ошибка ввода\n");
        return;
    }
    
    if (selected_primary_key == 0) {
        printf("Удаление отменено\n");
        return;
    }
    
    if (*head == NULL) {
        printf("Телефонная книга пуста\n");
        return;
    }
    
    if ((*head)->primary_key == selected_primary_key) {
        pop(head);
        return;
    }
    
    delete_from_structure(head, selected_primary_key);
}

void add_person_choice(Node **head) {
    char new_firstname[20] = {0};
    char new_secondname[20] = {0};
    char new_otchestvo[20] = {0};
    char new_age[5] = {0};
    char new_phone_number[12] = {0};
    char new_work_place[20] = {0};
    char new_work_post[20] = {0};
    char new_media[50] = {0};
    
    printf("\n=== Добавление нового контакта ===\n");
    
    get_string_input("Введите имя: ", new_firstname, 20);
    get_string_input("Введите фамилию: ", new_secondname, 20);
    get_string_input("Введите отчество: ", new_otchestvo, 20);
    get_string_input("Введите возраст: ", new_age, 5);
    get_string_input("Введите номер телефона: ", new_phone_number, 12);
    get_string_input("Введите место работы: ", new_work_place, 20);
    get_string_input("Введите должность: ", new_work_post, 20);
    get_string_input("Введите соцсети: ", new_media, 50);
    
    push(head, new_firstname, new_secondname, new_otchestvo, new_age,
         new_phone_number, new_work_place, new_work_post, new_media);
    
    printf("\nКонтакт успешно добавлен!\n");
}

void change_person(Node **head) {
    int index_person;
    if (!get_int_input("\nВведите индекс контакта для изменения (0 - отмена): ", &index_person)) {
        printf("Ошибка ввода\n");
        return;
    }
    
    if (index_person == 0) {
        printf("Изменение отменено\n");
        return;
    }
    
    Node *ptr = find_person(*head, index_person);
    if (ptr == NULL) {
        printf("Контакт с индексом %d не найден\n", index_person);
        return;
    }
    
    int choice;
    do {
        printf("\nРедактирование контакта %d:\n", index_person);
        printf("1. Имя (%s)\n", ptr->firstname);
        printf("2. Фамилия (%s)\n", ptr->secondname);
        printf("3. Отчество (%s)\n", ptr->otchestvo);
        printf("4. Возраст (%s)\n", ptr->age);
        printf("5. Телефон (%s)\n", ptr->phone_number);
        printf("6. Место работы (%s)\n", ptr->work_place);
        printf("7. Должность (%s)\n", ptr->work_post);
        printf("8. Соцсети (%s)\n", ptr->media);
        printf("0. Завершить редактирование\n");
        
        if (!get_int_input("Выберите поле для изменения: ", &choice)) {
            printf("Ошибка ввода\n");
            continue;
        }
        
        switch (choice) {
            case 1: get_string_input("Новое имя: ", ptr->firstname, 20); break;
            case 2: get_string_input("Новая фамилия: ", ptr->secondname, 20); break;
            case 3: get_string_input("Новое отчество: ", ptr->otchestvo, 20); break;
            case 4: get_string_input("Новый возраст: ", ptr->age, 5); break;
            case 5: get_string_input("Новый телефон: ", ptr->phone_number, 12); break;
            case 6: get_string_input("Новое место работы: ", ptr->work_place, 20); break;
            case 7: get_string_input("Новая должность: ", ptr->work_post, 20); break;
            case 8: get_string_input("Новые соцсети: ", ptr->media, 50); break;
            case 0: break;
            default: printf("Неверный выбор. Попробуйте снова.\n"); break;
        }
    } while (choice != 0);
    
    printf("Изменения сохранены\n");
}

void menu(Node **head) {
    int choice;
    while (1) {
        printf("\n=== Телефонная книга ===\n");
        printf("1. Добавить контакт\n");
        printf("2. Удалить контакт\n");
        printf("3. Просмотреть все контакты\n");
        printf("4. Изменить контакт\n");
        printf("0. Выход\n");
        
        if (!get_int_input("Выберите действие: ", &choice)) {
            printf("Ошибка ввода\n");
            continue;
        }
        
        switch (choice) {
            case 1: add_person_choice(head); break;
            case 2: delete_person_choice(head); break;
            case 3: printList(*head); break;
            case 4: change_person(head); break;
            case 0: exit(0);
            default: printf("Неверный выбор. Пожалуйста, введите число от 0 до 4.\n"); break;
        }
    }
}

void struct_init(Node *head) {
    if (head == NULL) return;
    
    head->primary_key = 0;
    strncpy(head->firstname, "", 1);
    strncpy(head->secondname, "", 1);
    strncpy(head->otchestvo, "", 1);
    strncpy(head->age, "", 1);
    strncpy(head->phone_number, "", 1);
    strncpy(head->work_place, "", 1);
    strncpy(head->work_post, "", 1);
    strncpy(head->media, "", 1);
    head->next = NULL;
}

int main() {
    setRussianEncoding();
    
    Node *phone_book_head = (Node *)calloc(1, sizeof(Node));
    if (phone_book_head == NULL) {
        printf("Ошибка выделения памяти\n");
        return 1;
    }
    
    struct_init(phone_book_head);
    menu(&phone_book_head);
    
    return 0;
}