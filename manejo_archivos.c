#include "manejo_archivos.h"


int comprobar_existencia_archivo(const char *archivo, const char *modo)
{
    FILE *fp=fopen(archivo, modo);

    if(fp==NULL)
        return 0;
    fclose(fp);
    return 1;
}

int guardar_indice(t_lista *lista,const char *archivo)
{
    t_reg_indice indice;
    FILE *fp=fopen(archivo, "wb");
    if(fp==NULL)
        return 0;

    while(sacar_de_lista(lista, &indice))
    {
        fwrite(&indice,sizeof(t_reg_indice),1,fp);
    }
    fclose(fp);
    return 1;
}


int grabar_en_archivo(t_alumno *alumno,const char *archivo)
{
    FILE *fp=fopen(archivo,"ab");

    if(!fp)
        return 0;

    fwrite(alumno,sizeof(t_alumno),1,fp);

    fclose(fp);
    return 1;
}

int grabar_en_archivo_en_posicion(const char *archivo, int posicion)
{
    t_alumno alumno;
    FILE *fp=fopen(archivo,"r+b");

    if(!fp)
        return 0;

    //ir a posicion
    //guardar en t_alumno
    // ediar:
    //      alumno.estado
    //      alumno.fBaja
    //ir a posicion de nuevo
    //guardar t_alumno

    fclose(fp);
    return 1;
}
