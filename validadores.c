#include "validadores.h"

int fecha_valida(const t_fecha *fecha)
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
