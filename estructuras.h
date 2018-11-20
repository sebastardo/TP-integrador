#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

typedef struct
{
    int dia,
        mes,
        anio;
}t_fecha;

typedef struct
{
    long DNI;
    char apyn[40];
    t_fecha fNacimiento;
    char sexo;
    t_fecha fIngreso;
    char carrera[4];
    int mAprobadas;
    t_fecha fUltimaMateria;
    char estado;
    t_fecha fBaja;
}t_alumno;


/** TIPO PARA TDA *****************************************************/
typedef struct
{
   long dni;
   unsigned nro_reg;
}t_reg_indice;


/** TDA Pila*****************************************************/

/** TDA Cola*****************************************************/

/** TDA Lista*****************************************************/

/** TDA Arbol*****************************************************/


#endif // ESTRUCTURAS_H_INCLUDED
