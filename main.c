#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

typedef struct {
    int id;
    char* nome_evento;
    float ev_avaliacao;
} TEvento;

typedef struct {
    int id;
    char* nome_cidade;
    TEvento evento;
} TCidade;

typedef struct cel{
    TCidade item;
    struct cel *pai;
    struct cel *esq;
    struct cel *dir;
}TCel;

typedef struct arvore{
    TCel *raiz;
}TArvore;

void Cidade_aleatoria(TCel** x, char* cidade[], int num_cidades);
TCidade Ler_cidade(char* cidade, int id);
void Inserir(TCel **x, TCel *pai, TCidade item);

TCidade Ler_cidade(char* cidade, int id) {
    TCidade c;
    c.nome_cidade = cidade;
    c.id = id;
    return c;
}


void Cidade_aleatoria(TCel** x, char* cidade[], int num_cidades) {
    char* copia_cidade[num_cidades];
    int preechimento[num_cidades], aux;
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
        aux = rand() % 101;
        Inserir(x, NULL, Ler_cidade(copia_cidade[i], aux));
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
        if (item.id < aux->item.id) {
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

TCel *Pesqusiar(TCel *x, TCidade item){          //Pesquiso um ID de determinado valor
    if((x == NULL) || (x->item.id == item.id))   // -> caso o valor de x seja nulo ou eu já tenha achado meu item, quebro o fluxo da função
        return;
    if(item.id < x->item.id){                    // -> caso o valor do ID desejado seja menor que X restrinjo o meu processo à arvore
        Pesqusiar(x->esq, item);                 //   da esquerda e repito o processo até que ache o valor desejado
    }
    else if(item.id > x->item.id){               // -> caso o valor do ID desejado seja maior que X restrinjo o meu processo à arvore
        Pesqusiar(x->dir, item);                 //   da direita e repito o processo até que ache o valor desejado
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
    if(*z = NULL){
        printf("\n>>>＞ AVISO：NO \"z\" E´ NULO! ");
        return;
    }
    if((*z)->esq == NULL)
        Transplante(arvore, z, &(*z) ->dir);
    else if( (*z)->dir == NULL)
        Transplante (arvore, z, &(*z)->esq);
    else{
        TCel *y = Minimo ((*z) ->dir);
        if(y->pai = (*z)){
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

// Métodos de Seleção
void  BubbleSort(TCel *C, int n){

}

void SelectionSort(TCidade*C, int n){
    int i,j,Min;
    TCidade x;
    for(i = 1; i <= n - 1; i++){
        Min = i;
        for(j = i + 1; j <= n; j++)
            if(C[j].id < C[Min].id){
                Min = j;
        }
        x = C[Min];
        C[Min] = C[i];
        C[i] = x;
    }
}

void InsertionSortt(TCidade *C, int n){
    int i,j;
    TCidade x;
    for(i = 2; i <= n; i++){
        x = C[i];
        j = i - 1;
        j = i - 1;
        C[0] = x;
        while(x.id < C[j].id){
            C[j + 1] = C[j];
            j--;
        }
        C[j + 1] = x;
    }
}

void ShellSortt(TCidade *C, int n){
    int i, j; int h = 1;
    TCidade x;
    do{
        h = h * 3 + 1;
    }while(h < n);
    do{
        h /= 3;
        for(i = h + 1; i <= n; i++){
            x = C[i];
            j = i;
            while(C[j - h].id > x.id){
                C[j] = C[j - h];
                j -= h;
                if(j <= h)
                    break;
            }
            C[j] = x;
        }
    } while(h != 1);
}

void MaxHeapify(TCidade *C, int i, int n){
    TCidade aux; int esq = 2*i; int dir = 2*i+1; int maior;
    if((C[i].id < C[esq].id) && (esq <= n) && esq >= 1)
        maior = esq;
    else
        maior = i;
    if((C[maior].id < C[dir].id) && (dir <= n) && dir >= 1)
        maior = dir;
    if(maior != i){
        aux = C[maior];
        C[maior] = C[i];
        MaxHeapify(C, maior, n);
    }
}

void BuildMaxHeap(TCidade *C, int n){
    int i;
    for(i = n/2; i > 0; i--){
        MaxHeapify(C, i, n);
    }
}

void HeapSort(TCidade *C, int n){
    TCidade aux; int tam = n;
    int i;
    BuildMaxHeap(C, n);
    for(i = 1; i <= n - 1; i++){
        aux = C[1];
        C[1] = C[tam];
        tam--;
        MaxHeapify(C, 1, tam);
    }
}

int Particao(TCidade *C, int p, int r){
    int i = p - 1;
    TCidade x, aux;
    x = C[r];
    for(int j = p; j < r; j++){
        i = i + 1;
        aux = C[i];
        C[i] = C[j];
        C[j] = aux;
    }
}

void QuickSort(TCel *C, int p, int r){
    if( p < r){
        int q = Particao(C, p, r);
        QuickSort(C, p, q - 1);
        QuickSort(C, q + 1, r);
    }
}

void MergeSort(TCel *C, int n){

}


// Caminhamento InOrdem, Pre e Pos
void InOrdem(TCel *x){
    if(x != NULL){
        InOrdem(x->esq);
        printf("[%d - %s] -> ", x->item.id, x->item.nome_cidade);
        InOrdem(x->dir);
    }
}
void PreOrdem(TCel *x){
    if(x != NULL){
        printf("[%d - %s] -> ", x->item.id, x->item.nome_cidade);
        PreOrdem(x->esq);
        PreOrdem(x->dir);
    }
}
void PosOrdem(TCel *x){
    if(x != NULL){
        PosOrdem(x->esq);
        PosOrdem(x->dir);
        printf("[%d - %s] -> ", x->item.id, x->item.nome_cidade);
    }
}

int main() {
    setlocale(LC_ALL,"portuguese");

    TArvore arvore;
    arvore.raiz = NULL;

    char *cidade[] = {"Nova Era", "João Monlevade", "Ipatinga", "Belo Horizonte", "Itabira"};
    int num_cidade = sizeof(cidade) / sizeof(cidade[0]);
    Cidade_aleatoria(&arvore.raiz, cidade, num_cidade);

/*
    TCidade c1, c2, c3;
    c1.id = 3;
    c2.id = 2;
    c3.id = 1;

    Inserir(&arvore.raiz, NULL, c1);
    Inserir(&arvore.raiz, NULL, c2);
    Inserir(&arvore.raiz, NULL, c3);
*/

    printf("Pre-Order: ");
    PreOrdem(arvore.raiz);
    printf("\n");
    printf("In-Order: ");
    InOrdem(arvore.raiz);
    printf("\n");
    printf("Pos-Order: ");
    PosOrdem(arvore.raiz);


    return 0;
}
