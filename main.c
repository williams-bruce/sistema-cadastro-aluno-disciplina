#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void saveAluno(FILE *file, ALUNO aluno);
void printAluno(int contador, ALUNO aluno);
void continuar();
int deleteData();


int main() {
    LIST_ALUNO listAlunos;
    start_list_aluno(&listAlunos);

    startFiles();
    cls();
    printf("Bem vindo ao sistema de cadastro de alunos, disciplinas e periodos.\n\n");

    int stayOnLoop = True;
    while(stayOnLoop) {
        switch (menu()) {
            case 1:{
                cls();
                switch(menuAlunos()) {
                    case 1:{ /* Cadastra um novo aluno */
                        cls();
                        ALUNO aluno;
                        puts("Digite o codigo do aluno:");
                        fflush(stdin);
                        gets(aluno.codigo);
                        cls();

                        puts("Digite o nome do aluno:");
                        fflush(stdin);
                        gets(aluno.nome);
                        cls();

                        puts("Digite o cpf do aluno (apenas numeros):");
                        fflush(stdin);
                        gets(aluno.cpf);
                        cls();

                        insert_end_aluno(&listAlunos, aluno);
                        puts("Aluno salvo com sucesso!\n");
                        continuar();
                        cls();
                        break;
                    }
                    case 2:{ /* Lista todos os alunos cadastrados */
                        cls();
                        if (listAlunos.len == 0) {
                            puts("Nao ha alunos cadastrados!");
                            continuar();
                            cls();
                            break;
                        }
                        printf("Alunos cadastrados: \n\n");
                        for(int i = 0; i<listAlunos.len; i++){
                            ALUNO alunoToPrint = aluno_at_position(&listAlunos, i);
                            printAluno(i, alunoToPrint);
                        }
                        puts("\n");
                        continuar();
                        cls();
                        break;
                    }
                    case 3:{ /* Remove um aluno cadastrado */
                        char nameToRemove[50];
                        puts("Digite o nome do aluno a ser removido: ");
                        fflush(stdin);
                        gets(nameToRemove);
                        cls();
                        int position = query_aluno_by_name(&listAlunos, nameToRemove);

                        if (position == -1){
                            printf("O aluno %s nao esta cadastrado. Tente novamente com um aluno cadastrado.\n\n", nameToRemove);
                            continuar();
                            cls();
                            break;
                        }
                        if (deleteData()){
                            del_position_aluno(&listAlunos, position);
                            puts("Aluno removido com sucesso!\n\n");
                            continuar();
                            cls();
                            break;
                        }
                        cls();
                        break;
                    }
                    default:{
                        puts("Opçao invalida. Tente novamente.");
                        continuar();
                        cls();
                        break;
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
                break;
            }
        }
    }
    puts("\n\nPrograma encerrado pelo usuario!\n\n");
}


void startFiles() {
    alunosFile = fopen("alunos.dat", "r+b");
    if (alunosFile == NULL) {
        alunosFile = fopen("aluno.dat", "w+b");
        if (alunosFile == NULL) {
            fprintf(stderr, "Impossivel criar arquivo de alunos.");
            exit(1);
        }
    }
    fclose(alunosFile);


    disciplinasFile = fopen("disciplinas.dat", "r+b");
    if (disciplinasFile == NULL) {
        disciplinasFile = fopen("aluno.dat", "w+b");
        if (disciplinasFile == NULL) {
            fprintf(stderr, "Impossivel criar arquivo de disciplinas.");
            exit(1);
        }
    }
    fclose(disciplinasFile);


    periodoFiles = fopen("periodos.dat", "r+b");
    if (periodoFiles == NULL) {
        periodoFiles = fopen("aluno.dat", "w+b");
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
    puts("2 --> Listar alunos cadastrados.");
    puts("3 --> Remover aluno cadastrado.");
    int decisao;
    fflush(stdin);
    printf("\nDigite o numero de sua escolha: ");
    scanf("%d", &decisao);
    cls();
    return decisao;
}

int menuDisciplinas() {
    puts("********** ABA DE ALUNOS **********");
    puts("O que deseja fazer?");
    puts("1 --> Cadastrar disciplina.");
    puts("2 --> Listar disciplinas cadastradas.");
    puts("2 --> Remover disciplina cadastrada.");
    int decisao;
    fflush(stdin);
    printf("Digite o numero de sua escolha: ");
    scanf("%d", &decisao);
    return decisao;
}

int menuPeriodos() {
    puts("********** ABA DE ALUNOS **********");
    puts("O que deseja fazer?");
    puts("1 --> Cadastrar Periodo.");
    puts("2 --> Listar Periodos cadastrados.");
    puts("2 --> Remover Periodo cadastrado.");
    int decisao;
    fflush(stdin);
    printf("Digite o numero de sua escolha: ");
    scanf("%d", &decisao);
    return decisao;
}

void cls() {
    for(int i = 0; i< 100; i++){
        putchar('\n');
    }
}

void saveAluno(FILE *alunoFile, ALUNO aluno) {
    alunoFile = fopen("alunos.dat", "a+b");
    if (alunoFile == NULL) {
        puts("Nao foi possivel salvar os dados do aluno.");
        exit(1);
    }
    if (fwrite(&aluno, sizeof(ALUNO), 1, alunoFile) != 1) {
        puts("Falha ao tentar escrever o registro do aluno.");
        exit(1);
    }
    fclose(alunoFile);
}

void printAluno(int contador, ALUNO aluno) { /* printa um aluno na tela com sua posição e nome */
    
    printf("%d --> %s\n", contador+1, aluno.nome);
}

void continuar() {
    printf("Aperte <enter> para continuar...");
    fflush(stdin);
    getchar();
}

int deleteData() {
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
    return retorno;
}

