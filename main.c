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
    TEvento evento[5];
    int qtd_eventos;
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
void Inserir(TCel **x, TCel *pai, TCidade item);

void Cidade_aleatoria(TCel** x, char* cidade[], int num_cidades) {
    char* copia_cidade[num_cidades];
    int preechimento[num_cidades];
    TCidade item;

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

void Evento_aleatorio(TCel* x, char* eventos[], int num_eventos) {
    if (x == NULL)
        return;

    int num = (rand() % 5) + 1;
    x->item.qtd_eventos = num;

    int preechimento[num_eventos];
    for (int i = 0; i < num_eventos; i++) {
        preechimento[i] = 0;
    }

    for (int i = 0; i < num; i++) {
        int indice;
        do {
            indice = rand() % num_eventos;
        } while (preechimento[indice]);

        x->item.evento[i].nome_evento = eventos[indice];
        x->item.evento[i].ev_avaliacao = ((float)rand() / RAND_MAX) * 10.0;
        preechimento[indice] = 1;
    }

    Evento_aleatorio(x->esq, eventos, num_eventos);
    Evento_aleatorio(x->dir, eventos, num_eventos);
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

void BubbleSort(TCel* x) {
    if (x == NULL) {
        return;
    }

    TEvento eventos[5];
    int qtd_eventos = x->item.qtd_eventos;
    for (int i = 0; i < qtd_eventos; i++) {
        eventos[i] = x->item.evento[i];
    }

    for (int k = qtd_eventos - 1; k > 0; k--) {
        for (int j = 0; j < k; j++) {
            if (eventos[j].ev_avaliacao < eventos[j + 1].ev_avaliacao) {
                TEvento aux = eventos[j];
                eventos[j] = eventos[j + 1];
                eventos[j + 1] = aux;
            }
        }
    }

    printf("\n%s:\n", x->item.nome_cidade);
    for (int i = 0; i < qtd_eventos; i++) {
        printf("\t%s - %.2f\n", eventos[i].nome_evento, eventos[i].ev_avaliacao);
    }
    printf("\n");
    BubbleSort(x->esq);
    BubbleSort(x->dir);
}

void SelectionSort(TCel* x){
    if (x == NULL) {
        return;
    }

    TEvento eventos[5];
    int qtd_eventos = x->item.qtd_eventos;
    for (int i = 0; i < qtd_eventos; i++) {
        eventos[i] = x->item.evento[i];
    }

    for(int i = 0; i < qtd_eventos - 1; i++){
        int Max = i;
        for(int j = i + 1; j < qtd_eventos; j++)
            if(eventos[j].ev_avaliacao > eventos[Max].ev_avaliacao){
                Max = j;
        }
        if (eventos[i].ev_avaliacao != eventos[Max].ev_avaliacao) {
            TEvento aux = eventos[Max];
            eventos[Max] = eventos[i];
            eventos[i] = aux;
        }
    }

    printf("\n%s:\n", x->item.nome_cidade);
    for (int i = 0; i < qtd_eventos; i++) {
        printf("\t%s - %.2f\n", eventos[i].nome_evento, eventos[i].ev_avaliacao);
    }
    printf("\n");
    SelectionSort(x->esq);
    SelectionSort(x->dir);
}

void InsertionSort(TCel* x){
    if (x == NULL) {
        return;
    }

    TEvento eventos[5];
    int qtd_eventos = x->item.qtd_eventos;
    for (int i = 0; i < qtd_eventos; i++) {
        eventos[i] = x->item.evento[i];
    }

    for(int i = 1; i < qtd_eventos; i++){
        TEvento aux = eventos[i];
        int j = i - 1;
        while((j >= 0) && (eventos[j].ev_avaliacao < aux.ev_avaliacao)){
            eventos[j + 1] = eventos[j];
            j--;
        }
        eventos[j + 1] = aux;
        j++;
    }

    printf("\n%s:\n", x->item.nome_cidade);
    for (int i = 0; i < qtd_eventos; i++) {
        printf("\t%s - %.2f\n", eventos[i].nome_evento, eventos[i].ev_avaliacao);
    }
    printf("\n");
    InsertionSort(x->esq);
    InsertionSort(x->dir);
}

void ShellSort(TCel* x){
    if (x == NULL) {
        return;
    }

    TEvento eventos[5];
    int qtd_eventos = x->item.qtd_eventos;
    for (int i = 0; i < qtd_eventos; i++) {
        eventos[i] = x->item.evento[i];
    }

    int h = 1;
    do{
        h = h * 3 + 1;
    } while(h < qtd_eventos);
    do{
        h /= 3;
        for(int i = h; i < qtd_eventos; i++){
            TEvento aux = eventos[i];
            int j = i;
            while(eventos[j - h].ev_avaliacao < aux.ev_avaliacao){
                eventos[j] = eventos[j - h];
                j -= h;
            }
            eventos[j] = aux;
        }
    } while(h != 1);

    printf("\n%s:\n", x->item.nome_cidade);
    for (int i = 0; i < qtd_eventos; i++) {
        printf("\t%s - %.2f\n", eventos[i].nome_evento, eventos[i].ev_avaliacao);
    }

    ShellSort(x->esq);
    ShellSort(x->dir);
}

int Particao(TCel*x , int p, int r) {
    if (x == NULL) {
        return -1;
    }
    TEvento* eventos = x->item.evento;
    TEvento aux1 = eventos[r];
    int i = p - 1;

    for (int j = p; j < r; j++) {
        if (eventos[j].ev_avaliacao >= aux1.ev_avaliacao) {
            i++;

            TEvento aux2 = eventos[i];
            eventos[i] = eventos[j];
            eventos[j] = aux2;
        }
    }

    TEvento aux2 = eventos[i + 1];
    eventos[i + 1] = eventos[r];
    eventos[r] = aux2;

    return i + 1;
}

void QuickSort(TCel* x, int p, int r) {
    if (x == NULL || p >= r) {
        return;
    }
    int q = Particao(x, p, r);
    QuickSort(x, p, q - 1);
    QuickSort(x, q + 1, r);
}

void Imprime_QuickSort(TCel* x) {
    if (x == NULL) {
        return;
    }

    QuickSort(x, 0, x->item.qtd_eventos - 1);

    printf("\n%s:\n", x->item.nome_cidade);
    for (int i = 0; i < x->item.qtd_eventos; i++) {
        printf("\t%s - %.2f\n", x->item.evento[i].nome_evento, x->item.evento[i].ev_avaliacao);
    }
    printf("\n");
    Imprime_QuickSort(x->esq);
    Imprime_QuickSort(x->dir);
}

void Merge(TCel* x, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    TEvento L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = x->item.evento[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = x->item.evento[m + 1 + j];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].ev_avaliacao >= R[j].ev_avaliacao) {
            x->item.evento[k] = L[i];
            i++;
        } else {
            x->item.evento[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        x->item.evento[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        x->item.evento[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(TCel* x, int l, int r) {
    if (l >= r) {
        return;
    }
    int m = l + (r - l) / 2;
    MergeSort(x, l, m);
    MergeSort(x, m + 1, r);
    Merge(x, l, m, r);
}

void Imprimir_MergeSort(TCel* x) {
    if (x == NULL) {
        return;
    }
    MergeSort(x, 0, x->item.qtd_eventos - 1);

    printf("\n%s:\n", x->item.nome_cidade);
    for (int i = 0; i < x->item.qtd_eventos; i++) {
        printf("\t%s - %.2f\n", x->item.evento[i].nome_evento, x->item.evento[i].ev_avaliacao);
    }
    printf("\n");
    Imprimir_MergeSort(x->esq);
    Imprimir_MergeSort(x->dir);
}

void MaxHeapify(TCel* x, int i, int n) {
    int esq = 2 * i + 1, dir = 2 * i + 2, menor = i;

    if (esq < n && x->item.evento[esq].ev_avaliacao < x->item.evento[menor].ev_avaliacao) {
        menor = esq;
    }
    if (dir < n && x->item.evento[dir].ev_avaliacao < x->item.evento[menor].ev_avaliacao) {
        menor = dir;
    }
    if (menor != i) {
        TEvento aux = x->item.evento[i];
        x->item.evento[i] = x->item.evento[menor];
        x->item.evento[menor] = aux;

        MaxHeapify(x, menor, n);
    }
}

void BuildMaxHeap(TCel* x, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        MaxHeapify(x, i, n);
    }
}

void HeapSort(TCel* x, int n) {
    BuildMaxHeap(x, n);

    for (int i = n - 1; i >= 0; i--) {
        TEvento aux = x->item.evento[0];
        x->item.evento[0] = x->item.evento[i];
        x->item.evento[i] = aux;

        MaxHeapify(x, 0, i);
    }
}

void Imprimir_HeapSort(TCel* x) {
    if (x == NULL) {
        return;
    }
    HeapSort(x, x->item.qtd_eventos);

    printf("\n%s:\n", x->item.nome_cidade);
    for (int i = 0; i < x->item.qtd_eventos; i++) {
        printf("\t%s - %.2f\n", x->item.evento[i].nome_evento, x->item.evento[i].ev_avaliacao);
    }
    printf("\n");
    Imprimir_HeapSort(x->esq);
    Imprimir_HeapSort(x->dir);
}

// Impressão das cidades
void Imprimir_cidades(TCel *x){
    if(x != NULL){
        Imprimir_cidades(x->esq);
        printf("%s, ", x->item.nome_cidade);
        Imprimir_cidades(x->dir);
    }
}

void Imprimir_eventos(TCel *x){
    if(x != NULL){
        Imprimir_eventos(x->esq);
        printf("\n%s: \n", x->item.nome_cidade);
        for (int i = 0; i < x->item.qtd_eventos; i++) {
            if (x->item.evento[i].nome_evento != NULL) {
                printf("\n\t%s - %.2f", x->item.evento[i].nome_evento,
                       x->item.evento[i].ev_avaliacao);
            }
        }
        printf("\n");
        Imprimir_eventos(x->dir);
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
    srand(time(NULL));

    TArvore arvore;
    arvore.raiz = NULL;

    char *cidade[] = {"Nova Era", "Joao Monlevade", "Ipatinga", "Belo Horizonte", "Itabira"};
    int num_cidade = sizeof(cidade) / sizeof(cidade[0]);
    Cidade_aleatoria(&arvore.raiz, cidade, num_cidade);

    char *eventos[] = {"Festival de Musica", "Festival de Artesanato", "Show ao Vivo", "Festival Gastronomico",
    "Exposicao de Arte", "Exposicao de Museum", "Cinema ao ar Livre", "Festival de Comedia", "Festival da Cultura",
    "Exposicao de Livros", "Festival do Foclore", "Festival do Vinho", "Festival do Fogo", "Festival da Danca",
    "Exposicao Cientifica"};
    int num_eventos = sizeof(eventos) / sizeof(eventos[0]);
    Evento_aleatorio(arvore.raiz, eventos, num_eventos);

    printf("Cidades: ");
    Imprimir_cidades(arvore.raiz);
    printf("\n\n");

    printf("Eventos em: ");
    Imprimir_eventos(arvore.raiz);
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
    bool loop = true;

    while(loop) {
        printf("ARVORE BINARIA");
        printf("\n\t1. Pesquisa pelo NOME\n\t2. Visualizar metodos de ordenacao\n\t3. Sair");
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
                printf("Escolha o metodo de ordenacao:");
                printf("\n\t1. Bublle Sort\n\t2. Selection Sort\n\t3. Insertion Sort\n\t4. Shellsort\n\t5. Quixksort\n\t6. Mergesort\n\t7. Heapsort\n\t8. Sair");
                printf("\nEscolha: ");
                scanf("%d", &escolha);
                getchar();
                switch(escolha){
                    case 1:
                        printf("\nMETODO BUBBLE SORT:");
                        BubbleSort(arvore.raiz);
                        break;
                    case 2:
                        printf("\nMETODO SELECTION SORT:");
                        SelectionSort(arvore.raiz);
                        break;
                    case 3:
                        printf("\nMETODO INSERTION SORT:");
                        InsertionSort(arvore.raiz);
                        break;
                    case 4:
                        printf("\nMETODO SHELL SORT:");
                        ShellSort(arvore.raiz);
                        break;
                    case 5:
                        printf("\nMETODO QUICK SORT:");
                        Imprime_QuickSort(arvore.raiz);
                        break;
                    case 6:
                        printf("\nMETODO MERGE SORT:");
                        Imprimir_MergeSort(arvore.raiz);
                        break;
                    case 7:
                        printf("\nMETODO HEAP SORT:");
                        Imprimir_HeapSort(arvore.raiz);
                        break;
                    case 8:
                        printf("Saindo...\n");
                        return;
                        break;
                    default:
                        printf("Erro de digitacao! Digite novamente!\n");
                }
                break;
            case 3:
                printf("Saindo...\n");
                loop = false;
                break;
            default:
                printf("Erro de digitacao! Digite novamente!\n");
        }
    }

    return 0;
}
