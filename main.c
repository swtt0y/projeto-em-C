#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct {
    char nome[10];
    char senha[12];
}adm;
adm Adm;

typedef struct usuario{
    char nome[25];
    char cpf[12];
    char senha[12];
    struct usuario *pont;

}usuario;

usuario* lista_usuarios (){
    usuario *lu;
    lu = (usuario*) malloc (sizeof(usuario));
    if(lu != NULL){
      lu->pont=NULL; //*lu = NULL n funciona
    }
    return lu;
}

void carregar(usuario *usuarios){
    FILE *fp;
    fp = fopen("arquivo.txt", "r");
    char palavra[25];
    usuario *novo = NULL;
     if(fp == NULL){
        return;
     }
     while (fscanf(fp, "%s", palavra) != EOF) {
        if (strcmp(palavra, "nome:") == 0) {
            novo = (usuario*) malloc(sizeof(usuario));
            fscanf(fp, "%s", novo->nome);
        }
        else if(strcmp(palavra, "CPF:")==0){
            fscanf(fp, "%s", novo->cpf);
        }
        else if(strcmp(palavra, "senha:")==0){
            fscanf(fp, "%s", novo->senha);
            novo->pont = usuarios->pont;
            usuarios->pont = novo;
        }
    }
    fclose(fp);
}

void salva(usuario *usuarios){
    FILE *fp;
    fp=fopen("arquivo.txt", "w");
    if(fp==NULL){
        puts("erro ao abrir o arquivo");
        exit(1);
    }
    usuario *no;
    no = usuarios->pont;
    while(no!=NULL){
        fprintf(fp, "\nusuario \nnome: %s\nCPF: %s\nsenha: %s\n", no->nome, no->cpf, no->senha);
        no = no->pont;
    }
    fclose(fp);
}

void inicio(){
    puts("//////////////////////////\n");
    puts("sistema de cadastro e busca\n");
    puts("//////////////////////////\n");
    puts("bem-vindo!");
    puts("qual sera o modo de acesso?");
    puts("1. admistrador");
    puts("2. usuario");
    puts("aperta 0 para parar o programa");
}

void menu_adm(){
    puts("o que deseja fazer como adm?");
    puts("1. mudar cadastro de algum usuario");
    puts("2. mudar cadastro de adm");
    puts("3. sair do modo adm");
    puts("4. adicionar cadastro");
    puts("5. sair do sistema");
}

usuario* verifica(usuario *usuarios){
    usuario *no;
    no = usuarios->pont;
    char cpf[12];
    printf("digite seu cpf para que verifique no sistema: ");
    scanf("%s", cpf);
    while(no != NULL){
        if (strcmp(cpf, no->cpf) == 0){
            printf("cadastro já está no sistema!");
            return no;
        }
        no = no->pont;
    }
    return NULL;
}

void dados(usuario *usuarios) {
    usuario *novo;
    novo = (usuario*) malloc(sizeof(usuario));
    printf("defina seu cadastro\n");
    printf("qual o seu nome?");
    scanf("%s", novo->nome);
    printf("qual o seu cpf? ");
    scanf("%s", novo->cpf);
    printf("qual será a sua senha?");
    scanf("%s", novo->senha);
    puts("cadastro realizado com sucesso!");
    novo->pont = usuarios->pont;
    usuarios->pont = novo;
    salva(usuarios);
}

void alterar_cad(usuario *usuarios){
    usuario *no = verifica(usuarios);
    if(no == NULL){
        puts("cpf não encontrado");
        return;
    }
    int escolha;
    while(1){
        puts("qual campo deseja alterar no cadastro?");
        puts("1. nome");
        puts("2. CPF");
        puts("3. senha");
        puts("4. todos");
        scanf("%d", &escolha);
         switch(escolha){
            case 1:
                printf("novo nome: ");
                scanf("%s", no->nome);
                salva(usuarios);
                puts("alteração salva com sucesso!");
                break;
            case 2:
                printf("novo CPF: ");
                scanf("%s", no->cpf);
                salva(usuarios);
                puts("alteração salva com sucesso!");
                break;
            case 3:
                printf("nova senha: ");
                scanf("%s", no->senha);
                salva(usuarios);
                puts("alteração salva com sucesso!");
                break;
            case 4:
                printf("novo nome: ");
                scanf("%s", no->nome);
                printf("novo CPF: ");
                scanf("%s", no->cpf);
                printf("nova senha: ");
                scanf("%s", no->senha);
                salva(usuarios);
                puts("alterações salvas com sucesso!");
                break;
            default:
                puts("opção invalida");
            }
        }
}

void login_admistrador(adm *adm, usuario *usuarios){
    char nome[10];
    char senha[12];
    int escolha;
    puts("\nfaça o login exclusivo do administrador");
    printf("nome: ");
    scanf("%s", nome);
    printf("senha: ");
    scanf("%s", senha);
    if (strcmp(adm->nome, nome) == 0) {
        if (strcmp(adm->senha, senha) == 0) {
            puts("Login realizado com sucesso!");
        }
        else {
            puts("senha incorreta");
        }
    }
    else {
        puts("nome incorreto");
    }
    while(1){
        menu_adm();
        scanf("%d", &escolha);
        switch(escolha){
        case 1:
             alterar_cad(usuarios);
             break;
        }
    }

}

void define_adm (adm *adm){
    puts("percebemos que ainda não possue o login de administrador.");
    puts("defina os campos");
    printf("Nome: ");
    scanf("%s", adm->nome);
    printf("Senha: ");
    scanf("%s", adm->senha);
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    adm *adm = &Adm;
    usuario *usuarios = lista_usuarios();
    int entrada;
    carregar(usuarios);
    while(1){
        FILE *fp;
        char palavra[30];
        inicio();
        scanf("%d", &entrada);
        if(entrada==1){
        fp = fopen("adms.txt", "r+");
        if(fp == NULL) {
            puts("erro ao abrir o arquivo.");
            exit(1);
        }
        fseek(fp, 0, SEEK_END);
        long posicao = ftell(fp);
        printf("posição: %ld\n", posicao);
        if(posicao==0){
            define_adm(adm);
            fprintf(fp,"\nADMINISTRADOR\nnome: %s\nsenha: %s\n", adm->nome, adm->senha);
            fseek(fp, 70, SEEK_END);
            login_admistrador(adm, usuarios);
        }
        fseek(fp, 0, SEEK_SET);
        while(!feof(fp)){
            fscanf(fp, "%s", palavra);
            if(strcmp(palavra, "nome:")==0){
                fscanf(fp, "%s", adm->nome);
            }
            else if(strcmp(palavra, "senha:")==0){
                fscanf(fp, "%s", adm->senha);
            }
        }
        fclose(fp);
        login_admistrador(adm, usuarios);
        }
        else if(entrada==2){
            if (verifica(usuarios) == NULL) {
                printf("cadastro pendente! aguarde!\n");
                dados(usuarios);
            }
        }
        else if(entrada==0){
            puts("saindo do sistema");
            break;
        }

        else{
            puts("não tem essa opção");
        }
    }
    return 0;
}
