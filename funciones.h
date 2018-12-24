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


int crear_indice_baja(char *, char *, char *);
int cargar_listas(char *, char *,t_lista *,t_lista *);

char menu(const char [][TAM_MENU],const char *);

int ingresar_alumno(t_lista *, const char *, int, const t_fecha *);
int dar_de_baja_alumno(t_lista *, t_lista *, const char *);

int grabar_en_archivo(t_alumno *,const char *);

int ingersar_datos_alumno(t_alumno *, const t_fecha *);
void datos_por_teclado(t_alumno *);

#endif // FUNCIONES_H_INCLUDED

