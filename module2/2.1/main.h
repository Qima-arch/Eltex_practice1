#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>

typedef struct Node
{
    int primary_key;
    char firstname[20];
    char secondname[20];
    char otchestvo[20];
    char age[5];
    char phone_number[12];
    char work_place[20];
    char work_post[20];
    char media[50];
    struct Node *next;
} Node;

// Основные функции телефонной книги
void push(Node **head, char new_firstname[20], char new_secondname[20],
          char new_otchestvo[20], char new_age[5], char new_phone_number[12],
          char new_work_place[20], char new_work_post[20], char new_media[50]);
void printList(Node *head);
void add_person_choice(Node **head);
void pop(Node **head);
void delete_person_choice(Node **head);
Node *find_person(Node *head, int primary_key);
Node *find_prev_person(Node *head, int primary_key);
void delete_from_structure(Node **head, int primary_key);
void change_person(Node **head);
void menu(Node **head);
void struct_init(Node *head);

// Функции для работы с вводом
int get_int_input(const char *prompt, int *value);
int get_string_input(const char *prompt, char *buffer, int max_length);
void clear_input_buffer();

#endif  // SRC_MAIN_H_