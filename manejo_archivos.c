#include "manejo_archivos.h"


int comprobar_existencia_archivo(const char *archivo, const char *modo)
{
    FILE *fp=fopen(archivo, modo);

    if(fp==NULL)
        return 0;
    fclose(fp);
    return 1;
}


int cantidad(const char *archivo)
{
    t_alumno alumno;
    int ubicacion;

    FILE *ok=fopen(archivo, "rb");

    if(!archivo)
        return 0;

    fread(&alumno,sizeof(t_alumno),1,ok);
    ubicacion=1;

    while(!feof(ok))
    {
        fread(&alumno,sizeof(t_alumno),1,ok);
        ubicacion++;
    }

    ubicacion--;
    fclose(ok);
    return ubicacion;
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
    int pos;
    FILE *fp=fopen(archivo,"r+b");


    if(!fp)
        return 0;


    //ir a posicion
    pos=(sizeof(t_alumno))*(posicion-1);
    fseek( fp, pos , SEEK_SET );
    //guardar en t_alumno
    fread(&alumno,sizeof(t_alumno),1,fp);
    // editar:
    //      alumno.estado
    alumno.estado='B';


    //      alumno.fBaja: ingresarla a mano (validar que no se anterior a fecha de inscripcion ni mayor a fecha actual), espacio en blanco pone fecha actual
    do{
        ingresar_fecha(&alumno.fBaja, "Fecha de baja");
    }while(validar_fecha_baja(&alumno.fBaja));

    //ir a posicion de nuevo
    fseek( fp, pos , SEEK_SET );
    //guardar t_alumno
    fwrite(&alumno,sizeof(t_alumno),1,fp);

    fclose(fp);
    return 1;
}
