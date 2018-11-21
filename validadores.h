#ifndef VALIDADORES_H_INCLUDED
#define VALIDADORES_H_INCLUDED

#include "estructuras.h"
#include "definiciones.h"

int validar_fecha(const t_fecha *);
int validar_dni(const long int);
//comparadorString(&a->apynom);
//err[2]=(!(fechaDeNacimiento(&a->fNac, f)))? 1: 0;
in validar_sexo(const char *);
//err[4]=(!fechaDeIngreso(&a->fIng,f, &a->fNac)) ? 1: 0;
int validar_carrera(const char *);
int validar_materias_aprobadas(const int);
//err[7]=(!fechaUltimaMateria(&a->ultMatAprob,&a->fIng, f, a->matAprob));
int validar_estado(const char *);
//err[9]=validacionFechaBaja(&a, &f);//no anda

#endif // VALIDADORES_H_INCLUDED
