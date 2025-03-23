void Imprimir_cidades(TCel *x, int* seta){
    if(x != NULL){
        Imprimir_cidades(x->esq, seta);
        if (*seta == 1) {
            printf(", ");
        }
        printf("[%s]", x->item.nome_cidade);
        *seta = 1;
        Imprimir_cidades(x->dir, seta);
    }
}