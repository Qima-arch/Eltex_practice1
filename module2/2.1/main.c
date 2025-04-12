#include "main.h"

// ��������� ������� ��������� �������
void setRussianEncoding() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
}

// ������� ������ �����
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// ��������� �������������� ����� � ���������
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
        
        printf("������: ��������� ������ ����� �����. ���������� �����.\n");
    }
}

// ��������� ���������� ����� � ���������
int get_string_input(const char *prompt, char *buffer, int max_length) {
    printf("%s", prompt);
    if (fgets(buffer, max_length, stdin) == NULL) {
        return 0;
    }
    
    // ������� ������ ����� ������
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
        printf("������ ��������� ������\n");
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
        printf("���������� ����� �����\n");
        return;
    }
    
    Node *prev = find_prev_person(*head, primary_key);
    if (prev == NULL || prev->next == NULL) {
        printf("������� � �������� %d �� ������\n", primary_key);
        return;
    }
    
    Node *to_delete = prev->next;
    prev->next = to_delete->next;
    free(to_delete);
    printf("������� ������� ������\n");
}

void pop(Node **head) {
    if (*head == NULL) {
        printf("���������� ����� �����\n");
        return;
    }
    
    Node *temp = *head;
    *head = (*head)->next;
    free(temp);
    printf("������ ������� ������� ������\n");
}

void printList(Node *head) {
    if (head == NULL || (head->primary_key == 0 && head->next == NULL)) {
        printf("\n���������� ����� �����\n");
        return;
    }
    
    printf("\n=== ���������� ���������� ����� ===\n");
    Node *ptr = head;
    while (ptr != NULL) {
        if (ptr->primary_key != 0) {
            printf("\n������: %d\n", ptr->primary_key);
            printf("���: %s\n", ptr->firstname);
            printf("�������: %s\n", ptr->secondname);
            printf("��������: %s\n", ptr->otchestvo);
            printf("�������: %s\n", ptr->age);
            printf("�������: %s\n", ptr->phone_number);
            printf("����� ������: %s\n", ptr->work_place);
            printf("���������: %s\n", ptr->work_post);
            printf("�������: %s\n", ptr->media);
            printf("----------------------------");
        }
        ptr = ptr->next;
    }
    printf("\n==================================\n");
}

void delete_person_choice(Node **head) {
    int selected_primary_key;
    if (!get_int_input("\n������� ������ �������� ��� �������� (0 - ������): ", &selected_primary_key)) {
        printf("������ �����\n");
        return;
    }
    
    if (selected_primary_key == 0) {
        printf("�������� ��������\n");
        return;
    }
    
    if (*head == NULL) {
        printf("���������� ����� �����\n");
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
    
    printf("\n=== ���������� ������ �������� ===\n");
    
    get_string_input("������� ���: ", new_firstname, 20);
    get_string_input("������� �������: ", new_secondname, 20);
    get_string_input("������� ��������: ", new_otchestvo, 20);
    get_string_input("������� �������: ", new_age, 5);
    get_string_input("������� ����� ��������: ", new_phone_number, 12);
    get_string_input("������� ����� ������: ", new_work_place, 20);
    get_string_input("������� ���������: ", new_work_post, 20);
    get_string_input("������� �������: ", new_media, 50);
    
    push(head, new_firstname, new_secondname, new_otchestvo, new_age,
         new_phone_number, new_work_place, new_work_post, new_media);
    
    printf("\n������� ������� ��������!\n");
}

void change_person(Node **head) {
    int index_person;
    if (!get_int_input("\n������� ������ �������� ��� ��������� (0 - ������): ", &index_person)) {
        printf("������ �����\n");
        return;
    }
    
    if (index_person == 0) {
        printf("��������� ��������\n");
        return;
    }
    
    Node *ptr = find_person(*head, index_person);
    if (ptr == NULL) {
        printf("������� � �������� %d �� ������\n", index_person);
        return;
    }
    
    int choice;
    do {
        printf("\n�������������� �������� %d:\n", index_person);
        printf("1. ��� (%s)\n", ptr->firstname);
        printf("2. ������� (%s)\n", ptr->secondname);
        printf("3. �������� (%s)\n", ptr->otchestvo);
        printf("4. ������� (%s)\n", ptr->age);
        printf("5. ������� (%s)\n", ptr->phone_number);
        printf("6. ����� ������ (%s)\n", ptr->work_place);
        printf("7. ��������� (%s)\n", ptr->work_post);
        printf("8. ������� (%s)\n", ptr->media);
        printf("0. ��������� ��������������\n");
        
        if (!get_int_input("�������� ���� ��� ���������: ", &choice)) {
            printf("������ �����\n");
            continue;
        }
        
        switch (choice) {
            case 1: get_string_input("����� ���: ", ptr->firstname, 20); break;
            case 2: get_string_input("����� �������: ", ptr->secondname, 20); break;
            case 3: get_string_input("����� ��������: ", ptr->otchestvo, 20); break;
            case 4: get_string_input("����� �������: ", ptr->age, 5); break;
            case 5: get_string_input("����� �������: ", ptr->phone_number, 12); break;
            case 6: get_string_input("����� ����� ������: ", ptr->work_place, 20); break;
            case 7: get_string_input("����� ���������: ", ptr->work_post, 20); break;
            case 8: get_string_input("����� �������: ", ptr->media, 50); break;
            case 0: break;
            default: printf("�������� �����. ���������� �����.\n"); break;
        }
    } while (choice != 0);
    
    printf("��������� ���������\n");
}

void menu(Node **head) {
    int choice;
    while (1) {
        printf("\n=== ���������� ����� ===\n");
        printf("1. �������� �������\n");
        printf("2. ������� �������\n");
        printf("3. ����������� ��� ��������\n");
        printf("4. �������� �������\n");
        printf("0. �����\n");
        
        if (!get_int_input("�������� ��������: ", &choice)) {
            printf("������ �����\n");
            continue;
        }
        
        switch (choice) {
            case 1: add_person_choice(head); break;
            case 2: delete_person_choice(head); break;
            case 3: printList(*head); break;
            case 4: change_person(head); break;
            case 0: exit(0);
            default: printf("�������� �����. ����������, ������� ����� �� 0 �� 4.\n"); break;
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
        printf("������ ��������� ������\n");
        return 1;
    }
    
    struct_init(phone_book_head);
    menu(&phone_book_head);
    
    return 0;
}