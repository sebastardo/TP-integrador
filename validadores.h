#ifndef VALIDADORES_H_INCLUDED
#define VALIDADORES_H_INCLUDED

#include "estructuras.h"
#include "definiciones.h"

int validar_fecha(const t_fecha *);
int validar_dni(const long int);
int validar_apyn(const char *);
int validar_fecha_nacimiento(const t_fecha *, const t_fecha *);
int validar_sexo(const char);
int validar_fecha_ingreso(const t_fecha *,const t_fecha *,const t_fecha *);
int validar_carrera(const char *);
int validar_materias_aprobadas(const int);
int validar_fecha_ultima_materia(const t_fecha *,const t_fecha *,const t_fecha *);
int validar_estado(const char);
int validar_fecha_baja(const t_fecha *,const t_fecha *,const t_fecha *);
int comparar_fechas(const t_fecha *, const t_fecha *);
#endif // VALIDADORES_H_INCLUDED
