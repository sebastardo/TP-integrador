#include "lista.h"


void crear_lista(t_lista *lista)
{
    *lista=NULL;
}

int poner_lista_al_final(t_lista *lista, const t_reg_indice *d)
{
    t_nodo *nuevo = (t_nodo *)malloc(sizeof(t_nodo));

    if(nuevo==NULL)
        return 0;

    nuevo->indice=*d;
    nuevo->siguiente=NULL;

    while(*lista)
    {
        lista=&(*lista)->siguiente;
    }

    *lista=nuevo;

    return 1;
}

void vaciar_lista(t_lista *lista)
{
    t_nodo *aux;
    while(*lista)
    {
        aux=*lista;
        lista=&(*lista)->siguiente;
        free(aux);
    }
}


int poner_lista_en_orden(t_lista *lista, const t_reg_indice *d, int (*comparar)(const t_reg_indice *, const t_reg_indice *))
{
    t_nodo *aux;
    while(*lista && comparar(&(*lista)->indice, d)<0)
    {
        lista=&(*lista)->siguiente;
    }

    aux=(t_nodo *)malloc(sizeof(t_nodo));

    if(aux==NULL)
        return 0;

    aux->indice=*d;
    aux->siguiente=*lista;
    *lista=aux;

    return 1;
}

int comparar(const t_reg_indice *A, const t_reg_indice *B)
{
    return A->dni - B->dni;
}


void lista_indice(const t_lista *lista, void (*mostrar)(const t_reg_indice *, const char *))
{
    while(*lista)
    {
        mostrar(&(*lista)->indice, ARCHALUMNOK);
        lista = &(*lista)->siguiente;
    }
    printf("Fin de lista\n\n");
}

void mostrar(const t_reg_indice *A, const char *archivo)
{
    FILE *fp;
    t_alumno alumno;

    fp = fopen(archivo,"rb");

    fseek(fp, (sizeof(t_alumno)*(A->nro_reg-1)), SEEK_SET );

    fread(&alumno,sizeof(t_alumno),1,fp);

    fclose(fp);

    printf("%d\n", A->dni);
    printf("\t%s - ", alumno.apyn);
    printf("%d/%d/%d - ", alumno.fNacimiento.dia,alumno.fNacimiento.mes,alumno.fNacimiento.anio);
    printf("%c\n",alumno.sexo);
    printf("\t%d/%d/%d - ", alumno.fIngreso.dia,alumno.fIngreso.mes,alumno.fIngreso.anio);
    printf("%s - ",alumno.carrera);
    printf("%d - ",alumno.mAprobadas);
    printf("%d/%d/%d - ", alumno.fUltimaMateria.dia, alumno.fUltimaMateria.mes, alumno.fUltimaMateria.anio);
    printf("%c - ",alumno.estado);
    printf("%d/%d/%d\n", alumno.fBaja.dia,alumno.fBaja.mes,alumno.fBaja.anio);

}


int buscar_en_lista(const t_lista *lista,const t_reg_indice *d, int (*comparar)(const t_reg_indice *, const t_reg_indice *))
{
    while(*lista)
    {
        if(comparar(&(*lista)->indice, d)==0)
            return 1;

        lista=&(*lista)->siguiente;
    }
    return 0;
}


int sacar_de_lista(t_lista *lista, t_reg_indice *indice)
{
    if(*lista==NULL)
    {
        return 0;
    }

    indice=*lista;
    *lista=(*lista)->siguiente;
    return 1;
}
