#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __LIST_ALUNOS__
#define __LIST_ALUNOS__


#define DATA_TYPE ALUNO
#define NO NO_ALUNO
#define LIST_TYPE LIST_ALUNO

typedef struct AL {
    char codigo[6];
    char nome[50];
    char cpf[16];
} DATA_TYPE;

typedef struct NO {
    DATA_TYPE aluno;
    struct NO *next;
} NO;

typedef struct LIST_TYPE {
    NO *start;
    NO *end;
    int len;
} LIST_TYPE;


void start_list_aluno(LIST_TYPE *lista) {
    lista->start = NULL;
    lista->end = NULL;
    lista->len = 0;
}

NO *_create_node_aluno() {
    NO *new = (NO*) malloc(sizeof(NO));
    return new;
}

NO *_no_at_position_aluno(LIST_TYPE *lista, int position) {
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

void insert_start_aluno(LIST_TYPE *lista, DATA_TYPE aluno) {
    NO* new = _create_node_aluno();
    new->aluno = aluno;

    if (lista->start == NULL) {
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

void insert_end_aluno(LIST_TYPE *lista, DATA_TYPE aluno) {
    NO *new = _create_node_aluno();
    new->aluno = aluno;
    new->next = NULL;

    if (lista->start == NULL) {
        lista->start = new;
        lista->end = new;
    }
    else {
        lista->end->next = new;
        lista->end = new;
    }
    lista->len++;
}

void insert_at_position_aluno(LIST_TYPE *lista, DATA_TYPE aluno, int position) {
    if(position < 0) {
        position = lista->len + position;
    }
    if (position > lista->len || position < 0) {
        fprintf(stderr, "Index list out of range.");
        exit(1);
    }
    if (position == 0) {
        insert_start_aluno(lista, aluno);
    }
    if (position == lista->len) {
        insert_end_aluno(lista, aluno);
    }
    else {
        NO *aux = _no_at_position_aluno(lista, position - 1);
        NO *new = _create_node_aluno();

        new->aluno = aluno;
        new->next = aux->next;
        aux->next = new;
        lista->len++;
    }
}

DATA_TYPE aluno_at_position(LIST_TYPE *lista, int position) {
    int aux = 0;
    NO *no_aux = lista->start;

    if(position < 0) {
        position = lista->len + position;
    }
    if (position >= lista->len || position < 0) {
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
    return no_aux->aluno;
}

void print_list_aluno(LIST_TYPE *lista) {
    NO *aux = lista->start;
    putchar('[');
    if (aux == NULL) {
        putchar(']');
    }
    while(aux != NULL) {
        printf("%s%c", (aux->aluno).nome, aux->next==NULL?']':',');
        aux = aux->next;
    }
    putchar('\n');
}

void del_position_aluno(LIST_TYPE *lista, int position) {
    if (position < 0) {
        position = lista->len + position;
    }
    if (position >= lista->len || position < 0) {
        fprintf(stderr, "Index list out of range.");
        exit(1);
    }
    if (position == 0 && lista->len == 1) {
        NO *aux = lista->start;
        lista->start = NULL;
        lista->end = NULL;
        free(aux);
    }
    else if (position == 0 && lista->len != 1) {
        NO *aux = lista->start;
        lista->start = aux->next;
        free(aux);
    }
    else {
        NO *before_to_remove = _no_at_position_aluno(lista, position-1);
        NO *to_remove = before_to_remove->next;
        before_to_remove->next = before_to_remove->next->next;
        free(to_remove);
    }
    lista->len--;
}

void del_first_aluno(LIST_TYPE *lista) {
    del_position_aluno(lista, 0);
}

void del_last_aluno(LIST_TYPE *lista) {
    del_position_aluno(lista, lista->len - 1);
}

int query_aluno_by_code(LIST_TYPE *lista, char *code) { /*Procura um aluno pelo code e retorna a posição do nó na lista*/
    NO *aux = lista->start;
    if (aux == NULL) {
        return -1;
    }
    for (int i = 0; i < lista->len; i++) {
        int teste = strcmp(code, (aux->aluno).codigo);
        if (!teste){
            return i;
        }
        if (aux->next != NULL)  {
            aux = aux->next;
        }
    }
    return -1;
}

int query_aluno_by_name(LIST_TYPE *lista, char *nome) {
    NO *aux = lista->start;
    if (aux == NULL) {
        return -1;
    }
    for (int i = 0; i < lista->len; i++) {
        char name_temp[50];
        char name_test[50];
        strcpy(name_temp, strlwr(nome));
        strcpy(name_test, strlwr((aux->aluno).nome));

        int teste = strcmp(name_temp, name_test);
        if (!(teste)) {
            return i;
        }
        if (aux->next != NULL) {
            aux = aux->next;
        }
    }
    return -1;
}


#undef DATA_TYPE
#undef NO
#undef LIST_TYPE

#endif // __LIST_ALUNOS__
