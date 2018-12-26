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
