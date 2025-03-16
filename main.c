#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <stdbool.h>

typedef struct {
    char* nome_evento;
    float ev_avaliacao;
} TEvento;

typedef struct {
    char* nome_cidade;
    TEvento evento;
} TCidade;

typedef struct cel{
    TCidade item;
    struct cel *pai;
    struct cel *esq;
    struct cel *dir;
} TCel;

typedef struct arvore{
    TCel *raiz;
}TArvore;

void Cidade_aleatoria(TCel** x, char* cidade[], int num_cidades);
void Inserir(TCel **x, TCel *pai, TCidade item);

void Cidade_aleatoria(TCel** x, char* cidade[], int num_cidades) {
    char* copia_cidade[num_cidades];
    int preechimento[num_cidades];
    TCidade item;
    srand(time(NULL));

    for (int i = 0; i < num_cidades; i++) {
        preechimento[i] = 0;
    }

    for (int i = 0; i < num_cidades; i++) {
        int posicao;
        do {
            posicao = rand() % num_cidades;
        } while (preechimento[posicao]);

        copia_cidade[posicao] = cidade[i];
        preechimento[posicao] = 1;
    }

    for (int i = 0; i < num_cidades; i++) {
        item.nome_cidade = copia_cidade[i];
        Inserir(x, NULL, item);
    }
}

TCel* CriaNo(TCidade item) {
    TCel *novoNo = (TCel*)malloc(sizeof(TCel));
    novoNo->item = item;
    novoNo->pai = NULL;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}

void Inserir(TCel **x, TCel *pai, TCidade item) {
    if (*x == NULL) {
        *x = CriaNo(item);
        (*x)->pai = pai;
        return;
    }
    TCel *aux = *x;
    while (aux != NULL) {
        int cmp = strcmp(item.nome_cidade, aux->item.nome_cidade);
        if (cmp < 0 || (cmp == 0)) {
            if (aux->esq == NULL) {
                aux->esq = CriaNo(item);
                aux->esq->pai = aux;
                return;
            }
            aux = aux->esq;
        } else {
            if (aux->dir == NULL) {
                aux->dir = CriaNo(item);
                aux->dir->pai = aux;
                return;
            }
            aux = aux->dir;
        }
    }
}

TCel* Pesquisar_nome(TCel *x, char* nome_cidade) {
    if (x == NULL) {
        return NULL;
    }
    int cmp = strcmp(x->item.nome_cidade, nome_cidade);
    if (cmp == 0) {
        return x;
    }
    if (cmp > 0) {
        return Pesquisar_nome(x->esq, nome_cidade);
    } else {
        return Pesquisar_nome(x->dir, nome_cidade);
    }
}

TCel *Minimo(TCel *x){         // Procuro o menor valor da minha árvore
    if(x == NULL){
        return NULL;
    }
    while(x->esq != NULL){     // Como os menores valores estão à esquerda da árvore, percorro a árvore indo à direita até que
        x = x->esq;            // o valor seja diferente de NULL, ou seja o último valor
    }
    return x;
}

void Transplante(TArvore *arvore, TCel **u, TCel **v){
    if((*u)->pai == NULL)
        arvore->raiz = (*v);
    else if ((*u) == (*u)->pai->esq)
        (*u)->pai->esq = (*v);
    else
        (*u)->pai->dir = (*v);
    if(*v != NULL)
        (*v)->pai->dir = (*u)->pai;
}

void Retirar (TArvore *arvore, TCel **z){
    if(*z == NULL){
        printf("\n>>>＞ AVISO：NO \"z\" E´ NULO! ");
        return;
    }
    if((*z)->esq == NULL)
        Transplante(arvore, z, &(*z) ->dir);
    else if( (*z)->dir == NULL)
        Transplante (arvore, z, &(*z)->esq);
    else{
        TCel *y = Minimo ((*z) ->dir);
        if(y->pai == (*z)){
            Transplante (arvore, &y, &y->dir);
            y->dir = (*z) ->dir;
            y ->dir->pai = y;
        }
        Transplante (arvore, z, &y);
        y->esq = (*z) ->esq;
        y->esq->pai = y;
    }
    free (*z);
    *z = NULL;
}

/*
void Bubblesort(TCidade C[], int n){
    TCidade x;
    int i, j;
    for(i = 1; i < n; i++){
        for(j = n; j > i; j--){
            if(C[j].id > C[j - 1].id){
                x = C[j];
                C[j] = C[j - 1];
                C[j - 1] = x;
            }
        }
    }
}

void SelectionSort(TCidade*C, int n){
    int i, j, Max;
    TCidade x;
    for(i = 1; i <= n - 1; i++){
        Max = i;
        for(j = i + 1; j <= n; j++)
            if(C[j].id > C[Max].id){
                Max = j;
            }
        x = C[Max];
        C[Max] = C[i];
        C[i] = x;
    }
}

void InsertionSort(TCidade *C, int n){
    int i, j;
    TCidade x;
    for(i = 2; i <= n; i++){
        x = C[i];
        j = i - 1;
        C[0] = x;
        while(x.id > C[j].id){
            C[j + 1] = C[j];
            j--;
        }
        C[j + 1] = x;
    }
}

void ShellSort(TCidade *C, int n){
    int i, j, h = 1;
    TCidade x;
    do{
        h = h * 3 + 1;
    } while(h < n);
    do{
        h /= 3;
        for(i = h + 1; i <= n; i++){
            x = C[i];
            j = i;
            while(C[j - h].id < x.id){
                C[j] = C[j - h];
                j -= h;
                if(j <= h)
                    break;
            }
            C[j] = x;
        }
    } while(h != 1);
}

int Particao(TCidade *C, int p, int r) {
    TCidade x = C[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (C[j].id >= x.id) {
            i++;
            TCidade aux = C[i];
            C[i] = C[j];
            C[j] = aux;
        }
    }
    TCidade aux = C[i + 1];
    C[i + 1] = C[r];
    C[r] = aux;
    return i + 1;
}

void QuickSort(TCidade *C, int p, int r){
    if(p < r){
        int q = Particao(C, p, r);
        QuickSort(C, p, q - 1);
        QuickSort(C, q + 1, r);
    }
}

void Merge(TCidade *C, int l, int m, int r){
    int n1 = m - l + 1;
    int n2 = r - m;
    TCidade L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = C[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = C[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].id >= R[j].id) {
            C[k] = L[i];
            i++;
        } else {
            C[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        C[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        C[k] = R[j];
        j++;
        k++;
    }
}

void Mergesort(TCidade *C, int l, int r) {
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    Mergesort(C, l, m);
    Mergesort(C, m + 1, r);
    Merge(C, l, m, r);
}

void MaxHeapify(TCidade *C, int i, int n){
    TCidade aux; int esq = 2*i; int dir = 2*i+1; int menor;
    if((C[i].id > C[esq].id) && (esq <= n) && esq >= 1)
        menor = esq;
    else
        menor = i;
    if((C[menor].id > C[dir].id) && (dir <= n) && dir >= 1)
        menor = dir;
    if(menor != i){
        aux = C[menor];
        C[menor] = C[i];
        MaxHeapify(C, menor, n);
    }
}

void BuildMaxHeap(TCidade *C, int n){
    int i;
    for(i = n/2; i > 0; i--){
        MaxHeapify(C, i, n);
    }
}

void HeapSort(TCidade *C, int n) {
    TCidade aux;
    int tam = n;
    BuildMaxHeap(C, n);
    for (int i = n; i >= 2; i--) {
        aux = C[1];
        C[1] = C[i];
        C[i] = aux;
        tam--;
        MaxHeapify(C, 1, tam);
    }
}
*/

// Impressão das cidades
void Imprimir_cidades(TCel *x){
    if(x != NULL){
        Imprimir_cidades(x->esq);
        printf("%s, ", x->item.nome_cidade);
        Imprimir_cidades(x->dir);
    }
}

// Caminhamento InOrdem, Pre e Pos
void InOrdem(TCel *x){
    if(x != NULL){
        InOrdem(x->esq);
        printf("[%s] -> ", x->item.nome_cidade);
        InOrdem(x->dir);
    }
}
void PreOrdem(TCel *x){
    if(x != NULL){
        printf("[%s] -> ", x->item.nome_cidade);
        PreOrdem(x->esq);
        PreOrdem(x->dir);
    }
}
void PosOrdem(TCel *x){
    if(x != NULL){
        PosOrdem(x->esq);
        PosOrdem(x->dir);
        printf("[%s] -> ", x->item.nome_cidade);
    }
}


int main() {
    setlocale(LC_ALL,"portuguese");

    TArvore arvore;
    arvore.raiz = NULL;

    char *cidade[] = {"Nova Era", "Joao Monlevade", "Ipatinga", "Belo Horizonte", "Itabira"};
    int num_cidade = sizeof(cidade) / sizeof(cidade[0]);
    Cidade_aleatoria(&arvore.raiz, cidade, num_cidade);

    printf("Cidades: ");
    Imprimir_cidades(arvore.raiz);
    printf("\n");
    printf("\n");
    printf("Pre-Order: ");
    PreOrdem(arvore.raiz);
    printf("\n");
    printf("In-Order: ");
    InOrdem(arvore.raiz);
    printf("\n");
    printf("Pos-Order: ");
    PosOrdem(arvore.raiz);
    printf("\n");
    printf("\n");

    int escolha;
    TCel* pesquisa = NULL;
    TCidade i, c;
    bool loop = true;

    printf("ARVORE BINARIA");
    while(loop) {
        printf("\n\t1. Pesquisa pelo NOME\n\t2. Sair");
        printf("\nEscolha: ");
        scanf("%d", &escolha);
        getchar();
        switch (escolha) {
            case 1:
                printf("Digite o NOME da cidade que deseja verificar se ha na arvore: ");
                char nome[100];
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                pesquisa = Pesquisar_nome(arvore.raiz, nome);
                if (pesquisa != NULL){
                    printf("O NOME [%s] foi encontrado na arvore!\n", pesquisa->item.nome_cidade);
                }else {
                    printf("O NOME [%s] nao foi encontrado na arvore!\n", nome);
                }
                break;
            case 2:
                printf("Saindo...\n");
                loop = false;
                break;
            default:
                printf("Erro de digitacao! Digite novamente!\n");
        }
    }



    return 0;
}
