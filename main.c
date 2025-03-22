#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

typedef struct {
    char* nome_evento;
    float ev_avaliacao;
} TEvento;

typedef struct {
    char* nome_cidade;
    TEvento* evento;
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

// Declaração das funções que serão chamadas no código
void Cidade_aleatoria(TCel** x, char* cidade[], int num_cidades);
void Inserir(TCel **x, TCel *pai, TCidade item);
void InOrdem(TCel *x, int* seta);
void PreOrdem(TCel *x, int* seta);
void PosOrdem(TCel *x, int* seta);
void Ordem_cidades(TCel *x, int* seta); 
void Exibir_mensagens(TCel* x); 

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
    x->item.evento = (TEvento*)malloc(num * sizeof(TEvento)); 
    
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

void Geracao_cidade(TArvore* arvore) {
    char *cidade[] = {"Nova Era", "João Monlevade", "Ipatinga", "Belo Horizonte", "Itabira"};
    int num_cidade = sizeof(cidade) / sizeof(cidade[0]);
    Cidade_aleatoria(&(arvore->raiz), cidade, num_cidade);
}

void Geracao_eventos(TArvore* arvore) {
    char *eventos[] = {"Festival de Música", "Festival de Artesanato", "Show ao Vivo", "Festival Gastronômico",
        "Exposição de Arte", "Exposição de Museum", "Cinema ao ar Livre", "Festival de Comédia", "Festival da Cultura",
        "Exposição de Livros", "Festival do Folclore", "Festival do Vinho", "Festival do Fogo", "Festival da Dança",
        "Exposição Científica"};
    int num_eventos = sizeof(eventos) / sizeof(eventos[0]);

    Evento_aleatorio(arvore->raiz, eventos, num_eventos);
}

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

TCel* Pesquisar_nome(TCel *x, char* nome_cidade) {
    if (x == NULL) {
        return NULL;
    }
    char aux1[50], aux2[50];
    strcpy(aux1, nome_cidade);
    strcpy(aux2, x->item.nome_cidade);

    toLowerCase(aux1);
    toLowerCase(aux2);
    int cmp = strcmp(aux2, aux1);

    if (cmp == 0) {
        return x;
    }
    if (cmp > 0) {
        return Pesquisar_nome(x->esq, nome_cidade);
    } else {
        return Pesquisar_nome(x->dir, nome_cidade);
    }
}

TEvento* Pesquisar_evento_nome(TCidade* x, char* nome_evento) {
    char aux1[50], aux2[50];
    strcpy(aux1, nome_evento);

    for (int i = 0; i < x->qtd_eventos; i++) {
        strcpy(aux2, x->evento[i].nome_evento);
        toLowerCase(aux2);

        if (strcmp(aux1,  aux2) == 0) {
            return &(x->evento[i]);
        }
    }
    return NULL;
}

TEvento Buscar_evento_avaliacao(TCidade* x, float ev_avaliacao ){
    float Aux;
    float minimo = 10;
    for(int i = 0; i < x->qtd_eventos; i++){
        Aux = fabs((ev_avaliacao) - (x->evento[i].ev_avaliacao));
        if(Aux < minimo){
            minimo = Aux;
        }
    }
    for(int i = 0; i < x->qtd_eventos; i++){
        if(fabs((ev_avaliacao) - (x->evento[i].ev_avaliacao)) == minimo){
            return x->evento[i];
        }
    }
}

int Pesquisar_evento_nome1(TCel* x, char* nome_evento) {
    if (x == NULL) {
        return 0;
    }

    char aux1[50], aux2[50];
    strcpy(aux1, nome_evento);

    int encontrado = 0;

    for (int i = 0; i < x->item.qtd_eventos; i++) {
        strcpy(aux2, x->item.evento[i].nome_evento);
        toLowerCase(aux2);

        if (strcmp(aux1,  aux2) == 0) {
            printf("\n%s:\n", x->item.nome_cidade);
            printf("\t%s - %.2f\n", x->item.evento[i].nome_evento, x->item.evento[i].ev_avaliacao);
            encontrado = 1;
        } 
    }

    int encontrado_esq = Pesquisar_evento_nome1(x->esq, nome_evento);
    int encontrado_dir = Pesquisar_evento_nome1(x->dir, nome_evento);

    return encontrado || encontrado_esq || encontrado_dir;
}

void Buscar_evento_avaliacao1(TCel* x, float ev_avaliacao){
    if (x == NULL) {
        return;
    }
    float Aux;
    float minimo = 10;

    for(int i = 0; i < x->item.qtd_eventos; i++){
        Aux = fabs((ev_avaliacao) - (x->item.evento[i].ev_avaliacao));
        if(Aux < minimo){
            minimo = Aux;
        }
    }
    for(int i = 0; i < x->item.qtd_eventos; i++){
        if(fabs((ev_avaliacao) - (x->item.evento[i].ev_avaliacao)) == minimo){
            printf("\n%s:\n", x->item.nome_cidade);
               printf("\t%s - %.2f\n", x->item.evento[i].nome_evento, x->item.evento[i].ev_avaliacao);
        }
    }

    Buscar_evento_avaliacao1(x->esq, ev_avaliacao);
    Buscar_evento_avaliacao1(x->dir, ev_avaliacao);
}

void Buscar_evento_avaliacao2(TCel* x) {
    if (x == NULL) {
        return;
    }

    int cid = 0;
    int cont = 0;

    for (int i = 0; i < x->item.qtd_eventos; i++) {
        if (x->item.evento[i].ev_avaliacao > 7) {
            if (!cid) {
                printf("\n%s:\n", x->item.nome_cidade);
                cid = 1;
            }
            printf("\t%s - %.2f\n", x->item.evento[i].nome_evento, x->item.evento[i].ev_avaliacao);
            cont = 1;
        }
    }

    Buscar_evento_avaliacao2(x->esq);
    Buscar_evento_avaliacao2(x->dir);
}


void Evento_maior_avalicao(TCel* x) {
    if (x == NULL) {
        return;
    }

    int qtd_eventos = x->item.qtd_eventos;
    TEvento *eventos = (TEvento*)malloc(qtd_eventos * sizeof(TEvento));

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
    printf("\t%s - %.2f\n", eventos[0].nome_evento, eventos[0].ev_avaliacao);
    
    Evento_maior_avalicao(x->esq);
    Evento_maior_avalicao(x->dir);
}

void Contar_eventos(TCel* x){
    if (x == NULL) {
        return;
    }
    int cont = 0;

    printf("\n%s: ", x->item.nome_cidade);
    for (int i = 0; i <  x->item.qtd_eventos; i++) {
        cont++;
    }
    printf("%d eventos na cidade\n", cont);

    Contar_eventos(x->esq);
    Contar_eventos(x->dir);
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

    int qtd_eventos = x->item.qtd_eventos;
    TEvento *eventos = (TEvento*)malloc(qtd_eventos * sizeof(TEvento));

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
    printf("\t%s - %.2f - Melhor evento do momento!\n", eventos[0].nome_evento, eventos[0].ev_avaliacao);
    for (int i = 1; i < qtd_eventos; i++) {
        printf("\t%s - %.2f\n", eventos[i].nome_evento, eventos[i].ev_avaliacao);
    }
    BubbleSort(x->esq);
    BubbleSort(x->dir);
}

void SelectionSort(TCel* x){
    if (x == NULL) {
        return;
    }

    int qtd_eventos = x->item.qtd_eventos;
    TEvento *eventos = (TEvento*)malloc(qtd_eventos * sizeof(TEvento));

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
    printf("\t%s - %.2f - Melhor evento do momento!\n", eventos[0].nome_evento, eventos[0].ev_avaliacao);
    for (int i = 1; i < qtd_eventos; i++) {
        printf("\t%s - %.2f\n", eventos[i].nome_evento, eventos[i].ev_avaliacao);
    }
    SelectionSort(x->esq);
    SelectionSort(x->dir);
}

void InsertionSort(TCel* x){
    if (x == NULL) {
        return;
    }

    int qtd_eventos = x->item.qtd_eventos;
    TEvento *eventos = (TEvento*)malloc(qtd_eventos * sizeof(TEvento));

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
    printf("\t%s - %.2f - Melhor evento do momento!\n", eventos[0].nome_evento, eventos[0].ev_avaliacao);
    for (int i = 1; i < qtd_eventos; i++) {
        printf("\t%s - %.2f\n", eventos[i].nome_evento, eventos[i].ev_avaliacao);
    }
    InsertionSort(x->esq);
    InsertionSort(x->dir);
}

void ShellSort(TCel* x){
    if (x == NULL) {
        return;
    }

    int qtd_eventos = x->item.qtd_eventos;
    TEvento *eventos = (TEvento*)malloc(qtd_eventos * sizeof(TEvento));
    
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
    printf("\t%s - %.2f - Melhor evento do momento!\n", eventos[0].nome_evento, eventos[0].ev_avaliacao);
    for (int i = 1; i < qtd_eventos; i++) {
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
    printf("\t%s - %.2f - Melhor evento do momento!\n", x->item.evento[0].nome_evento, x->item.evento[0].ev_avaliacao);
    for (int i = 1; i < x->item.qtd_eventos; i++) {
        printf("\t%s - %.2f\n", x->item.evento[i].nome_evento, x->item.evento[i].ev_avaliacao);
    }
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
    printf("\t%s - %.2f - Melhor evento do momento!\n", x->item.evento[0].nome_evento, x->item.evento[0].ev_avaliacao);
    for (int i = 1; i < x->item.qtd_eventos; i++) {
        printf("\t%s - %.2f\n", x->item.evento[i].nome_evento, x->item.evento[i].ev_avaliacao);
    }

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
    printf("\t%s - %.2f - Melhor evento do momento!\n", x->item.evento[0].nome_evento, x->item.evento[0].ev_avaliacao);
    for (int i = 1; i < x->item.qtd_eventos; i++) {
        printf("\t%s - %.2f\n", x->item.evento[i].nome_evento, x->item.evento[i].ev_avaliacao);
    }
    Imprimir_HeapSort(x->esq);
    Imprimir_HeapSort(x->dir);
}

// Impressão das cidades
void Imprimir_cidades(TCel *x, int* seta){
    if(x != NULL){
        Imprimir_cidades(x->esq, seta);
        Imprimir_cidades(x->dir, seta);
        if (*seta == 1) {
            printf(", ");
        }
        printf("[%s]", x->item.nome_cidade);
        *seta = 1;
    }
}

void Imprimir_eventos(TCel *x){
    if(x != NULL){
        Imprimir_eventos(x->esq);
        printf("\n%s: ", x->item.nome_cidade);
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

void Ordem_cidades(TCel *x, int* seta){
    if(x != NULL){
        Ordem_cidades(x->esq, seta);
        if (*seta == 1) {
            printf(" -> ");
        }
        printf("[%s]", x->item.nome_cidade);
        *seta = 1;
        Ordem_cidades(x->dir, seta);
    }
}

void Exibir_mensagem(TCel* x) {
    if (x == NULL || x->item.evento == NULL)
        return;

    char* mens1[] = {
        "Evento TOP:", "Um dos melhores da região:", "Uma experiência única!",
        "Fique ligado:", "Recomendação especial:", "Destaque do mês:", "Prepare-se para o melhor:"};
    char* mens2[] = {
        "Não deixe de participar!", "Imperdível!", "Não perca!", "É a chance de viver algo novo!",
        "Aproveite ao máximo!", "Não deixe escapar essa chance!", "Garanta já o seu lugar!"};

    int aux1 = rand() % (sizeof(mens1) / sizeof(mens1[0]));
    int aux2 = rand() % (sizeof(mens2) / sizeof(mens2[0]));
    int aux3 = rand() % x->item.qtd_eventos;

    printf("\t     %s %s - %s", mens1[aux1], x->item.evento[aux3].nome_evento, mens2[aux2]);

    return;
}

void InOrdem(TCel *x, int* seta){
    if(x != NULL){
        InOrdem(x->esq, seta);
        if (*seta == 1) {
            printf(" -> ");
        }
        printf("[%s]", x->item.nome_cidade);
        *seta = 1;
        InOrdem(x->dir, seta);
    }
}
void PreOrdem(TCel *x, int* seta){
    if(x != NULL){
        if (*seta == 1) {
            printf(" -> ");
        }
        printf("[%s]", x->item.nome_cidade);
        *seta = 1;
        PreOrdem(x->esq, seta);
        PreOrdem(x->dir, seta);
    }
}
void PosOrdem(TCel *x, int* seta){
    if(x != NULL){
        PosOrdem(x->esq, seta);
        PosOrdem(x->dir, seta);
        if (*seta == 1) {
            printf(" -> ");
        }
        printf("[%s]", x->item.nome_cidade);
        *seta = 1;
    }
}


int main() {
    setlocale(LC_ALL,"pt_BR.UTF-8");
    srand(time(NULL));

    TArvore arvore;
    arvore.raiz = NULL;

    Geracao_cidade(&arvore);
    Geracao_eventos(&arvore);

    int escolha, seta = 0;
    TCel* pesquisa = NULL;
    bool loop = true;

    while (loop) {
        escolha = 0;
        printf("=========================================================================================\n");
        printf("\t\t\t\tMENU ROTEIRIO TURÍSTICO");
        printf("\n=========================================================================================\n");
        printf("Escolha uma opção abaixo:");
        printf("\n\t1. Pesquisar\t3. Roteiro de viagem\n\t2. Visualizar\t4. Sair");
        printf("\nEscolha: ");
        scanf("%d", &escolha);
        getchar();
        switch (escolha) {
            case 1:
                while (true) {
                    escolha = 0;    
                    printf("\n=========================================================================================");
                    printf("\n\t\t\t\tPESQUISAR");
                    printf("\n=========================================================================================\n");
                    Exibir_mensagem(arvore.raiz);
                    printf("\n=========================================================================================");
                    printf("\n\t1. Pesquisar cidade pelo nome\t3. Sair\n\t2. Pesquisar por eventos");
                    printf("\nEscolha: ");
                    scanf("%d", &escolha);
                    getchar();
                    switch (escolha) {
                        case 1:
                            printf("\n=========================================================================================");
                            printf("\n\t\t\tPesquisa na cidade");
                            printf("\n=========================================================================================");
                            printf("\nQual cidade deseja pesquisar: ");
                            char nome[100];
                            fgets(nome, sizeof(nome), stdin);
                            nome[strcspn(nome, "\n")] = '\0';
                            pesquisa = Pesquisar_nome(arvore.raiz, nome);
                            if (pesquisa != NULL) {
                                printf("A cidade %s foi encontrada no roteiro turístico!\n", pesquisa->item.nome_cidade);
                                while (true) {
                                    escolha = 0;
                                    printf("\nDeseja pesquisar evento por: \n\t1. Nome\t\t3. Sair\n\t2. Avaliação");
                                    printf("\nEscolha: ");
                                    scanf("%d", &escolha);
                                    getchar();
                                    switch (escolha) {
                                        case 1:
                                            printf("\nDigite o nome do evento: ");
                                            fgets(nome, sizeof(nome), stdin);
                                            nome[strcspn(nome, "\n")] = '\0';
                                            TEvento* evento = Pesquisar_evento_nome(&pesquisa->item, nome);
                                            if (evento != NULL) {
                                                printf("Foi encontrado o evento %s na cidade %s\n", evento->nome_evento, pesquisa->item.nome_cidade);
                                            } else {
                                                printf("O evento %s não foi encontrado na cidade %s\n", nome, pesquisa->item.nome_cidade);
                                            }
                                            break;
                                        case 2:
                                            printf("\nDigite o valor da avaliação desejada: ");
                                            float nota;
                                            scanf("%f", &nota);
                                            getchar();
                                            TEvento evento2 = Buscar_evento_avaliacao(&pesquisa->item, nota);
                                            printf("O evento %s - %.2f, é o que tem a avaliação mais próxima da desejada\n", evento2.nome_evento, evento2.ev_avaliacao);
                                            break;
                                        case 3:
                                            printf("\nVoltando para o menu principal");
                                            printf("\n=========================================================================================\n\n");
                                            break;
                                        default:
                                            printf("\n=========================================================================================");
                                            printf("\n\t\t\tErro de digitação! Digite novamente!");
                                            printf("\n=========================================================================================\n\n");
                                            break;
                                    }
                                    if (escolha == 3) {
                                        printf("\n");
                                        break;
                                    }
                                }
                            } else {
                                printf("Cidade não encontrada!\n");
                                printf("=========================================================================================\n");
                            }
                            break;
                        case 2:
                            while (true) {
                                escolha = 0;
                                printf("\n=========================================================================================");
                                printf("\n\t\t\tPesquisa de eventos em diferentes cidades");
                                printf("\n=========================================================================================");
                                printf("\nDeseja pesquisar evento por: \n\t1. Nome\t\t3. Sair\n\t2. Avaliação");
                                printf("\nEscolha: ");
                                scanf("%d", &escolha);
                                getchar();
                                switch (escolha) {
                                    case 1:
                                        printf("\nDigite o nome do evento: ");
                                        fgets(nome, sizeof(nome), stdin);
                                        nome[strcspn(nome, "\n")] = '\0';
                                        if (Pesquisar_evento_nome1(arvore.raiz, nome) == 0) {
                                            printf("\nEvento não encontrado!\n");
                                        }
                                            printf("=========================================================================================\n");
                                        break;
                                    case 2:
                                        printf("\nDigite o valor da avaliação desejada: ");
                                        float nota;
                                        scanf("%f", &nota);
                                        getchar();
                                        Buscar_evento_avaliacao1(arvore.raiz, nota);
                                        printf("=========================================================================================\n");
                                        break;
                                    case 3:
                                        printf("\nVoltando para o menu principal\n");
                                        printf("=========================================================================================\n\n");
                                        break;
                                    default:
                                        printf("\n=========================================================================================");
                                        printf("\n\t\t\tErro de digitação! Digite novamente!");
                                        printf("\n=========================================================================================\n\n");
                                        break;
                                    }
                                    if (escolha == 3) {
                                        printf("\n");
                                        break;
                                    }
                            } 
                            break;
                        case 3:
                            printf("\nVoltando para o menu principal\n");
                            printf("=========================================================================================\n\n");
                            break;
                        default:
                            printf("\n=========================================================================================");
                            printf("\n\t\t\tErro de digitação! Digite novamente!");
                            printf("\n=========================================================================================\n\n");
                            break;
                    }
                    if (escolha == 3) {
                        break;
                    }
                }
                break;
            case 2:
                while (true) {
                    escolha = 0;
                    printf("\n=========================================================================================");
                    printf("\n\t\t\t\tVISUALIZAR");
                    printf("\n=========================================================================================\n");
                    Exibir_mensagem(arvore.raiz);
                    printf("\n=========================================================================================");
                    printf("\n1. Visualizar por métodos de ordenação\t\t4. Visualizar eventos disponíveis nas cidades\n");
                    printf("2. Visualizar tipos de percursos das cidades\t5. Visualizar eventos com maiores avaliações por cidade\n");
                    printf("3. Visualizar cidades disponíveis\t\t6. Sair\n");
                    printf("\nEscolha: ");
                    scanf("%d", &escolha);
                    getchar();
                    switch (escolha) {
                        case 1: {
                            int num = (rand() % 7) + 1;
                            if (num == 1) {
                                printf("\n=========================================================================================");
                                printf("\n\t\t\t\tMÉTODO BUBBLESORT");
                                printf("\n=========================================================================================");
                                BubbleSort(arvore.raiz);
                                printf("=========================================================================================\n\n");
                            } else if (num == 2) {
                                printf("\n=========================================================================================");
                                printf("\n\t\t\t\tMÉTODO SELECTIONSORT");
                                printf("\n=========================================================================================");
                                SelectionSort(arvore.raiz);
                                printf("=========================================================================================\n\n");
                            } else if (num == 3) {
                                printf("\n=========================================================================================");
                                printf("\n\t\t\t\tMÉTODO INSERTIONSORT");
                                printf("\n=========================================================================================");
                                InsertionSort(arvore.raiz);
                                printf("=========================================================================================\n\n");
                            } else if (num == 4) {
                                printf("\n=========================================================================================");
                                printf("\n\t\t\t\tMÉTODO SHELLSORT");
                                printf("\n=========================================================================================");
                                ShellSort(arvore.raiz);
                                printf("=========================================================================================\n\n");
                            } else if (num == 5) {
                                printf("\n=========================================================================================");
                                printf("\n\t\t\t\tMÉTODO QUICKSORT");
                                printf("\n=========================================================================================");
                                Imprime_QuickSort(arvore.raiz);
                                printf("=========================================================================================\n\n");
                            } else if (num == 6) {
                                printf("\n=========================================================================================");
                                printf("\n\t\t\t\tMÉTODO MERGESORT");
                                printf("\n=========================================================================================");
                                Imprimir_MergeSort(arvore.raiz);
                                printf("=========================================================================================\n\n");
                            } else {
                                printf("\n=========================================================================================");
                                printf("\n\t\t\t\tMÉTODO HEAPSORT");
                                printf("\n=========================================================================================");
                                Imprimir_HeapSort(arvore.raiz);
                                printf("=========================================================================================\n\n");
                            }
                            break;
                        }
                        case 2:
                            printf("\n=========================================================================================");
                            printf("\n\t\t\tPercursos da viajem");
                            printf("\n=========================================================================================");
                            seta = 0;
                            printf("\nPré-ordem: ");
                            PreOrdem(arvore.raiz, &seta);
                            seta = 0;
                            printf("\nEm-order: ");
                            InOrdem(arvore.raiz, &seta);
                            seta = 0;
                            printf("\nPós-order: ");
                            PosOrdem(arvore.raiz, &seta);
                            printf("\n=========================================================================================\n\n");
                            break;
                        case 3:
                            printf("\n=========================================================================================");
                            printf("\n\t\t\t\tCidades disponíveis");
                            printf("\n=========================================================================================");
                            printf("\n=========================================================================================");
                            printf("\nCidades: ");
                            Imprimir_cidades(arvore.raiz, &seta);
                            printf("\n=========================================================================================\n\n");
                            break;
                        case 4:
                            printf("\n=========================================================================================");
                            printf("\n\t\t\tEventos disponíveis nas cidades");
                            printf("\n=========================================================================================");
                            Imprimir_eventos(arvore.raiz);
                            printf("=========================================================================================\n\n");
                            break;
                        case 5:
                            printf("\n=========================================================================================");
                            printf("\n\t\t\tEventos com maiores avaliações por cidade");
                            printf("\n=========================================================================================");
                            Evento_maior_avalicao(arvore.raiz);
                            printf("=========================================================================================\n\n");
                            break;
                        case 6:
                            printf("\nVoltando para o menu principal\n");
                            printf("=========================================================================================\n");
                            break;
                        default:
                            printf("\n=========================================================================================");
                            printf("\n\t\t\tErro de digitação! Digite novamente!");
                            printf("\n=========================================================================================\n\n");
                            break;
                    }
                    if (escolha == 6) {
                        printf("\n");
                        break;
                    }
                }
                break;
            case 3:
            while (true) {
                escolha = 0;
                printf("\n=========================================================================================");
                printf("\n\t\t\t\tROTEIRO");
                printf("\n=========================================================================================\n");
                Exibir_mensagem(arvore.raiz);
                printf("\n=========================================================================================\n");
                printf("Que tipo de roteiro você gostaria de seguir: \n\t1. Eventos com a avalição maior do que 7\t3. Cidades com mais eventos\n\t2. Seguir na ordem das cidades\t\t\t4. Sair");
                printf("\nEscolha: ");
                scanf("%d", &escolha);
                getchar();
                    switch (escolha) {
                        case 1:              
                            printf("\n=========================================================================================");   
                            printf("\n\t\t\tEventos as avaliações maiores do que 7");
                            printf("\n=========================================================================================");
                            Buscar_evento_avaliacao2(arvore.raiz);
                            printf("=========================================================================================\n\n");
                            break;
                        case 2:
                            seta = 0;
                            printf("\n=========================================================================================");
                            printf("\n\t\t\tMelhor rota para visitar todas as cidades!");
                            printf("\n=========================================================================================\n");
                            Ordem_cidades(arvore.raiz, &seta);
                            printf("\n=========================================================================================\n\n");
                            
                            break;
                        case 3:
                            printf("\n========================================================================================="); 
                            printf("\n\t\t\tQuantidade de eventos por cidade");
                            printf("\n=========================================================================================");
                            Contar_eventos(arvore.raiz);
                            printf("\n=========================================================================================\n\n");
                            break;    
                        case 4:
                            printf("\nVoltando para o menu principal\n");
                            printf("=========================================================================================\n");
                            break;
                        default:
                            printf("\n=========================================================================================");
                            printf("\n\t\t\tErro de digitação! Digite novamente!");
                            printf("\n=========================================================================================\n\n");
                            break;
                    }
                    if (escolha == 4) {
                        printf("\n");
                        break;
                    }
                } 
                break;
            case 4:
                printf("\nFechando o roteiro turístico...");
                printf("\n=========================================================================================\n\n");
                loop = false;
                break;
            default:
                printf("\n=========================================================================================");
                printf("\n\t\t\tErro de digitação! Digite novamente!");
                printf("\n=========================================================================================\n\n");
                break;
        }
    }

    return 0;
}