#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define tam 10

typedef struct {
    char nome[25];
    char cpf[12];
    char senha[12];

}usuario;

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
    puts("4. adicionar cadastro")
    puts("5. sair do sistema");
}

int verifica(char cpfs[tam][12]){
    char num_cpf[12];
    puts("digite seu cpf para que verifique no sistema: ");
    scanf("%s", num_cpf);
    for (int i = 0; i < tam; i++){
        if (strcmp(num_cpf, cpfs[i]) == 0){
            printf("cadastro já está no sistema!");
            return 0;
        }
    }
    return 1;
}

usuario dados() {
    usuario usuario_novo;
    printf("defina seu cadastro\n");
    printf("qual o seu nome? ");
    scanf("%s", usuario_novo.nome);
    printf("qual o seu cpf? ");
    scanf("%s", usuario_novo.cpf);
    printf("qual será a sua senha? ");
    scanf("%s", usuario_novo.senha);
    getchar();
    puts("cadastro realizado com sucesso!");
    return usuario_novo;
}

void login_admistrador(usuario adm){
    char nome[25];
    char senha[12];
    int escolha;
    puts("\nfaça o login exclusivo do administrador");
    printf("nome: ");
    scanf("%s", &nome);
    printf("senha: ");
    scanf("%s", senha);
    if (strcmp(adm.nome, nome) == 0) {
        if (strcmp(adm.senha, senha) == 0) {
            puts("Login realizado com sucesso!");
        }
        else {
            puts("Login ou senha incorreto(s)");
        }
    }
    else {
        puts("Login ou senha incorreto(s)");
    }
    while(1){
        menu_adm();
        scanf("%d", &escolha);
        switch(escolha){
        case 1:
             alterar_cad();
        }
    }

}

void alterar_cad(){
    int escolha;
    if(verifica()==0){
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

            }
        }
    }
    else{
        puts("cfp não encontrado no sistema");
    }
}

usuario define_adm(){
    usuario adm;

    puts("percebemos que ainda não possue o login de administrador.");
    puts("defina os campos");
    printf("Nome: ");
    scanf("%s", &adm.nome);
    printf("Senha: ");
    scanf("%s", &adm.senha);
    return adm;
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    usuario adm, usuario_novo;
    int entrada;
    while(1){
        FILE *fp;
        char len;
        char palavra[10];
        char cpfs[tam][12];
        int quantidade = 0;
        inicio();
        scanf("%d", &entrada);

        if(entrada==1){
        fp = fopen("adms.txt", "r");
        if(fp == NULL) {
            puts("erro ao abrir o arquivo.");
            exit(1);
        }
        while ((len = fgetc(fp)) != EOF) {
            if (len == '#') {
                adm = define_adm();
            }
        }
        fclose(fp);
        fp = fopen("adms.txt", "w");
        if(fp == NULL){
            puts("erro ao abrir o arquivo.");
            exit(1);
        }
        fprintf(fp,"\nADMINISTRADOR\nnome: %s\nsenha: %s\n", adm.nome, adm.senha);
        fclose(fp);

        login_admistrador(adm);

        }

        else if(entrada==2){
            fp = fopen("arquivo.txt", "r");
            if(fp == NULL){
                puts("erro ao abrir o arquivo.");
                exit(1);
            }
            while (!feof(fp)) {
                fscanf(fp, "%s", &palavra);
                if (strcmp(palavra, "CPF:") == 0) {
                    fscanf(fp, "%s", &cpfs[quantidade]);
                        quantidade++;
                }
            }
            fclose(fp);
            if (verifica(cpfs) == 1) {
                printf("cadastro pendente! aguarde!\n");
                usuario_novo = dados();
                fp = fopen("arquivo.txt", "a");
                if (fp == NULL) {
                    puts("Impossível gravar no arquivo!");
                    exit(1);
                }
                if (quantidade == 0){
                    fprintf(fp,"______________lista de cadastros realizados______________\n");
                }
                fprintf(fp,"\nusuario %d\nnome: %s\nCPF: %s\nsenha: %s\n", quantidade+1, usuario_novo.nome, usuario_novo.cpf, usuario_novo.senha);

                fclose(fp);
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
