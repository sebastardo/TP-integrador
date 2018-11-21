#include "funciones.h"


/** con esto ingreso cualquier fecha y con mensaje! **/
void ingresar_fecha(t_fecha *fecha, const char *mensaje)
{
    int ok;
    do
    {
        printf("%s (dd/mm/aaaa):",mensaje);
        scanf("%d/%d/%d", &fecha->dia, &fecha->mes, &fecha->anio);
        fflush(stdin);
        ok=validar_fecha(fecha);


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


/** Con esto creo los archivos con los datos correcto y otro conlos errores **/
int creacion_archivos(char *archivo_maestro, const t_fecha *fecha_actual)
{
    FILE *fpTexto, *fpOK, *fpError;
    t_alumno alumno;
    char linea[300];
    int errores[10];

    fpTexto=fopen(archivo_maestro,"r");
    if(!fpTexto)
        return ERROR;

    fpOK=fopen(ARCHALUMNOK, "wb");
    if(!fpOK)
        return ERROR;

    fpError=fopen(ARCHALUMNERROR, "w");
    if(!fpError)
        return ERROR;

    while(fgets(linea,sizeof(linea),fpTexto))
    {
        separar(&linea,&alumno);

        lista_errores(&alumno,&errores, fecha_actual);

        if(comprobar_errores(&errores)==0)
        {
            //guardar en ok.dat
        }
        else
        {
            //guardar en error.txt
        }
    }

    fclose(fpTexto);
    fclose(fpOK);
    fclose(fpError);

    return CORRECTO;
}


/** separa las lineas de txt en datos para la estructura **/
void separar(const char *s, t_alumno *alumno)
{
    char linea[300];
    char *aux;

    strcpy(linea,s);

    aux = strrchr(linea, '|');
    *aux='\0';

    /*fecha de baja*/
    aux = strrchr(linea,'|');
    if(strlen(aux)==1)
    {
        alumno->fBaja.dia=1;
        alumno->fBaja.mes=1;
        alumno->fBaja.anio=9999;
    }
    else
    {
        sscanf(aux+1,"%d/%d/%d",&alumno->fBaja.dia,&alumno->fBaja.mes,&alumno->fBaja.anio);
    }
    *aux='\0';

    /*estado*/
    aux = strrchr(linea,'|');
    if(strlen(aux)==1)
    {
        alumno->estado='R';
    }
    else
    {
        sscanf(aux+1,"%c",&alumno->estado);
    }
    *aux='\0';


    /*Fecha ultima materia aprobada */
    aux = strrchr(linea,'|');

    sscanf(aux+1,"%d/%d/%d",&alumno->fUltimaMateria.dia,&alumno->fUltimaMateria.mes,&alumno->fUltimaMateria.anio);
    *aux='\0';

    /*Cantidad de materias*/
    aux = strrchr(linea,'|');
    sscanf(aux+1,"%d",&alumno->mAprobadas);
    *aux='\0';

    /*Carrera*/
    aux = strrchr(linea,'|');
    sscanf(aux+1,"%s",&alumno->carrera);
    *aux='\0';

    /*Fecha ingreso */
    aux = strrchr(linea, '|');
    sscanf(aux+1,"%d/%d/%d",&alumno->fIngreso.dia, &alumno->fIngreso.mes,&alumno->fIngreso.anio);
    *aux='\0';


    /*sexo*/
    aux = strrchr(linea,'|');
    sscanf(aux+1,"%c",&alumno->sexo);
    *aux='\0';

    /*Fecha nacimiento */
    aux = strrchr(linea, '|');
    sscanf(aux+1,"%d/%d/%d",&alumno->fNacimiento.dia, &alumno->fNacimiento.mes, &alumno->fNacimiento.anio);
    *aux='\0';

    /*Nombre*/
    aux = strrchr(linea,'|');
    sscanf(aux+1,"%s",&alumno->apyn);
    *aux='\0';

    /*DNI*/
    aux-=8;
    sscanf(aux,"%ld", &alumno->DNI);
}


/** Compruebo los errores **/
 //NO HECHO
void lista_errores(const t_alumno *alumno,int *errores, const t_fecha *fecha_actual)
{
    errores[0]=validar_dni(alumno->DNI);
//    errores[1]=comparadorString(&a->apynom);
//    errores[2]=(!(fechaDeNacimiento(&a->fNac, f)))? 1: 0;
//    errores[3]=validarSexo(a->sexo);
//    errores[4]=(!fechaDeIngreso(&a->fIng,f, &a->fNac)) ? 1: 0;
//    errores[5]=validarCarrera(&a->carrera);
//    errores[6]=materiasAprobadas(a->matAprob);
//    errores[7]=(!fechaUltimaMateria(&a->ultMatAprob,&a->fIng, f, a->matAprob));
//    errores[8]=(validacionEstado(a->estado));
//    errores[9]=validacionFechaBaja(&a, &f);//no anda
    fflush(stdin);
}

int comprobar_errores(const int *errores)
{
    return CORRECTO;
}
