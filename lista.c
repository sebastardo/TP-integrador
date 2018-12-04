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
