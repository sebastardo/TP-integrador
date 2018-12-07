#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include "validadores.h"


void ingresar_fecha(t_fecha *, const char *);
int desarme_archivo_txt(char *, const t_fecha *);

void separar(const char *,t_alumno *);
void lista_errores(const t_alumno *,int *, const t_fecha *);
int comprobar_errores(const int *);
char *normalizarNombre(char *);
char *txt_registros_invalidos(const t_alumno *, const int *errores, const t_fecha *, char *);


//int crear_indice_baja(char *, char *, char *);
//int cargar_listas(char *, char *,t_lista *,t_lista *);

int cargar_listas(const char *, t_lista *,t_lista *);

char menu(const char [][TAM_MENU],const char *);

int ingresar_alumno(t_lista *, const char *);
int dar_de_baja_alumno(t_lista *, t_lista *, const char *);

void listar(const char *,t_lista *);
#endif // FUNCIONES_H_INCLUDED
