#include "validadores.h"

int validar_fecha(const t_fecha *fecha)
{
    const int dias[][12] = {{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                            {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

    if(fecha->anio<1900)
        return FECHAERRORANIO;

    if(fecha->mes<1 || fecha->mes>12)
        return FECHAERRORMES;

    if(fecha->dia<1 || fecha->dia>dias[esBisiesto(fecha->anio)][fecha->mes-1])
        return FECHAERRORDIA;

    return FECHAOK;
}


int validar_dni(const long int dni)
{
    return (10000<dni && 100000000>dni);
}


int validar_apyn(const char *apyn)
{
    char aux1[40], aux2[40];
    int i;

    strcpy(aux1, apyn);
    strcpy(aux2, apyn);
    normalizarNombre(&aux2);

    for(i=0;i<strlen(aux1)-1;i++)
    {
        if(aux1[i]!=aux2[i])
        {
            return 0;
        }
    }
    return 1;
}


int validar_fecha_nacimiento(const t_fecha *fecha_nac, const t_fecha *fecha_actual)
{
    if(validar_fecha(fecha_nac))
        return ERROR;

    return ((fecha_actual->anio-10)>fecha_nac->anio);
}


int validar_sexo(const char sexo)
{
    return (toupper(sexo)=='F' || toupper(sexo)=='M');
}


int validar_fecha_ingreso(const t_fecha *fecha_ingreso,const t_fecha *fecha_nac,const t_fecha *fecha_actual)
{
    if(validar_fecha(fecha_ingreso))
        return ERROR;

    return (comparar_fechas(fecha_ingreso,fecha_nac) >=1 && comparar_fechas(fecha_ingreso,fecha_actual)<=0);
}


int validar_carrera(const char *carrera)
{
    int i;
    char carreras[][4]={{"INF"},{"ELE"},{"IND"},{"ECO"},{"DER"},{"ADM"},{"MED"},{"EDF"},{"FIL"}};

    for(i=0;i<9;i++)
    {
        if(!strcmp(carreras[i],carrera))
        {
            return 1; //lo encontro
        }
    }
    return 0;
}


int validar_materias_aprobadas(const int materias)
{
    return materias>=0 && materias<50;
}


int validar_fecha_ultima_materia(const t_fecha *fecha_ultima_materia,const t_fecha *fecha_ingreso,const t_fecha *fecha_actual)
{
    if(validar_fecha(fecha_ultima_materia))
        return 0;

    return (comparar_fechas(fecha_ultima_materia,fecha_ingreso) >=0 && comparar_fechas(fecha_ultima_materia,fecha_actual)<=0);
}


int validar_estado(const char estado)
{
    return (toupper(estado)=='R' || toupper(estado)=='B');
}


int validar_fecha_baja(const t_fecha *fecha_baja,const t_fecha *fecha_ingreso)
{
    if(validar_fecha(fecha_baja))
        return 0;
    return (comparar_fechas(fecha_baja,fecha_ingreso)>0);
}


int comparar_fechas(const t_fecha *fecha_1, const t_fecha *fecha_2)
{
    /// return -1 -> fecha_2 es mayor
    /// return  1 -> fecha_1 es mayor
    /// return  0 -> fechas iguales



    int comp = fecha_1->anio - fecha_2->anio;

    if(comp)
        return comp;

    comp=fecha_1->mes - fecha_2->mes;

    if(comp)
        return comp;

    return fecha_1->dia - fecha_2->dia;
}
