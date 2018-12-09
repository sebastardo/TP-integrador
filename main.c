#include "main.h"


int main()
{
    t_fecha fechaProceso;
    char archMaestro[TAM];
    int ubicacion;
    t_lista lista_regulares, lista_bajas;
    char menuPrincipal[][TAM_MENU]={{"MBOF"},
                                    {"Mantenimiento"},
                                    {"Listar bajas"},
                                    {"Listar en orden"},
                                    {"Finalizar"}};
    char menuMantenimiento[][TAM_MENU]={{"ABS"},{"Altas"},{"Bajas"},{"Salir"}};
    char opcion;



    ingresar_fecha(&fechaProceso, "Ingrese fecha de hoy");


    printf("\nDatos de archivos (debe incluir path)\n");
    printf("Archivo a leer: ");
    fflush(stdin);
    scanf("%999[^\n]%*c", archMaestro);
    fflush(stdin);


    if(!desarme_archivo_txt(archMaestro,&fechaProceso))
        return 1;

    ubicacion=crear_indice_baja(ARCHALUMNOK,ARCHINDICEOK,ARCHIDICEBAJA);
    if(!ubicacion)
        return 2;

    //crear y cargar TDA
    /// PILA
    /// COLA
    /// LISTA(S)

    crear_lista(&lista_regulares);
    crear_lista(&lista_bajas);


    if(!cargar_listas(ARCHINDICEOK,ARCHIDICEBAJA,&lista_regulares, &lista_bajas))
        return 3;

    /// ARBOL


    //MENU

    do
    {
        opcion=menu(menuPrincipal,"Seleccione opcion: ");
        switch(opcion)
        {
            case 'M':

                do
                {
                    opcion=menu(menuMantenimiento,"Seleccione subopcion: ");
                    switch(opcion)
                    {
                        case 'A':
                            ubicacion=ingresar_alumno(&lista_regulares, ARCHALUMNOK, ubicacion);
                            break;
                        case 'B':
                            dar_de_baja_alumno(&lista_regulares, &lista_bajas, ARCHALUMNOK);
                            break;
                        default:
                            break;
                    }
                }while(opcion!='S');

                break;

            case 'B':
                lista_indice(&lista_bajas,mostrar);
                break;

            case 'O':
                lista_indice(&lista_regulares,mostrar);
                break;

            default:
                break;
        }
    }while(opcion!='F');


    vaciar_lista(&lista_regulares);
    vaciar_lista(&lista_bajas);

    return 0;
}

