#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list_alunos.c"
#include "list_disciplinas.c"
#define True 1
#define False 0

FILE *alunosFile;
FILE *disciplinasFile;
FILE *periodoFiles;



void startFiles();
void cls();
int menu();
int menuAlunos();
int menuDisciplinas();
int menuPeriodos();
void getAlunoData(ALUNO *aluno);
void saveAlunos(LIST_ALUNO *list_of_alunos);
void printAluno(int contador, ALUNO aluno);
void continuar();
int sureDeleteData();


int main() {
    LIST_ALUNO listAlunos;
    start_list_aluno(&listAlunos);

    startFiles();
    cls();
    printf("Bem vindo ao sistema de cadastro de alunos, disciplinas e periodos.\n\n");

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
                            puts("Aluno salvo com sucesso!\n");
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
                            puts("Opçao invalida. Tente novamente.");
                            continuar();
                            break;
                        }
                    }
                }
                break;
            }
            case 2:{
                puts("Falta implementar menu de disciplinas");
                break;
            }
            case 3:{
                puts("Falta implementar menu de periodos.");
                break;
            }
            case 4:{
                puts("Falta implementar menu.");
                break;
            }
            case 5:{
                puts("Falta implementar menu.");
                break;
            }
            case 6:{
                puts("Salvando arquivos e saindo...");
                /* Implementar o salvamento de arquivos aqui */
                puts("Arquivos salvos com sucesso.");
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
    puts("\n\nPrograma encerrado pelo usuario!\n\n");
}


void startFiles() {
    alunosFile = fopen("alunos.dat", "r+b");
    if (alunosFile == NULL) {
        alunosFile = fopen("alunos.dat", "w+b");
        if (alunosFile == NULL) {
            fprintf(stderr, "Impossivel criar arquivo de alunos.");
            exit(1);
        }
    }
    fclose(alunosFile);


    disciplinasFile = fopen("disciplinas.dat", "r+b");
    if (disciplinasFile == NULL) {
        disciplinasFile = fopen("disciplinas.dat", "w+b");
        if (disciplinasFile == NULL) {
            fprintf(stderr, "Impossivel criar arquivo de disciplinas.");
            exit(1);
        }
    }
    fclose(disciplinasFile);


    periodoFiles = fopen("periodos.dat", "r+b");
    if (periodoFiles == NULL) {
        periodoFiles = fopen("periodos.dat", "w+b");
        if (periodoFiles == NULL) {
            fprintf(stderr, "Impossivel criar arquivo de periodos.");
            exit(1);
        }
    }
    fclose(periodoFiles);
}

int menu(){
    printf("********* MENU PRINCIPAL *********\n");
    puts("O que deseja fazer?");
    printf("1 --> Ir para aba de alunos.\n");
    printf("2 --> Ir para aba de disciplinas.\n");
    printf("3 --> Ir para aba de periodos.\n");
    printf("4 --> Listar disciplina de aluno por periodo.\n");
    printf("5 --> Listar alunos de disciplina por periodo.\n");
    printf("6 --> Sair do sistema.\n");
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
    puts("********** ABA DE DISCIPLINAS **********");
    puts("O que deseja fazer?");
    puts("1 --> Cadastrar disciplina.");
    puts("2 --> Listar disciplinas cadastradas.");
    puts("3 --> Remover disciplina cadastrada.");
    puts("4 --> Voltar ao menu inicial.");
    int decisao;
    fflush(stdin);
    printf("Digite o numero de sua escolha: ");
    scanf("%d", &decisao);
    cls();
    return decisao;
}

int menuPeriodos() {
    puts("********** ABA DE PERIODOS **********");
    puts("O que deseja fazer?");
    puts("1 --> Cadastrar Periodo.");
    puts("2 --> Listar Periodos cadastrados.");
    puts("3 --> Remover Periodo cadastrado.");
    puts("4 --> Voltar ao menu inicial.");
    int decisao;
    fflush(stdin);
    printf("Digite o numero de sua escolha: ");
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

void saveAlunos(LIST_ALUNO *list_of_alunos) {
    alunosFile = fopen("alunos.dat", "a+b");
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

void printAluno(int contador, ALUNO aluno) { /* printa um aluno na tela com sua posição e nome */
    printf("%d --> %5s   %30s   %11s\n", contador+1, aluno.codigo ,aluno.nome, aluno.cpf);
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


