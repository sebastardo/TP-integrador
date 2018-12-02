#include "main.h"


int main()
{
    t_fecha fechaProceso;
    char archMaestro[TAM];

    ingresar_fecha(&fechaProceso, "Ingrese fecha de hoy");


    printf("\nDatos de archivos (debe incluir path)\n");
    printf("Archivo a leer: ");
    fflush(stdin);
    scanf("%999[^\n]%*c", archMaestro);
    fflush(stdin);


    if(!desarme_archivo_txt(archMaestro,&fechaProceso))
        return 1;

    if(!crear_indice_baja(ARCHALUMNOK,ARCHINDICEOK,ARCHIDICEBAJA))
        return 2;

    //crear y cargar TDA
    /// PILA
    /// COLA
    /// LISTA(S)
    /// ARBOL


    //MENU

    return 0;
}
