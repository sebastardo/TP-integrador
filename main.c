#include "main.h"


int main()
{
    t_fecha fechaProceso;
    char archMaestro[TAM];

    ingresar_fecha(&fechaProceso, "Ingrese fecha de hoy");


    printf("\nDatos de archivos (debe incluir path)\n");
    printf("\nArchivo a leer: ");
    fflush(stdin);
    scanf("%999[^\n]%*c", archMaestro);
    fflush(stdin);


    if(!creacion_archivos(archMaestro,&fechaProceso))
        return 1;


    return 0;
}
