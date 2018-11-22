#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include "validadores.h"


void ingresar_fecha(t_fecha *, const char *);
int creacion_archivos(char *, const t_fecha *);

void separar(const char *,t_alumno *);
void lista_errores(const t_alumno *,int *, const t_fecha *);
int comprobar_errores(const int *);
char *normalizarNombre(char *);
char *txt_registros_invalidos(const t_alumno *, const int *errores, const t_fecha *, char *);

#endif // FUNCIONES_H_INCLUDED
