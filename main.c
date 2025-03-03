#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

typedef struct {
    const char* cidades[4];
    int num_cidades;
} TCidade;

typedef struct no {
    int cidade_aleatoria;
    int evento_aleatorio;
    TCidade cidade;
    struct no *direita, *esquerda;
} NoArvore;

void Inserir_cidade(NoArvore** raiz, int cidade_aleatoria, TCidade c);
void Cidade_aleatoria(NoArvore** raiz, TCidade c);

void Cidade_aleatoria(NoArvore** raiz, TCidade c) {
    int cidade_aleatoria[c.num_cidades];
    int qtd_inserida = 0;

    while (qtd_inserida < c.num_cidades) {
        int nova_cidade = rand() % c.num_cidades;
        int repetido = 0;

        for (int j = 0; j < qtd_inserida; j++) {
            if (cidade_aleatoria[j] == nova_cidade) {
                repetido = 1;
                break;
            }
        }
        if (repetido == 0) {
            cidade_aleatoria[qtd_inserida] = nova_cidade;
            Inserir_cidade(raiz, nova_cidade, c);
            qtd_inserida++;
        }
    }
}

void Inserir_cidade(NoArvore** raiz, int cidade_aleatoria, TCidade c) {
    NoArvore* aux = *raiz;
    while (aux) {
        if (aux->cidade_aleatoria < cidade_aleatoria) {
            raiz = &aux->direita;
            aux = *raiz;
        } else {
            raiz = &aux->esquerda;
            aux = *raiz;
        }
    }
    aux = (NoArvore*)malloc(sizeof(NoArvore));
    aux->cidade_aleatoria = cidade_aleatoria;
    aux->cidade = c;
    aux->direita = NULL;
    aux->esquerda = NULL;
    *raiz = aux;
}

void Imprimir_preorder(NoArvore* raiz) { // [raiz] [esqerda] [direita]
    if(raiz != NULL) {
        printf("[%s] ", raiz->cidade.cidades[raiz->cidade_aleatoria]);
        Imprimir_preorder(raiz->esquerda);
        Imprimir_preorder(raiz->direita);
    }
}

void Imprimir_inorder(NoArvore* raiz) { // [esquerda] [raiz] [direita]
    if(raiz != NULL) {
        Imprimir_inorder(raiz->esquerda);
        printf("[%s] ", raiz->cidade.cidades[raiz->cidade_aleatoria]);
        Imprimir_inorder(raiz->direita);
    }
}

void Imprimir_postorder(NoArvore* raiz) { // [esquerda] [direita] [raiz]
    if(raiz != NULL) {
        Imprimir_postorder(raiz->esquerda);
        Imprimir_postorder(raiz->direita);
        printf("[%s] ", raiz->cidade.cidades[raiz->cidade_aleatoria]);
    }
}


int main() {
    setlocale(LC_ALL,"portuguese");
    srand(time(NULL));

    NoArvore* raiz = NULL;
    TCidade c = {
        .cidades = {"Nova Era", "João Monlevade", "Bele Horizonte", "Ipatinga"},
        .num_cidades = 4
    };

    /*
    const char *eventos[] = {"Pagode", "Rock", "Sertanejo", "Funck"};
    int num_eventos = sizeof(eventos) / sizeof(eventos[0]);
    int evento_aleatorio = rand() % num_eventos;
    */

    Cidade_aleatoria(&raiz,c);

    Imprimir_preorder(raiz);
    printf("\n");
    Imprimir_inorder(raiz);
    printf("\n");
    Imprimir_postorder(raiz);


    return 0;
}
