#include "funciones.h"

void ingresar_fecha(t_fecha *fecha, const char *mensaje)
{
    int ok;
    do
    {
        printf("%s (dd/mm/aaaa):",mensaje);
        scanf("%d/%d/%d", &fecha->dia, &fecha->mes, &fecha->anio);
        fflush(stdin);
        ok=fecha_valida(fecha);


        switch (ok)
        {
            case FECHAERRORANIO:
            {
                printf("El año debe ser mayor a 1900\n");
                break;
            }
            case FECHAERRORMES:
            {
                printf("El mes debe ser entre 1 y 12\n");
                break;
            }
            case FECHAERRORDIA:
            {
                printf("El dia es incorrecto\n");
                break;
            }
            default:
                break;
        }
    }while(ok);

}
