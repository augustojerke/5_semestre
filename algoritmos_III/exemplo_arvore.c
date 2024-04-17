#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct NodeTypeS {   // projetando o nó
    ElemType element; 
    struct NodeTypeS    *left, 
                        *right;
} NodeType;

typedef struct {       // referencia a raiz e ao tamanho
    NodeType *root;
    int size; // altura, profundidade
} TreeType;

TreeType* initialize()
{
    TreeType *newTree = (TreeType*)malloc(sizeof(TreeType));
    newTree->root = NULL;
    newTree->size = 0;
    return newTree;
}

// operação de busca - encontrar o pai do elemento onde quero incluir
NodeType* searchParent(TreeType *tree, ElemType element, int forInsert, int *Found)
{
    //Questão: a árvore pode aceitar nós repetidos ou não?
    NodeType    *p = tree->root,
                *parent = NULL;
    while (p != NULL &&
            (forInsert || p->element != element)) // rep até achar o elemento
    {
        parent = p; // quardo o pai antes de descer
        if(element <= p->element)
            p = p->left;
        else
            p = p->right;
    }
    if(p == NULL)
        *Found = 0;
    else
        *Found = 1;
    return parent;
}
// operação de busca simples
NodeType* search(TreeType *tree, ElemType element)
{
    int found;
    NodeType *parent = searchParent(tree, element, 0, &found),
             *p = NULL;

    if(found){
        if(parent == NULL)
            p = tree->root;
        else if(element == parent->left->element)
            p = parent->left;
        else
            p = parent->right;
    }
    return p;
}
// função inserir nó na arvore
NodeType* insert(TreeType *tree, ElemType element)
{
    NodeType *newNode = (NodeType*)malloc(sizeof(NodeType));
    newNode->element = element;
    newNode->left = NULL;
    newNode->right = NULL;

    if(tree->root == NULL)
        tree->root = newNode;
    else{
        int found;
        NodeType *parent = searchParent(tree, element, 1, &found);
        if(element <= parent->element)
            parent->left = newNode;
        else
            parent->right = newNode;
    }

    tree->size++; // nro de nós e não nro de níveis...???
    return newNode;
}

// - BUSCAR: Em Ordem, Pré-Ordem e Pós-Ordem

void inOrderR(NodeType *sroot) // recursivo
{
    if(sroot != NULL){
      inOrderR(sroot->left);
      printf("%d", sroot->element);
      inOrderR(sroot->right);
    }
}

void inOrder(TreeType *tree)
{
	// // desenvolver    
}

void main()
{
    TreeType *tree;
    int action;
    ElemType input;
    NodeType *exist;

    tree = initialize();

    do{
        printf("\n\n---- ARVORE BINARIA -----");
        printf("\n----: 1 - Inserir\n----: 2 - Verifica se Existe\n----: 3 - Excluir\n----: 4 - Tamanho\n----: 5 - Em Ordem\n----: 6 - Pre-Ordem\n----: 7 - Pos-Ordem\n----: 0 - SAIR");
        printf("\n----> Digite uma opcao: ");
        scanf("%d",&action);

        switch(action){
            case 1:
                printf("\n-- Digite um numero: ");
                scanf("%d",&input);
                insert(tree, input);
                break;
            case 2:
                printf("\n-- Digite o Elemento: ");
                scanf("%d", &input);
                exist = search(tree, input);
                if(exist != NULL)
                    printf("\n-- Elemento Exite.");
                else
                    printf("\n-- Elemento nao existe.");
                break;
            case 3:
                //----
                break;
            case 4:
                //printf("\n-- Tamanho da arvore eh: %d", size(tree));
                break;
            case 5:
                inOrderR(tree->root);
                break;
            case 6:
                //preOrder(tree);
                break;
            case 7:
                //posOrder(tree);
                break;
            case 0: break;
            default :
                printf("\n-- Opcao invalida....");
        }

    }while(action != 0);
}