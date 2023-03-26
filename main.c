#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.n>
#endif
#include "list_alunos.c"
#include "list_disciplinas.c"
#include "list_matriculas.c"
#define True 1
#define False 0
#define ARQ_ALUNOS "alunos.dat"
#define ARQ_DISCIPLINAS "disciplinas.dat"
#define ARQ_MATRICULAS "matriculas.dat"

FILE *alunosFile;
FILE *disciplinasFile;
FILE *matriculasFile;


void startFiles();
void cls();
int menu();
int menuAlunos();
int menuDisciplinas();
int menuMatriculas();
void getAlunoData(ALUNO *aluno);
void getMatriculaData(MATRICULA *matricula, LIST_ALUNO *listAluno, LIST_DISCIPLINA *listDisciplina);
void getDisciplinaData(DISCIPLINA *disciplina);
void saveAlunosOnFile(LIST_ALUNO *list_of_alunos);
void saveDisciplinasOnFile(LIST_DISCIPLINA *list_of_disciplinas);
void saveMatriculasOnFile(LIST_MATRICULA *list_of_matriculas);
void printAluno(int contador, ALUNO aluno);
void printDisciplina(int contador, DISCIPLINA Disciplina);
void printMatricula(int contador, MATRICULA matricula);
void continuar();
int sureDeleteData();
void getAlunosFromFile(LIST_ALUNO *list_of_alunos);
void getDisciplinasFromFile(LIST_DISCIPLINA *list_of_disciplinas);
void getMatriculasFromFile(LIST_MATRICULA *list_of_matriculas);
int isFileEmpty(FILE *file, char *filename);
int _okPeriodoFormat(char *codigo_periodo);
void getInfoMatriculaAluno(LIST_MATRICULA *list_of_matriculas, char *aluno);
void printDisciplinasAluno(LIST_MATRICULA *list_of_matriculas, char *aluno);
void printAlunosOnDisciplina(LIST_MATRICULA *list_of_matriculas, char *disciplina);
void printDisciplinasOfAlunoOnPeriodo(LIST_MATRICULA *list_of_matriculas, char *aluno, char *periodo);
void printAlunosOfDisciplinaOnPeriodo(LIST_MATRICULA *list_of_matriculas, char *disciplina, char *periodo);


int main() {
    LIST_ALUNO listAlunos;
    start_list_aluno(&listAlunos);

    LIST_DISCIPLINA listDisciplinas;
    start_list_disciplina(&listDisciplinas);

    LIST_MATRICULA listMatriculas;
    start_list_matricula(&listMatriculas);

    startFiles();

    if (!isFileEmpty(alunosFile, ARQ_ALUNOS)) {
        getAlunosFromFile(&listAlunos);
    }
    if (!isFileEmpty(disciplinasFile, ARQ_DISCIPLINAS)) {
        getDisciplinasFromFile(&listDisciplinas);
    }
    if (!isFileEmpty(matriculasFile, ARQ_MATRICULAS)) {
        getMatriculasFromFile(&listMatriculas);
    }

    cls();
    printf("Bem vindo ao sistema de cadastro de alunos, disciplinas e Matriculas.\n\n");

    int stayOnLoop = True;
    while(stayOnLoop) {
        switch (menu()) {
            case 1:{ /*ABA DE ALUNOS*/
                int stayOnAlunos = True;
                while(stayOnAlunos){
                    cls();
                    switch(menuAlunos()) {
                        case 1:{ /* Cadastra um novo aluno */
                            cls();
                            ALUNO aluno;
                            getAlunoData(&aluno);
                            insert_end_aluno(&listAlunos, aluno);
                            puts("Aluno cadastrado com sucesso!\n");
                            continuar();
                            break;
                        }
                        case 2:{ /* Lista todos os alunos cadastrados */
                            cls();
                            if (listAlunos.len == 0) {
                                puts("Nao ha alunos cadastrados!\n");
                                continuar();
                                break;
                            }
                            printf("Alunos cadastrados: \n\n");
                            printf("nr    Codigo                     Nome              CPF\n");
                            for(int i = 0; i<listAlunos.len; i++){
                                ALUNO alunoToPrint = aluno_at_position(&listAlunos, i);
                                printAluno(i, alunoToPrint);
                            }
                            puts("\n");
                            continuar();
                            break;
                        }
                        case 3:{ /* Remove um aluno cadastrado */
                            char alunoToRemove[50];
                            puts("Digite o codigo do aluno a ser removido: ");
                            fflush(stdin);
                            gets(alunoToRemove);
                            cls();
                            int position = query_aluno_by_code(&listAlunos, alunoToRemove);
                            if (position == -1){
                                printf("O aluno %s nao esta cadastrado. Tente novamente com um aluno cadastrado.\n\n", alunoToRemove);
                                continuar();
                                break;
                            }
                            printf("Voce pretende apagar os dados do aluno:\n");
                            printAluno(position, aluno_at_position(&listAlunos, position));
                            putchar('\n');
                            if (sureDeleteData()){
                                del_position_aluno(&listAlunos, position);
                                puts("Aluno removido com sucesso!\n\n");
                                continuar();
                                break;
                            }
                            break;
                        }
                        case 4:{
                            stayOnAlunos = False;
                            cls();
                            break;
                        }
                        default:{
                            puts("Opcao invalida. Tente novamente.");
                            continuar();
                            break;
                        }
                    }
                }
                break;
            }
            case 2:{ /*ABA DE DISCIPLINAS*/
                int stayOnDisciplina = True;
                while(stayOnDisciplina) {
                    cls();
                    switch(menuDisciplinas()) {
                        case 1: {
                            cls();
                            DISCIPLINA disciplina;
                            getDisciplinaData(&disciplina);
                            insert_end_disciplina(&listDisciplinas, disciplina);
                            puts("Disciplina cadastrado com sucesso!\n");
                            continuar();
                            break;
                        }
                        case 2:{ /*LISTAR DISCIPLINAS*/
                            cls();
                            if (listDisciplinas.len == 0) {
                                puts("Nao ha disciplinas cadastrados!\n");
                                continuar();
                                break;
                            }
                            printf("Disciplinas cadastradas: \n\n");
                            printf("nr    Codigo                     Nome     %10s       Professor    %5s    Creditos\n", " ", " ");
                            for(int i = 0; i<listDisciplinas.len; i++){
                                DISCIPLINA disciplinaToPrint = disciplina_at_position(&listDisciplinas, i);
                                printDisciplina(i, disciplinaToPrint);
                            }
                            puts("\n");
                            continuar();
                            break;
                        }
                        case 3: { /*REMOVER DISCIPLINA*/
                            char disciplinaToRemove[50];
                            puts("Digite o codigo da disciplina a ser removida: ");
                            fflush(stdin);
                            gets(disciplinaToRemove);
                            cls();
                            int position = query_disciplina_by_codigo(&listDisciplinas, disciplinaToRemove);
                            if (position == -1){
                                printf("A disciplina \"%s\" nao esta cadastrada. Tente novamente com uma disciplina cadastrada.\n\n", disciplinaToRemove);
                                continuar();
                                break;
                            }
                            printf("Voce pretende apagar os dados da disciplina:\n");
                            printDisciplina(position, disciplina_at_position(&listDisciplinas, position));
                            putchar('\n');
                            if (sureDeleteData()){
                                printf("%d\n", listDisciplinas.len);
                                printf("%d\n", position);
                                del_position_disciplina(&listDisciplinas, position);
                                puts("Disciplina removida com sucesso!\n\n");
                                continuar();
                                break;
                            }
                            break;
                        }
                        case 4:{ /*RETORNAR AO MENU INICIAL*/
                            stayOnDisciplina = False;
                            cls();
                            break;
                        }
                        default:{
                            puts("Opcao invalida. Tente novamente.");
                            continuar();
                            break;
                        }
                    }
                }
                break;
            }
            case 3:{ /*ABA DE MATRICULAS*/
                int stayOnMatricula = True;
                while(stayOnMatricula) {
                    cls();
                    switch (menuMatriculas()) {
                        case 1:{ /* Realizar matricula de aluno em disciplina.*/
                            cls();
                            MATRICULA matricula;
                            getMatriculaData(&matricula, &listAlunos, &listDisciplinas);
                            insert_end_matricula(&listMatriculas, matricula);
                            cls();
                            puts("Aluno matriculado com sucesso!");
                            continuar();
                            break;
                        }
                        case 2:{
                            puts("Exibindo todas as matriculas existentes...\n");
                            printf("nr |%14sNome%14s|%11sDisciplina%11s|%3sPeriodo%2s|\n","","","","","","");
                            printf("---|--------------------------------|--------------------------------|------------|\n", "","","");
                            for (int i = 0; i < listMatriculas.len; i++){
                                printMatricula(i, matricula_at_position(&listMatriculas, i));
                            }
                            printf("---|--------------------------------|--------------------------------|------------|\n", "","","");
                            puts("");
                            continuar();
                            break;
                        }
                        case 3:{ /* Listar disciplinas de aluno por periodo.*/
                            if (listMatriculas.len == 0){
                                puts("Nao ha matriculas cadastradas. Cadastre alunos em disciplinas e periodos...");
                                continuar();
                                break;
                            }
                            char aluno[50];
                            puts("Digite o nome do aluno: ");
                            fflush(stdin);
                            gets(aluno);
                            cls();
                            int position = query_matricula_by_aluno(&listMatriculas, aluno);
                            if (position == -1) {
                                printf("O aluno %s nao esta cadastrado. Tente novamente com um aluno cadastrado...\n", aluno);
                                continuar();
                                cls();
                                break;
                            }
                            printDisciplinasAluno(&listMatriculas, aluno);
                            char periodo[50];
                            puts("Digite o periodo a ser filtrado:");
                            fflush(stdin);
                            gets(periodo);
                            position = query_matricula_by_aluno_and_periodo(&listMatriculas, aluno, periodo);
                            if (position == -1) {
                                printf("O aluno %s nao esta matriculado em nenhuma disciplina no periodo dado. Tente novamente com um periodo cadastrado...\n", aluno);
                                continuar();
                                cls();
                                break;
                            }
                            cls();
                            printDisciplinasOfAlunoOnPeriodo(&listMatriculas, aluno, periodo);
                            continuar();
                            cls();
                            break;
                        }
                        case 4:{ /* Listar alunos de disciplina por periodo. */
                            if (listMatriculas.len == 0) {
                                puts("Nao ha matriculas cadastradas. Cadastre alunos em disciplinas e periodos...");
                                continuar();
                                break;
                            }
                            char disciplina[50];
                            puts("Digite o nome da disciplina:");
                            fflush(stdin);
                            gets(disciplina);
                            int position = query_matricula_by_disciplina(&listMatriculas, disciplina);
                            if (position == -1) {
                                cls();
                                printf("A disciplina %s nao esta cadastrada ou nao ha nenhum aluno na disciplina dada. Tente novamente...\n", disciplina);
                                continuar();
                                cls();
                                break;
                            }
                            cls();
                            printAlunosOnDisciplina(&listMatriculas, disciplina);
                            char periodo[50];
                            puts("Digite o periodo a ser filtrado:");
                            fflush(stdin);
                            gets(periodo);
                            position = query_matricula_by_disciplina_and_periodo(&listMatriculas, disciplina, periodo);
                            if (position == -1) {
                                printf("A disciplina %s nao esta cadastrada no periodo dado. Tente novamente com um periodo cadastrado...\n", disciplina);
                                continuar();
                                cls();
                                break;
                            }
                            cls();
                            printAlunosOfDisciplinaOnPeriodo(&listMatriculas, disciplina, periodo);
                            continuar();
                            cls();
                            break;
                        }
                        case 5:{ /*Remover matricula de aluno em disciplina.*/
                            char aluno[50];
                            puts("Digite o nome do aluno:");
                            fflush(stdin);
                            gets(aluno);
                            int alunoPosition = query_matricula_by_aluno(&listMatriculas, aluno);
                            if (alunoPosition == -1) {
                                cls();
                                printf("O aluno %s nao esta matriculado em nenhuma disciplina. Tente novamente novamente...\n");
                                continuar();
                                cls();
                                break;
                            }
                            char disciplina[50];
                            puts("Digite o nome da disciplina:");
                            gets(disciplina);
                            int disciplinaPosition = query_matricula_by_disciplina(&listMatriculas, disciplina);
                            if (disciplinaPosition == -1){
                                printf("A disciplina %s nao esta cadastrada. Tente novamente...\n", disciplina);
                                continuar();
                                cls();
                                break;
                            }
                            char periodo[20];
                            puts("Digite o periodo:");
                            gets(periodo);
                            int periodoPosition = query_matricula_by_periodo(&listMatriculas, periodo);
                            if (periodoPosition == -1){
                                printf("O periodo %s nao esta cadastrado. Tente novamente...\n", periodo);
                                continuar();
                                cls();
                                break;
                            }
                            printf("Voce pretende remover a seguinte matricula:\n");
                            int matriculaPosition = query_matricula_by_all_atributes(&listMatriculas, aluno, disciplina, periodo);
                            printMatricula(matriculaPosition, matricula_at_position(&listMatriculas, matriculaPosition));
                            putchar('\n');
                            if (sureDeleteData()){
                                del_position_matricula(&listMatriculas, matriculaPosition);
                                puts("Matricula removida com sucesso.");
                                continuar();
                                cls();
                            }
                            break;
                        }
                        case 6:{ /*RETORNAR AO MENU INICIAL*/
                            stayOnMatricula = False;
                            cls();
                            break;
                        }
                        default:{
                            puts("Opcao invalida. Tente novamente.");
                            continuar();
                            break;
                        }
                    }
                }
                break;
            }
            case 4:{ /*Sair do programa*/
                cls();
                puts("Salvando arquivos...");
                Sleep(500);
                saveAlunosOnFile(&listAlunos);
                saveDisciplinasOnFile(&listDisciplinas);
                saveMatriculasOnFile(&listMatriculas);
                puts("Todos os arquivos foram salvos com sucesso!");
                Sleep(500);
                stayOnLoop = False;
                break;
            }
            
            default: {
                puts("Opcao invalida. Tente novamente.");
                continuar();
                cls();
                break;
            }
        }
    }
    puts("\nPrograma encerrado pelo usuario!\n");
}


void startFiles() {
    alunosFile = fopen(ARQ_ALUNOS, "r+b");
    if (alunosFile == NULL) {
        alunosFile = fopen(ARQ_ALUNOS, "w+b");
        if (alunosFile == NULL) {
            fprintf(stderr, "Impossivel criar arquivo de alunos.");
            exit(1);
        }
    }
    fclose(alunosFile);


    disciplinasFile = fopen(ARQ_DISCIPLINAS, "r+b");
    if (disciplinasFile == NULL) {
        disciplinasFile = fopen(ARQ_DISCIPLINAS, "w+b");
        if (disciplinasFile == NULL) {
            fprintf(stderr, "Impossivel criar arquivo de disciplinas.");
            exit(1);
        }
    }
    fclose(disciplinasFile);


    matriculasFile = fopen(ARQ_MATRICULAS, "r+b");
    if (matriculasFile == NULL) {
        matriculasFile = fopen(ARQ_MATRICULAS, "w+b");
        if (matriculasFile == NULL) {
            fprintf(stderr, "Impossivel criar arquivo de matriculas.");
            exit(1);
        }
    }
    fclose(matriculasFile);
}

int menu(){
    printf("********* MENU PRINCIPAL *********\n");
    puts("O que deseja fazer?");
    printf("1 --> Ir para aba de alunos.\n");
    printf("2 --> Ir para aba de disciplinas.\n");
    printf("3 --> Ir para aba de matriculas.\n");
    printf("4 --> Sair do sistema.\n");
    int decisao;
    fflush(stdin);
    printf("\nDigite o numero de sua escolha: ");
    scanf("%d", &decisao);
    return decisao;
}

int menuAlunos() {
    puts("********** ABA DE ALUNOS **********\n");
    puts("O que deseja fazer?");
    puts("1 --> Cadastrar aluno.");
    puts("2 --> Listar alunos.");
    puts("3 --> Remover aluno.");
    puts("4 --> Voltar ao menu inicial.");
    int decisao;
    fflush(stdin);
    printf("\nDigite o numero de sua escolha: ");
    scanf("%d", &decisao);
    cls();
    return decisao;
}

int menuDisciplinas() {
    puts("********** ABA DE DISCIPLINAS **********\n");
    puts("O que deseja fazer?");
    puts("1 --> Cadastrar disciplina.");
    puts("2 --> Listar disciplinas cadastradas.");
    puts("3 --> Remover disciplina cadastrada.");
    puts("4 --> Voltar ao menu inicial.");
    int decisao;
    fflush(stdin);
    printf("\nDigite o numero de sua escolha: ");
    scanf("%d", &decisao);
    cls();
    return decisao;
}

int menuMatriculas() {
    puts("********** ABA DE MatriculaS **********\n");
    puts("O que deseja fazer?");
    puts("1 --> Realizar matricula de aluno em disciplina.");
    puts("2 --> Exibir todas as matricular existentes.");
    puts("3 --> Listar disciplinas de aluno por Matricula.");
    puts("4 --> Listar alunos de disciplina por Matricula.");
    puts("5 --> Remover matricula de aluno em disciplina.");
    puts("6 --> Voltar ao menu inicial.");
    int decisao;
    fflush(stdin);
    printf("\nDigite o numero de sua escolha: ");
    scanf("%d", &decisao);
    cls();
    return decisao;
}

void cls() {
    for(int i = 0; i< 100; i++){
        putchar('\n');
    }
}

void getAlunoData(ALUNO *aluno) {
    while(True) {
        char codigo[50];
        puts("Digite o codigo do aluno:");
        fflush(stdin);
        gets(codigo);
        if (strlen(codigo) != 5) {
            printf("Seu codigo deve ter 5 digitos. Tente novamente...\n");
            continuar();
            cls();
            continue;
        }
        strcpy(aluno->codigo, codigo);
        cls();
        break;
    }

    puts("Digite o nome do aluno:");
    fflush(stdin);
    gets(aluno->nome);
    cls();

    while(True) {
        char cpf[50];
        puts("Digite o cpf do aluno (apenas numeros):");
        fflush(stdin);
        gets(cpf);
        if(strlen(cpf) != 11) {
            printf("O CPF deve ter 11 digitos. Tente novamente...\n");
            continuar();
            cls();
            continue;
        }
        strcpy(aluno->cpf, cpf);
        cls();
        break;
    }
}

void getDisciplinaData(DISCIPLINA *disciplina) {
    while(True) {
        char codigo[50];
        puts("Digite o codigo de 4 digitos da disciplina:");
        fflush(stdin);
        gets(codigo);
        if (strlen(codigo) != 4) {
            printf("Seu codigo deve ter 4 digitos. Tente novamente...\n");
            continuar();
            cls();
            continue;
        }
        strcpy(disciplina->codigo, codigo);
        cls();
        break;
    }

    puts("Digite o nome da disciplina:");
    fflush(stdin);
    gets(disciplina->nome);
    cls();
    
    puts("Digite o nome do professor da disciplina:");
    fflush(stdin);
    gets(disciplina->professor);
    cls();
    
    puts("Digite a quantidade de creditos da disciplina:");
    fflush(stdin);
    scanf(" %d",&(disciplina->qtde_creditos));
    cls();
}

void getMatriculaData(MATRICULA *matricula, LIST_ALUNO *listAluno, LIST_DISCIPLINA *listDisciplina) {
    while(True) {
        char nome[50];
        puts("Digite o nome do aluno a ser matriculado: ");
        fflush(stdin);
        gets(nome);

        int position = query_aluno_by_name(listAluno, nome);
        if (position == -1) {
            printf("O aluno %s nao esta cadastrado. Tente novamente com um aluno cadastrado...", nome);
            continuar();
            cls();
            continue;
        }
        ALUNO aluno = aluno_at_position(listAluno, position);
        strcpy(matricula->aluno, aluno.nome);
        cls();
        break;
    }

    while(True) {
        char nome[50];
        puts("Digite o nome da disciplina na qual o aluno sera matriculado: ");
        gets(nome);

        int position = query_disciplina_by_name(listDisciplina, nome);
        if (position == -1) {
            printf("A disciplina %s nao esta cadastrada. Tente novamente com uma disciplina cadastrada...", nome);
            continuar();
            cls();
            continue;
        }
        DISCIPLINA disciplina = disciplina_at_position(listDisciplina, position);
        strcpy(matricula->disciplina, disciplina.nome);
        cls();
        break;
    }
    
    while(True) {
        char periodo[50];
        puts("Digite o periodo (formato: AAAA.X, ex: 2021.1):");
        fflush(stdin);
        gets(periodo);
        if (!(_okPeriodoFormat(periodo))) {
            continuar();
            cls();
            continue;
        }
        strcpy(matricula->periodo, periodo);
        break;
    }
}

int _okPeriodoFormat(char *periodo) {
    if (strlen(periodo) != 6) {
        puts("Codigo fora do padrao especificado.");
        return 0;
    }
    if (periodo[5] != '1' && periodo[5] != '2') {
        puts("Em um ano so pode haver periodo 1 ou periodo 2.");
        return 0;
    }
    if (periodo[4] != '.'){
        puts("Deve haver um ponto separando o ano do periodo considerado.");
        return 0;
    }
    for (int i = 0; i < 4; i++){
        if (!(isdigit(periodo[i]))){
            puts("Os caracteres do ano devem ser numeros.");
            return 0;
        }
    }
    return 1;
}

void saveAlunosOnFile(LIST_ALUNO *list_of_alunos) {
    alunosFile = fopen(ARQ_ALUNOS, "wb");
    if (alunosFile == NULL) {
        puts("Nao foi possivel abrir o arquivo de alunos.");
        exit(1);
    }
    for (int i = 0; i < list_of_alunos->len; i++){
        ALUNO aluno = aluno_at_position(list_of_alunos, i);
        if (fwrite(&aluno, sizeof(ALUNO), 1, alunosFile) != 1) {
            puts("Falha ao tentar escrever o registro do aluno.");
            exit(1);
        }
    }
    fclose(alunosFile);
}

void saveDisciplinasOnFile(LIST_DISCIPLINA *list_of_disciplinas) {
    disciplinasFile = fopen(ARQ_DISCIPLINAS, "wb");
    if (disciplinasFile == NULL) {
        puts("Nao foi possivel abrir o arquivo de disciplinas.");
        exit(1);
    }
    for (int i = 0; i < list_of_disciplinas->len; i++){
        DISCIPLINA disciplina = disciplina_at_position(list_of_disciplinas, i);
        if (fwrite(&disciplina, sizeof(DISCIPLINA), 1, disciplinasFile) != 1) {
            puts("Falha ao tentar escrever o registro do disciplina.");
            exit(1);
        }
    }
    fclose(disciplinasFile);
}

void saveMatriculasOnFile(LIST_MATRICULA *list_of_matriculas) {
    matriculasFile = fopen(ARQ_MATRICULAS, "wb");
    if (matriculasFile == NULL) {
        puts("Nao foi possivel abrir o arquivo de Matriculas.");
        exit(1);
    }
    for (int i = 0; i < list_of_matriculas->len; i++){
        MATRICULA Matricula = matricula_at_position(list_of_matriculas, i);
        if (fwrite(&Matricula, sizeof(MATRICULA), 1, matriculasFile) != 1) {
            puts("Falha ao tentar escrever o registro do Matricula.");
            exit(1);
        }
    }
    fclose(matriculasFile);
}

void printAluno(int contador, ALUNO aluno) { /* printa um aluno na tela com sua posição e nome */
    printf("%d --> %5s   %30s   %11s\n", contador+1, aluno.codigo ,aluno.nome, aluno.cpf);
}

void printDisciplina(int contador, DISCIPLINA disciplina) { /* printa uma disciplina na tela com sua posição e nome */
    printf("%d --> %4s   %30s   %30s  %9d\n", contador+1, disciplina.codigo ,disciplina.nome, disciplina.professor, disciplina.qtde_creditos);
}

void printMatricula(int contador, MATRICULA matricula) {
    printf("%2d | %30s | %30s | %10s |\n",contador+1, matricula.aluno, matricula.disciplina, matricula.periodo);
}

void continuar() {
    printf("Aperte <enter> para continuar...");
    fflush(stdin);
    getchar();
}

int sureDeleteData() { /*Verifica se o usuario realmente quer deletar o dado*/
    int retorno = -1;
    while (retorno == -1){
        char decisao;
        puts("Voce esta deletando um dado do sistema e essa acao nao pode ser revertida. Deseja continuar?(s/n)");
        fflush(stdin);
        decisao = getchar();
        switch (decisao) {
            case 'S':
            case 's':{
                retorno = 1;
                break;
            }
            case 'n':
            case 'N':{
                retorno = 0;
                break;
            }
            default:{
                puts("Entrada invalida. Tente novamente.");
                continuar();
                cls();
                break;
            }
        }
    }
    cls();
    return retorno;
}

void getAlunosFromFile(LIST_ALUNO *list_of_alunos) {
    ALUNO aluno;
    if ((alunosFile = fopen(ARQ_ALUNOS, "rb")) == NULL){
        printf("O arquivo %s nao existe ou nao pode ser aberto.\n", ARQ_ALUNOS);
        exit(1);
    }
    rewind(alunosFile);
    while((fread(&aluno, sizeof(ALUNO), 1,alunosFile)) == 1) {
        insert_end_aluno(list_of_alunos, aluno);
    }
    fclose(alunosFile);
}

void getDisciplinasFromFile(LIST_DISCIPLINA *list_of_disciplinas) {
    DISCIPLINA disciplina;
    if ((disciplinasFile = fopen(ARQ_DISCIPLINAS, "rb")) == NULL){
        printf("O arquivo %s nao existe ou nao pode ser aberto.\n", ARQ_DISCIPLINAS);
        exit(1);
    }
    rewind(disciplinasFile);
    while((fread(&disciplina, sizeof(DISCIPLINA), 1,disciplinasFile)) == 1) {
        insert_end_disciplina(list_of_disciplinas, disciplina);
    }
    fclose(disciplinasFile);
}

void getMatriculasFromFile(LIST_MATRICULA *list_of_matriculas) {
    MATRICULA matricula;
    if ((matriculasFile = fopen(ARQ_MATRICULAS, "rb")) == NULL){
        printf("O arquivo %s nao existe ou nao pode ser aberto.\n", ARQ_ALUNOS);
        exit(1);
    }
    rewind(alunosFile);
    while((fread(&matricula, sizeof(MATRICULA), 1,matriculasFile)) == 1) {
        insert_end_matricula(list_of_matriculas, matricula);
    }
    fclose(matriculasFile);
}

int isFileEmpty(FILE *file, char *filename) {
    if ((file = fopen(filename, "rb"))==NULL){
        puts("Erro! Nao foi possivel abrir o arquivo!");
        exit(1);
    }
    if (fgetc(file)!=EOF){
        fclose(file);
        return False;
    }
    fclose(file);
    return True;
}

void getInfoMatriculaAluno(LIST_MATRICULA *list_of_matriculas, char *aluno) {
    while(True) {
        puts("Digite o nome do aluno: ");
        fflush(stdin);
        gets(aluno);
        int position = query_matricula_by_aluno(list_of_matriculas, aluno);
        if (position == -1) {
            printf("O aluno %s nao esta cadastrado. Tente novamente com um aluno cadastrado...", aluno);
            continuar();
            cls();
            continue;
        }
        break;
    }
}

void printDisciplinasAluno(LIST_MATRICULA *list_of_matriculas, char *aluno) {
    int contador = 1;
    NO_MATRICULA *aux = list_of_matriculas->start;

    char name_temp_aluno[50];
    char name_test_aluno[50];
    
    strcpy(name_temp_aluno, strlwr(aluno));

    printf("Lista das disciplinas do aluno %s:\n\n", aluno);
    printf(" nr %12s disciplina %7s Periodo \n"," ", " ");
    for(int i = 0; i < list_of_matriculas->len; i++) {
        strcpy(name_test_aluno, strlwr((aux->matricula).aluno));

        if (!(strcmp(name_temp_aluno, name_test_aluno))) {
            printf("%2d %24s %15s\n", contador, (aux->matricula).disciplina, (aux->matricula).periodo);
            contador++;
        }
        aux = aux->next;
    }
    putchar('\n');
}

void printDisciplinasOfAlunoOnPeriodo(LIST_MATRICULA *list_of_matriculas, char *aluno, char *periodo) {
    int contador = 1;
    NO_MATRICULA *aux = list_of_matriculas->start;

    char aluno_temp[50];
    char aluno_test[50];
    char periodo_temp[50];
    char periodo_test[50];
    
    strcpy(aluno_temp, strlwr(aluno));
    strcpy(periodo_temp, strlwr(periodo));

    printf("Lista das disciplinas do aluno %s no periodo %s:\n\n", aluno, periodo);
    printf(" nr %12s disciplina\n","");
    for(int i = 0; i < list_of_matriculas->len; i++) {
        strcpy(aluno_test, strlwr((aux->matricula).aluno));
        strcpy(periodo_test, strlwr((aux->matricula).periodo));

        int teste = abs(strcmp(aluno_temp, aluno_test)) + abs(strcmp(periodo_temp, periodo_test));
        if (!(teste)) {
            printf("%2d %24s\n", contador, (aux->matricula).disciplina);
            contador++;
        }
        aux = aux->next;
    }
    putchar('\n');
}

void printAlunosOnDisciplina(LIST_MATRICULA *list_of_matriculas, char *disciplina) {
    int contador = 1;
    NO_MATRICULA *aux = list_of_matriculas->start;

    char name_temp_disciplina[50];
    char name_test_disciplina[50];
    
    strcpy(name_temp_disciplina, strlwr(disciplina));

    printf("Lista dos alunos da disciplina %s por periodo:\n\n", disciplina);
    printf(" nr %12s aluno %7s Periodo \n"," ", " ");
    for(int i = 0; i < list_of_matriculas->len; i++) {
        strcpy(name_test_disciplina, strlwr((aux->matricula).disciplina));

        if (!(strcmp(name_temp_disciplina, name_test_disciplina))) {
            printf("%2d %24s %15s\n", contador, (aux->matricula).aluno, (aux->matricula).periodo);
            contador++;
        }
        aux = aux->next;
    }
    putchar('\n');
}

void printAlunosOfDisciplinaOnPeriodo(LIST_MATRICULA *list_of_matriculas, char *disciplina, char *periodo) {
    int contador = 1;
    NO_MATRICULA *aux = list_of_matriculas->start;

    char disciplina_temp[50];
    char disciplina_test[50];
    char periodo_temp[50];
    char periodo_test[50];
    
    strcpy(disciplina_temp, strlwr(disciplina));
    strcpy(periodo_temp, strlwr(periodo));

    printf("Lista dos alunos da disciplina %s no periodo %s:\n\n", disciplina, periodo);
    printf(" nr %12s aluno\n","");
    for(int i = 0; i < list_of_matriculas->len; i++) {
        strcpy(disciplina_test, strlwr((aux->matricula).disciplina));
        strcpy(periodo_test, strlwr((aux->matricula).periodo));

        int teste = abs(strcmp(disciplina_temp, disciplina_test)) + abs(strcmp(periodo_temp, periodo_test));
        // puts("------ start");
        // printf("%d\n", teste);
        // printf("disciplina temp: %s. ### disciplina test: %s\n", disciplina_temp, disciplina_test);
        // printf("periodo temp: %s. ### periodo test: %s\n", periodo_temp, periodo_test);
        // puts("------ end");
        if (!teste) {
            printf("%2d %24s\n", contador, (aux->matricula).aluno);
            contador++;
        }
        aux = aux->next;
    }
    putchar('\n');
}


