#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Piloto {
   char nome[60];
   int pontos;
} Piloto;

typedef struct NoS {  
   Piloto piloto; 
   struct NoS *esquerda, *direita, *pai;
   int altura;                   
} No;

typedef struct {      
   No *raiz;
   int tamanho;
} Arvore;

void mostraMenu()
{
   printf("\n\n---- ARVORE BINARIA -----");
   printf("\n----: 1 - Inserir\n----: 2 - Verifica se Existe\n----: 3 - Excluir\n----: 4 - Em Ordem\n----: 5 - Pre-Ordem\n----: 6 - Pos-Ordem\n----: 7 - Imprimir Arvore\n----: 8 - Inserir Arvore pelo Arquivo\n----: 0 - SAIR");
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
               
   while (p != NULL && (inserir || strcmp(p->piloto.nome, piloto.nome) != 0))        
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

No* buscar(Arvore *arvore, Piloto piloto)
{
   int found;
   No *pai = encontrarPai(arvore, piloto, 0, &found), *p = NULL;             

   if(found){
      if(pai == NULL){
         p = arvore->raiz;
      }         
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

    if(arvore->raiz == NULL){
         novoNo->altura = 0;
         novoNo->pai = NULL;
         arvore->raiz = novoNo;
    }                
    else{
        int found;
        No *pai = encontrarPai(arvore, piloto, 1, &found);
        novoNo->altura = pai->altura + 1;
        novoNo->pai = pai;
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
      printf("%s ", sraiz->piloto.nome);
      inOrderR(sraiz->direita);
    }
}

void imprimirArvore(No *raiz, int nivel) {
    if (raiz == NULL)
        return;
    nivel += 5;

    imprimirArvore(raiz->direita, nivel);

    printf("\n");
    for (int i = 5; i < nivel; i++)
        printf(" ");
    printf("%s - %d\n", raiz->piloto.nome, raiz->piloto.pontos);

    imprimirArvore(raiz->esquerda, nivel);
}

void inserirArvoreArquivo(Arvore *arvore){
   FILE *arquivo;
   char linha[100];
   char nome[60];
   int pontos;

   arquivo = fopen("pilotos.txt", "rt");

   if (arquivo == NULL) {
      printf("Erro ao abrir o arquivo.");
      return;
   }

    while (fgets(linha, 100, arquivo) != NULL) {
       sscanf(linha, "%s - %d", nome, &pontos);
	   Piloto novopiloto;
	   strcpy(novopiloto.nome, nome);
	   novopiloto.pontos = pontos;
	   inserir(arvore, novopiloto);
   }

   fclose(arquivo);
}

int main(){

   Arvore *arvore;
   int opc = 1;
   Piloto piloto;
   No *exist;

   arvore = inicializarArvore();

   while(opc != 0)
   {
      mostraMenu();
      scanf("%d", &opc);

      switch(opc)
      {
         case 1:            
            printf("--Digite o nome do piloto: ");
            fflush(stdin);
            fgets(piloto.nome, sizeof(piloto.nome), stdin);
            piloto.nome[strcspn(piloto.nome, "\n")] = '\0';
            printf("--Digite os pontos do piloto: ");
            scanf("%d", &piloto.pontos);
            inserir(arvore, piloto);
            system("cls");
            printf("-- Incluido piloto %s - pontos %d", piloto.nome, piloto.pontos);
            break;
         case 2:
            printf("\n-- Digite o nome do piloto: ");
            fflush(stdin);
            fgets(piloto.nome, sizeof(piloto.nome), stdin);
            piloto.nome[strcspn(piloto.nome, "\n")] = '\0';
            printf("-- Digite os pontos do piloto: ");
            scanf("%d", &piloto.pontos);
            exist = buscar(arvore, piloto);
            system("cls");
            if(exist != NULL && exist->piloto.pontos == piloto.pontos)
            {  
               printf("\n-- Piloto Exite.");
               printf("\n\n-- Nome: %s", exist->piloto.nome);
               printf("\n-- Pontos: %d", exist->piloto.pontos);
               printf("\n-- Altura na arvore: %d", exist->altura);
               if(exist->pai != NULL)
                  printf("\n-- Pai: %s - %d pontos", exist->pai->piloto.nome, exist->pai->piloto.pontos);
               if(exist->esquerda != NULL)
                  printf("\n-- Filho esq: %s - %d pontos", exist->esquerda->piloto.nome, exist->esquerda->piloto.pontos);
               if(exist->direita != NULL)
                  printf("\n-- Filho dir: %s - %d pontos", exist->direita->piloto.nome, exist->direita->piloto.pontos);
            }               
            else
               printf("\n-- Piloto nao existe.");
            break;
         case 4:
         	system("cls");
         	inOrderR(arvore->raiz);
         	break;
         case 7: 
            system("cls");
            imprimirArvore(arvore->raiz, 0);
            break;
         case 8: 
            system("cls");
            inserirArvoreArquivo(arvore);
            printf("Dados inseridos");
            break;
      }
   }

   return 0;
}
