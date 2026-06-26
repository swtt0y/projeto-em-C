#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct {
    char nome[10];
    char senha[15];
}adm;

typedef struct usuario{
    char nome[25];
    char cpf[12];
    char senha[15];
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

void salva_usuario(usuario *usuarios){
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

void salva_adm(adm *adm){
    FILE *fp;
    fp = fopen("adms.txt", "w");
    if(fp==NULL){
        puts("erro ao abrir o arquivo");
        exit(1);
    }
    fprintf(fp,"\nADMINISTRADOR\nnome: %s\nsenha: %s\n", adm->nome, adm->senha);
    fseek(fp, 70, SEEK_END);
    fclose(fp);
}

int inicio(){
    int entrada;
    puts("//////////////////////////\n");
    puts("sistema de cadastro e busca\n");
    puts("//////////////////////////\n");
    puts("bem-vindo!");
    puts("qual sera o modo de acesso?");
    puts("1. admistrador");
    puts("2. usuario");
    puts("aperta 0 para parar o programa");
    scanf("%d", &entrada);
    return entrada;
}

void menu_adm(){
    puts("o que deseja fazer como adm?");
    puts("1. mudar cadastro de algum usuario");
    puts("2. mudar cadastro de adm");
    puts("3. sair do modo adm");
    puts("4. adicionar cadastro");
    puts("5. sair do sistema");
}
void menu_usuario(){
    puts("o que deseja fazer em sua conta?");
    puts("1. mudar meu cadastro");
    puts("2. sair do sistema");
}

usuario* verifica(usuario *usuarios, char cpf[12]){
    usuario *no;
    no = usuarios->pont;
    while(no != NULL){
        if (strcmp(cpf, no->cpf) == 0){
            return no;
        }
        no = no->pont;
    }
    return NULL;
}

void dados(usuario *usuarios) {
    usuario *novo;
    novo = (usuario*) malloc(sizeof(usuario));
    printf("defina o cadastro\n");
    printf("qual o nome?");
    scanf("%s", novo->nome);
    printf("qual o cpf? ");
    scanf("%s", novo->cpf);
    printf("qual será a senha?");
    scanf("%s", novo->senha);
    puts("cadastro realizado com sucesso!");
    novo->pont = usuarios->pont;
    usuarios->pont = novo;
    salva_usuario(usuarios);
}

void alterar_cad(usuario *usuarios, char cpf[12]){
    //falta o dps de adm e do usuario
    usuario *no;
    no = verifica(usuarios, cpf);
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
        puts("0. voltar");
        scanf("%d", &escolha);
         switch(escolha){
            case 0:
                break;
            case 1:
                printf("novo nome: ");
                scanf("%s", no->nome);
                salva_usuario(usuarios);
                puts("alteração salva com sucesso!");
                break;
            case 2:
                printf("novo CPF: ");
                scanf("%s", no->cpf);
                salva_usuario(usuarios);
                puts("alteração salva com sucesso!");
                break;
            case 3:
                printf("nova senha: ");
                scanf("%s", no->senha);
                salva_usuario(usuarios);
                puts("alteração salva com sucesso!");
                break;
            case 4:
                printf("novo nome: ");
                scanf("%s", no->nome);
                printf("novo CPF: ");
                scanf("%s", no->cpf);
                printf("nova senha: ");
                scanf("%s", no->senha);
                salva_usuario(usuarios);
                puts("alterações salvas com sucesso!");
                break;
            default:
                puts("opção invalida");
            }
            break;
        }
}
void alterar_adm(adm *adm){
    int escolha;
    while(1){
        puts("o que deseja alterar nas credenciais do adm?");
        puts("1. nome");
        puts("2. senha");
        puts("3. todos");
        puts("0. voltar para inicio");
        scanf("%d", &escolha);
        switch(escolha){
        case 0:
            break;
        case 1:
            printf("digite o novo nome: ");
            scanf("%s", adm->nome);
            salva_adm(adm);
            puts("alteração salva com sucesso!");
            break;
        case 2:
            printf("digite a nova senha: ");
            scanf("%s", adm->senha);
            salva_adm(adm);
            puts("alteração salva com sucesso!");
            break;
        case 3:
            printf("digite o novo nome: ");
            scanf("%s", adm->nome);
            printf("digite a nova senha: ");
            scanf("%s", adm->senha);
            salva_adm(adm);
            puts("alterações salvas com sucesso!");
            break;
        default:
            puts("opção invalida!");
        }
        break;
    }
}
void login_admistrador(adm *adm, usuario *usuarios){
    char nome[10], senha[15], cpf[12];
    int escolha;
    puts("\nfaça o login exclusivo do administrador");
    printf("nome: ");
    scanf("%s", nome);
    printf("senha: ");
    scanf("%s", senha);
    while(1){
        if (strcmp(adm->nome, nome) == 0) {
          if (strcmp(adm->senha, senha) == 0) {
            puts("Login realizado com sucesso!");
            menu_adm();
            scanf("%d", &escolha);
            switch(escolha){
            case 1:
               printf("digite o cpf para verificar no sistema: ");
               scanf("%s", cpf);
               alterar_cad(usuarios, cpf);
               break;
            case 2:
               alterar_adm(adm);
               break;
            case 3:
               break;
            case 4:
               dados(usuarios);
               return; //volta para o inicio
            case 5:
               puts("desconectanto do sistema");
               exit(1);
               break;
            }
          }
          else {
            puts("senha incorreta!tente novamente.");
            return;
          }
        }
        else {
          puts("nome incorreto!tente novamente.");
          return;
        }
        break;
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

void login_usuario(usuario *usuarios){
    char cpf[12];
    printf("digite seu cpf para que verifique no sistema: ");
    scanf("%s", cpf);
    usuario *no;
    no = verifica(usuarios, cpf);
    char senha[15];
    int escolha;
     if (no == NULL) {
        printf("cadastro pendente! aguarde!\n");
        dados(usuarios);
     }
     else{
        puts("cadastro já está no sistema!");
        printf("confirme sua identidade com a senha: ");
        scanf("%s", senha);
        if(strcmp(no->senha, senha) == 0){
            while(1){
              menu_usuario();
              scanf("%d", &escolha);
              switch(escolha){
              case 1:
                  alterar_cad(usuarios, cpf);
                  break;
              case 2:
                puts("desconectanto do sistema");
                exit(1);
                break;
              }
              break;
            }
        }
        else{
            puts("senha incorreta! refaça o processo.");
        }
     }
}

void inicial(adm *adm, usuario *usuarios){
    int entrada;
    carregar(usuarios);
    while(1){
        FILE *fp;
        char palavra[30];
        entrada=inicio();
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
            salva_adm(adm);
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
            login_usuario(usuarios);
        }
        else if(entrada==0){
            puts("saindo do sistema");
            break;
        }

        else{
            puts("não tem essa opção");
        }
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    adm Adm;
    adm *adm = &Adm;
    usuario *usuarios = lista_usuarios();
    inicial(adm, usuarios);
    return 0;
}
