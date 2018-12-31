#ifndef MANEJO_ARCHIVOS_H_INCLUDED
#define MANEJO_ARCHIVOS_H_INCLUDED

#include "lista.h"

int comprobar_existencia_archivo(const char *, const char *);

int cantidad(const char *archivo);

int guardar_indice(t_lista *,const char *);

int grabar_en_archivo(t_alumno *,const char *);

int grabar_en_archivo_en_posicion(const char *, int);


#endif // MANEJO_ARCHIVOS_H_INCLUDED
