#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int value;
    struct No *prev;
    struct No *next;
} NO;

typedef struct list {
    NO *start;
    NO *end;
    int len;
} list;


void start_list(list *lista);
NO *_create_node();
void insert_start(list *lista, int value);
void insert_end(list *lista, int value);
void insert_at_position(list *lista, int value, int position);
int value_at_position(list *lista, int value);
NO *_no_at_position(list *lista, int value);
void print_list(list *lista);
void remove_at_position(list *lista, int position);
void remove_first(list *lista);
void remove_last(list *lista);



int main() {
    list list_test;
    start_list(&list_test);
    printf("Meu tamanho inicial: %d\n", list_test.len);
    print_list(&list_test);

    insert_start(&list_test, 5);
    printf("Agora meu tamanho eh %d\n", list_test.len);
    print_list(&list_test);

    insert_start(&list_test, 13);
    printf("Agora meu tamanho eh %d\n", list_test.len);
    print_list(&list_test);

    insert_start(&list_test, 34);
    printf("Agora meu tamanho eh %d\n", list_test.len);
    print_list(&list_test);

    insert_end(&list_test, 3);
    printf("Agora meu tamanho eh %d\n", list_test.len);
    print_list(&list_test);

    insert_end(&list_test, 77);
    printf("Agora meu tamanho eh %d\n", list_test.len);
    print_list(&list_test);

    insert_at_position(&list_test, 110, 3);
    printf("Agora meu tamanho eh %d\n", list_test.len);
    print_list(&list_test);

    insert_at_position(&list_test, 700, 3);
    printf("Agora meu tamanho eh %d\n", list_test.len);
    print_list(&list_test);

    remove_at_position(&list_test, 3);
    printf("Agora meu tamanho eh %d\n", list_test.len);
    print_list(&list_test);

    remove_at_position(&list_test, 3);
    printf("Agora meu tamanho eh %d\n", list_test.len);
    print_list(&list_test);

    printf("Na posicao 1 esta %d\n", value_at_position(&list_test, 0));
    printf("Na posicao 2 esta %d\n", value_at_position(&list_test, 1));
    printf("Na posicao 3 esta %d\n", value_at_position(&list_test, 2));
    printf("Na posicao 4 esta %d\n", value_at_position(&list_test, 3));
    printf("Na posicao 5 esta %d\n", value_at_position(&list_test, 4));
    printf("Na posicao 6 esta %d\n", value_at_position(&list_test, 5));


    return 0;
}


void start_list(list *lista) {
    lista->start = NULL;
    lista->end = NULL;
    lista->len = 0;
}

NO *_create_node() {
    NO *new = (NO*) malloc(sizeof(NO));
    return new;
}

void insert_start(list *lista, int value) {
    NO* new = _create_node();
    new->value = value;

    if (lista->start == NULL) {
        new->prev = NULL;
        new->next = NULL;
        lista->start = new;
        lista->end = new;
    }
    else {
        new->next = lista->start;
        lista->start = new;
    }
    lista->len++;
}

void insert_end(list *lista, int value) {
    NO *new = _create_node();
    new->value = value;
    new->next = NULL;

    if (lista->start == NULL) {
        new->prev = NULL;
        lista->start = new;
        lista->end = new;
    }
    else {
        lista->end->next = new;
        new->prev = lista->end;
        lista->end = new;
    }
    lista->len++;
}

void insert_at_position(list *lista, int value, int position) {
    if(position < 0) {
        position = lista->len + position;
    }
    if (position > lista->len || position < 0) {
        // printf("Index list out of range.");
        fprintf(stderr, "Index list out of range.");
        exit(1);
    }
    if (position == 0) {
        insert_start(lista, value);
    }
    if (position == lista->len) {
        insert_end(lista, value);
    }
    else {
        NO *aux = _no_at_position(lista, position - 1);
        NO *new = _create_node();

        new->value = value;
        new->prev = aux;
        new->next = aux->next;
        aux->next = new;
        lista->len++;
    }
}

int value_at_position(list *lista, int position) {
    int aux = 0;
    NO *no_aux = lista->start;

    if(position < 0) {
        position = lista->len + position;
    }
    if (position >= lista->len || position < 0) {
        // printf("Index list out of range.\n");
        fprintf(stderr, "Index list out of range.");
        exit(1);
    }
    while (aux <= position){
        if (aux == position) {
            break;
        }
        no_aux = no_aux->next;
        aux++;
    }
    return no_aux->value;
}

NO *_no_at_position(list *lista, int position) {
    int aux = 0;
    NO *no_aux = lista->start;

    if(position < 0) {
        position = lista->len + position;
    }
    if (position >= lista->len || position < 0) {
        printf("Index list out of range.\n");
        exit(1);
    }
    while (aux <= position){
        if (aux == position) {
            break;
        }
        no_aux = no_aux->next;
        aux++;
    }
    return no_aux;
}

void print_list(list *lista) {
    NO *aux = lista->start;
    putchar('[');
    if (aux == NULL) {
        putchar(']');
    }
    while(aux != NULL) {
        printf("%d%c", aux->value, aux->next==NULL?']':',');
        aux = aux->next;
    }
    putchar('\n');
}

void remove_at_position(list *lista, int position) {
    if (position < 0) {
        position = lista->len + position;
    }
    if (position >= lista->len - 1 || position < 0) {
        fprintf(stderr, "Index list out of range.");
        exit(1);
    }
    else {
        NO *to_remove = _no_at_position(lista, position);
        to_remove->prev->next = to_remove->next;
        to_remove->next->prev = to_remove->prev;
        lista->len--;
        free(to_remove);
    }
}

void remove_first(list *lista) {
    remove_at_position(lista, 0);
}

void remove_last(list *lista) {
    remove_at_position(lista, lista->len - 1);
}


