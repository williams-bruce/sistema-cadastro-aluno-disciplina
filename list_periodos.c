#include <stdio.h>

#define DATA_TYPE PERIODO
#define NO NO_PERIODO
#define LIST_TYPE LIST_PERIODO

typedef struct PER {
    char codigo[8];
    struct PER *next;
} DATA_TYPE;

typedef struct NO {
    DATA_TYPE periodo;
    struct NO *next;
} NO;

typedef struct LIST_TYPE {
    NO *start;
    NO *end;
    int len;
} LIST_TYPE;


void start_list_periodo(LIST_TYPE *lista) {
    lista->start = NULL;
    lista->end = NULL;
    lista->len = 0;
}

NO *_create_node_periodo() {
    NO *new = (NO*) malloc(sizeof(NO));
    return new;
}

NO *_no_at_position_periodo(LIST_TYPE *lista, int position) {
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

void insert_start_periodo(LIST_TYPE *lista, DATA_TYPE periodo) {
    NO* new = _create_node_periodo();
    new->periodo = periodo;

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

void insert_end_periodo(LIST_TYPE *lista, DATA_TYPE periodo) {
    NO *new = _create_node_periodo();
    new->periodo = periodo;
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

void insert_at_position_periodo(LIST_TYPE *lista, DATA_TYPE periodo, int position) {
    if(position < 0) {
        position = lista->len + position;
    }
    if (position > lista->len || position < 0) {
        fprintf(stderr, "Index list out of range.");
        exit(1);
    }
    if (position == 0) {
        insert_start_periodo(lista, periodo);
    }
    if (position == lista->len) {
        insert_end_periodo(lista, periodo);
    }
    else {
        NO *aux = _no_at_position_periodo(lista, position - 1);
        NO *new = _create_node_periodo();

        new->periodo = periodo;
        new->next = aux->next;
        aux->next = new;
        lista->len++;
    }
}

DATA_TYPE periodo_at_position(LIST_TYPE *lista, int position) {
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
    return no_aux->periodo;
}

void print_list_periodo(LIST_TYPE *lista) {
    NO *aux = lista->start;
    putchar('[');
    if (aux == NULL) {
        putchar(']');
    }
    while(aux != NULL) {
        printf("%s%c", (aux->periodo).codigo, aux->next==NULL?']':',');
        aux = aux->next;
    }
    putchar('\n');
}

void del_position_periodo(LIST_TYPE *lista, int position) {
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
        NO *before_to_remove = _no_at_position_periodo(lista, position-1);
        NO *to_remove = before_to_remove->next;
        before_to_remove->next = before_to_remove->next->next;
        free(to_remove);
    }
    lista->len--;
}

void del_first_periodo(LIST_TYPE *lista) {
    del_position_periodo(lista, 0);
}

void del_last_periodo(LIST_TYPE *lista) {
    del_position_periodo(lista, lista->len - 1);
}

int query_periodo_by_code(LIST_TYPE *lista, char *code) { /*Procura um periodo pelo code e retorna a posição do nó na lista*/
    NO *aux = lista->start;
    if (aux == NULL) {
        return -1;
    }
    for (int i = 0; i < lista->len; i++) {
        int teste = strcmp(code, (aux->periodo).codigo);
        if (!teste){
            return i;
        }
        if (aux->next != NULL)  {
            aux = aux->next;
        }
    }
    return -1;
}


#undef DATA_TYPE
#undef NO
#undef LIST_TYPE
