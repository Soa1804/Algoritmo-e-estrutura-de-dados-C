#include <stdio.h>

// DoublyLinkedList.h
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdbool.h>

// Nó genérico da lista
typedef struct Node {
    void* data;
    struct Node* prev;
    struct Node* next;
} Node;

// Lista duplamente encadeada
typedef struct DoublyLinkedList {
    Node* head;
    Node* tail;
    int size;
} DoublyLinkedList;

DoublyLinkedList* createList();
void insertAtBeginning(DoublyLinkedList* list, void* data);
void insertAtEnd(DoublyLinkedList* list, void* data);
void removeFromBeginning(DoublyLinkedList* list);
void removeFromEnd(DoublyLinkedList* list);
void printList(DoublyLinkedList* list);
void freeList(DoublyLinkedList* list);

#endif

// DoublyLinkedList.c
#include <stdio.h>
#include <stdlib.h>
//#include "DoublyLinkedList.h"

DoublyLinkedList* createList() {
    DoublyLinkedList* list = (DoublyLinkedList*) malloc(sizeof(DoublyLinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void insertAtBeginning(DoublyLinkedList* list, void* data) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->prev = NULL;
    node->next = list->head;
    if (list->head) list->head->prev = node;
    else list->tail = node;
    list->head = node;
    list->size++;
}

void insertAtEnd(DoublyLinkedList* list, void* data) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    node->prev = list->tail;
    if (list->tail) list->tail->next = node;
    else list->head = node;
    list->tail = node;
    list->size++;
}

void removeFromBeginning(DoublyLinkedList* list) {
    if (!list->head) return;
    Node* temp = list->head;
    list->head = list->head->next;
    if (list->head) list->head->prev = NULL;
    else list->tail = NULL;
    free(temp->data);
    free(temp);
    list->size--;
}

void removeFromEnd(DoublyLinkedList* list) {
    if (!list->tail) return;
    Node* temp = list->tail;
    list->tail = list->tail->prev;
    if (list->tail) list->tail->next = NULL;
    else list->head = NULL;
    free(temp->data);
    free(temp);
    list->size--;
}

void printList(DoublyLinkedList* list) {
    printf("\nLista (tamanho: %d):\n", list->size);
    Node* current = list->head;
    if (!current) printf("[Lista Vazia]\n");
    while (current) {
        printf("  Nodo @%p -> Valor: %d\n", (void*)current, *(int*)current->data);
        current = current->next;
    }
    if (list->head) printf("Início: %d\n", *(int*)list->head->data);
    if (list->tail) printf("Fim: %d\n", *(int*)list->tail->data);
}

void freeList(DoublyLinkedList* list) {
    while (list->head) removeFromBeginning(list);
    free(list);
}

// main.c
#include <stdio.h>
#include <stdlib.h>
//#include "DoublyLinkedList.h"

void clearScreen() {
    printf("\033[H\033[J");
}

int main() {
    DoublyLinkedList* list = createList();
    int option;

    do {
        clearScreen();
        printList(list);
        printf("\nMenu:\n");
        printf("1 - Inserir no início\n");
        printf("2 - Inserir no final\n");
        printf("3 - Remover do início\n");
        printf("4 - Remover do final\n");
        printf("0 - Encerrar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        int* value;
        switch(option) {
            case 1:
                value = (int*) malloc(sizeof(int));
                printf("Digite um valor inteiro: ");
                scanf("%d", value);
                insertAtBeginning(list, value);
                break;
            case 2:
                value = (int*) malloc(sizeof(int));
                printf("Digite um valor inteiro: ");
                scanf("%d", value);
                insertAtEnd(list, value);
                break;
            case 3:
                removeFromBeginning(list);
                break;
            case 4:
                removeFromEnd(list);
                break;
            case 0:
                freeList(list);
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (option != 0);

    return 0;
}
