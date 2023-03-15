#define DATA_TYPE DISCIPLINA
#define NO NO_DISCIPLINA
#define LIST_TYPE LIST_DISCIPLINA

typedef struct DISC {
    char codigo[5];
    char nome[50];
    char professor[50];
    int qtde_creditos;
} DATA_TYPE;

typedef struct NO {
    DATA_TYPE disciplina;
    struct NO *next;
} NO;

typedef struct LIST_TYPE { /* ESTÁ NAS LISTAS ALUNOS E DISCIPLINAS */
    NO *start;
    NO *end;
    int len;
} LIST_TYPE;


void start_list_disciplina(LIST_TYPE *lista) { /* ESTÁ NAS LISTAS ALUNOS E DISCIPLINAS */
    lista->start = NULL;
    lista->end = NULL;
    lista->len = 0;
}

NO *_create_node_disciplina() {
    NO *new = (NO*) malloc(sizeof(NO));
    return new;
}

NO *_no_at_position_disciplina(LIST_TYPE *lista, int position) {
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

void insert_start_disciplina(LIST_TYPE *lista, DATA_TYPE disciplina) {
    NO* new = _create_node_disciplina();
    new->disciplina = disciplina;

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

void insert_end_disciplina(LIST_TYPE *lista, DATA_TYPE disciplina) {
    NO *new = _create_node_disciplina();
    new->disciplina = disciplina;
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

void insert_at_position_disciplina(LIST_TYPE *lista, DATA_TYPE disciplina, int position) {
    if(position < 0) {
        position = lista->len + position;
    }
    if (position > lista->len || position < 0) {
        fprintf(stderr, "Index list out of range.");
        exit(1);
    }
    if (position == 0) {
        insert_start_disciplina(lista, disciplina);
    }
    if (position == lista->len) {
        insert_end_disciplina(lista, disciplina);
    }
    else {
        NO *aux = _no_at_position_disciplina(lista, position - 1);
        NO *new = _create_node_disciplina();

        new->disciplina = disciplina;
        new->next = aux->next;
        aux->next = new;
        lista->len++;
    }
}

DATA_TYPE disciplina_at_position(LIST_TYPE *lista, int position) {
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
    return no_aux->disciplina;
}

void print_list_disciplina(LIST_TYPE *lista) {
    NO *aux = lista->start;
    putchar('[');
    if (aux == NULL) {
        putchar(']');
    }
    while(aux != NULL) {
        printf("%s%c", (aux->disciplina).nome, aux->next==NULL?']':',');
        aux = aux->next;
    }
    putchar('\n');
}

void del_position_disciplina(LIST_TYPE *lista, int position) {
    if (position < 0) {
        position = lista->len + position;
    }
    if (position >= lista->len - 1 || position < 0) {
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
        NO *before_to_remove = _no_at_position_disciplina(lista, position-1);
        NO *to_remove = before_to_remove->next;
        before_to_remove->next = before_to_remove->next->next;
        free(to_remove);
    }
    lista->len--;
}

void del_first_disciplina(LIST_TYPE *lista) {
    del_position_disciplina(lista, 0);
}

void del_last_disciplina(LIST_TYPE *lista) {
    del_position_disciplina(lista, lista->len - 1);
}

int query_disciplina_by_codigo(LIST_TYPE *lista, char *codigo) {
    NO *aux = lista->start;
    if (aux == NULL) {
        return -1;
    }
    for (int i = 0; i < lista->len; i++) {
        int teste = strcmp(codigo, (aux->disciplina).codigo);
        if (!(teste)) {
            return i;
        }
        if (aux->next != NULL) {
            aux = aux->next;
        }
    }
    return -1;
}

int query_disciplina_by_name(LIST_TYPE *lista, char *nome) {
    NO *aux = lista->start;
    if (aux == NULL) {
        return -1;
    }
    for (int i = 0; i < lista->len; i++) {
        char name_temp[50];
        char name_test[50];
        strcpy(name_temp, strlwr(nome));
        strcpy(name_test, strlwr((aux->disciplina).nome));
        
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
