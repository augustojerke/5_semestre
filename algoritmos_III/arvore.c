#include <stdio.h>
#include <stdlib.h>

typedef struct Piloto {
   char nome[60];
   int pontos;
} Piloto;

typedef struct NoS {  
   Piloto piloto; 
   struct NoS *esquerda, *direita;                   
} No;

typedef struct {      
   No *raiz;
   int tamanho;
} Arvore;

void mostraMenu()
{
   printf("\n\n---- ARVORE BINARIA -----");
   printf("\n----: 1 - Inserir\n----: 2 - Verifica se Existe\n----: 3 - Excluir\n----: 4 - Tamanho\n----: 5 - Em Ordem\n----: 6 - Pre-Ordem\n----: 7 - Pos-Ordem\n----: 0 - SAIR");
   printf("\n----> Digite uma opcao: ");
}

Arvore* inicializarArvore()
{
    Arvore *novaArvore = (Arvore*)malloc(sizeof(Arvore));
    novaArvore->raiz = NULL;
    novaArvore->tamanho = 0;
    return novaArvore;
}

No* encontrarPai(Arvore *arvore, Piloto piloto, int inserir, int *encontrou)
{
   No *p = arvore->raiz, *pai = NULL;
               
   while (p != NULL && (inserir || p->piloto.nome != piloto.nome))        
   {
      pai = p;
      if(piloto.pontos <= p->piloto.pontos)
         p = p->esquerda;
      else
         p = p->direita;
   }
   if(p == NULL)
      *encontrou = 0;
   else
      *encontrou = 1;
   return pai;
}

No* buscar(Arvore *arvore, char piloto[60])
{
   int found;
   No *pai = searchParent(arvore, piloto, 0, &found), *p = NULL;             

   if(found){
      if(pai == NULL)
         p = arvore->raiz;
      else if(piloto.nome == pai->esquerda->piloto.nome)
         p = pai->esquerda;
      else
         p = pai->direita;
   }
   return p;
}

No* inserir(Arvore *arvore, Piloto piloto)
{
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->piloto = piloto;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;

    if(arvore->raiz == NULL)
        arvore->raiz = novoNo;
    else{
        int found;
        No *pai = searchParent(arvore, piloto, 1, &found);
        if(piloto.pontos <= pai->piloto.pontos)
            pai->esquerda = novoNo;
        else
            pai->direita = novoNo;
    }

    arvore->tamanho++;
    return novoNo;
}

void inOrderR(No *sraiz)
{
    if(sraiz != NULL){
      inOrderR(sraiz->esquerda);
      printf("%d", sraiz->piloto.nome);
      inOrderR(sraiz->direita);
    }
}

int main(){

   Arvore *arvore;
   int opc;
   Piloto piloto;
   No *exist;

   arvore = inicializarArvore();

   while(opc != 0)
   {
      mostraMenu();
      scanf("%d", opc);

      switch(opc)
      {
         case 1:
            printf("Digite o nome do piloto: ");
            gets(piloto.nome);
            fflush(stdin);
            print("Digite os pontos do piloto: ");
            scanf("%d", piloto.pontos);
            inserir(arvore, piloto);
            break;
         case 2:
            printf("\n-- Digite o nome do piloto: ");
            gets(piloto.nome);
            exist = buscar(arvore, piloto.nome);
            if(exist != NULL)
               printf("\n-- Elemento Exite.");
            else
               printf("\n-- Elemento nao existe.");
            break;
      }
   }

   // FILE *arquivo;
   // char linha[100];
   // char nome[20];
   // int idade;

   // arquivo = fopen("pilotos.txt", "rt");

   // if (arquivo == NULL) {
   //    printf("Erro ao abrir o arquivo.");
   //    return 1;
   // }

   // fgets(linha, 100, arquivo);

   // sscanf(linha, "%s - %d", nome, &idade);

   // printf("Nome: %s\n", nome);
   // printf("Idade: %d\n", idade);

   // fclose(arquivo);

   return 0;
}
