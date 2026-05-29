#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define tam 10

typedef struct {
    char nome[10];
    char cpf[12];
    char senha[12];

}usuario;

usuario user[tam]={0};
usuario *pont = user;

void inicio(int entrada){
    puts("//////////////////////////\n");
    puts("sistema de cadastro e busca\n");
    puts("//////////////////////////\n");
    puts("bem-vindo!");
    puts("qual sera o modo de acesso?");
    puts("1. admistrador");
    puts("2. usuario");
    scanf("%d", &entrada);
}

void define_adm(){
    int id, senha;
    puts("percebemos que ainda não possue o login de administrador.");
    puts("defina os campos");
    printf("id: ");
    scanf("%d", &id);
    printf("senha: ");
    scanf("%d", &senha);
}
int verifica(){
    char num_cpf[12];
    puts("digite seu cpf para que verifique no sistema: ");
    scanf("%s", num_cpf);
    for(int i=0; i<tam; i++){
        if(strcmp(num_cpf,pont[i].cpf)==0){
            printf("cadastro ja no sistema!");
            return 0;
        }
    }
    return 1;
}

void dados(usuario *pont, int i){
    printf("defina seu cadastro\n");
    printf("qual o seu nome? ");
    scanf("%s", pont[i].nome);
    printf("qual o seu cpf? ");
    scanf("%s", pont[i].cpf);
    printf("qual será a sua senha? ");
    scanf("%s", pont[i].senha);
    getchar();
    puts("cadastro realizado com sucesso!");
}

void admistrador(){
    int id;
    char senha_adm;
    puts("\nfaça o login exclusivo do administrador");
    printf("id: ");
    scanf("%d", &id);
    printf("senha: ");
    scanf("%c", senha_adm);
}

int main(){
    usuario user0[tam]={0};
    usuario *pont0 = user0;
    int i=0, j, entrada0;
    int retorno = verifica();
    if(retorno==1){
      printf("cadastro pendente! aguarde!\n");
      dados(pont0, i);
      i++;
    }
    j=i-1;
    FILE *fp;
    char len;
    fp=fopen("arquivo.txt", "w");
    if(fp==NULL){
        puts("erro ao abrir o arquivo.");
        exit(1);
    }
    inicio(entrada0);
    if(entrada0==1){
        while ((len=fgetc(fp))!=EOF){
            if(len=' '){
                define_adm();
            }
        }
    }
    fprintf(fp,"______________lista de cadastros realizados______________\n");
    if(i>0){
      fprintf(fp,"\nusuario %d\nnome:%s\nCPF:%s\nsenha:%s", j, pont0->nome, pont0->cpf, pont0->senha);
    }
    fclose(fp);
    return 0;
}
