#include "lista.h"

void crear_lista(t_lista *lista)
{
    *lista=NULL;
}

int poner_lista_al_final(t_lista *lista, const t_reg_indice *d)
{
    t_nodo *nuevo = (t_nodo *)malloc(sizeof(t_nodo));

    if(nuevo==NULL)
        return 0;

    nuevo->indice=*d;
    nuevo->siguiente=NULL;

    while(*lista)
    {
        lista=&(*lista)->siguiente;
    }

    *lista=nuevo;

    return 1;
}

void vaciar_lista(t_lista *lista)
{
    t_nodo *aux;
    while(*lista)
    {
        aux=*lista;
        lista=&(*lista)->siguiente;
        free(aux);
    }
}


int poner_lista_en_orden(t_lista *lista, const t_reg_indice *d, int (*comparar)(const t_reg_indice *, const t_reg_indice *))
{
    t_nodo *aux;
    while(*lista && comparar(&(*lista)->indice, d)<0)
    {
        lista=&(*lista)->siguiente;
    }

    aux=(t_nodo *)malloc(sizeof(t_nodo));

    if(aux==NULL)
        return 0;

    aux->indice=*d;
    aux->siguiente=*lista;
    *lista=aux;

    return 1;
}

int comparar(const t_reg_indice *A, const t_reg_indice *B)
{
    return A->dni - B->dni;
}

