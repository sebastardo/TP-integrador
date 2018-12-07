#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"
#include "definiciones.h"

void crear_lista(t_lista *);

int poner_lista_al_final(t_lista *, const t_reg_indice *);
int poner_lista_en_orden(t_lista *, const t_reg_indice *, int (*comparar)(const t_reg_indice *, const t_reg_indice *));

void vaciar_lista(t_lista *);

void recorrer_lista(const t_lista *, void (*mostrar)(const t_reg_indice *, const char *));

int comparar(const t_reg_indice *, const t_reg_indice *);
void mostrar(const t_reg_indice *, const char *);

#endif // LISTA_H_INCLUDED
