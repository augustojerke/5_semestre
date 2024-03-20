//Augusto, Fabrício e Lorenzo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listadeCompra
{
    int codigo;
    char nome_produto[50];
    int quantidade;
    float preco;

} ListadeCompra;

void mostraMenu()
{
    printf("1 - Adicionar Item na Lista\n");
    printf("2 - Mostrar Item na Lista\n");
    printf("3 - Sair\n\n");
    printf("Digite uma Opcao: ");
}

void initLista(int tam, ListadeCompra *vetorLista)
{
    for (int i = 0; i < tam; i++)
    {
        vetorLista[i].codigo = 0;
        strcpy(vetorLista[i].nome_produto, "Nao Informado");
        vetorLista[i].preco = 0;
        vetorLista[i].quantidade = 0;
    }
}

void mostrarLista(int tam, ListadeCompra *vetorLista)
{
    system("cls");
    for (int i = 0; i < tam; i++)
    {
        printf("PRODUTO %d: \n\n", i + 1);
        printf("Codigo: %d\n", vetorLista[i].codigo);
        printf("Nome: %s\n", vetorLista[i].nome_produto);
        printf("Quantidade: %d\n", vetorLista[i].quantidade);
        printf("Valor: %f\n", vetorLista[i].preco);
        printf("--------------------\n");
    }
    printf("\n\n");
}

void incluirItem(int *tamLista, ListadeCompra *vetorLista)
{
    system("cls");
    ListadeCompra listaIncluir;

    printf("Digite o Codigo do Produto: \n");
    scanf("%d", &listaIncluir.codigo);
    printf("Digite o Nome do Produto: \n");
    scanf("%s", listaIncluir.nome_produto);
    fflush(stdin);
    printf("Digite a Quantidade do produto: \n");
    scanf("%d", &listaIncluir.quantidade);
    printf("Digite o Valor do Produto: ");
    scanf("%f", &listaIncluir.preco);

    vetorLista[*tamLista] = listaIncluir;
    (*tamLista)++;
    system("cls");
}

int main()
{
    int tam;
    printf("Digite o tamanho da Lista de Compras: ");
    scanf("%d", &tam);
    ListadeCompra *vetorLista = (ListadeCompra *)malloc(tam * sizeof(ListadeCompra));
    system("cls");
    int tamanhoLista = 0;
    initLista(tam, vetorLista);

    while (1)
    {
        int opc;
        mostraMenu();
        scanf("%d", &opc);

        switch (opc)
        {
            case 1:
                incluirItem(&tamanhoLista, vetorLista);
                break;
            case 2:
                mostrarLista(tam, vetorLista);
                break;
            case 3:
                free(vetorLista);
                return 0;
            default:
                continue;
        }
    }
    printf("Fim do Programa!");
}
