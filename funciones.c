#include "funciones.h"


/** con esto ingreso cualquier fecha y con mensaje! **/
void ingresar_fecha(t_fecha *fecha, const char *mensaje)
{
    int ok;
    do
    {
        printf("%s (dd/mm/aaaa): ",mensaje);
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


/** Con esto creo los archivos con los datos correcto y otro con los errores **/
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

        if(comprobar_errores(errores))
        {
            fwrite(&alumno,sizeof(t_alumno),1,fpOK);
        }
        else
        {
            char *mensaje[300];
            txt_registros_invalidos(&alumno, errores, fecha_actual, &mensaje);
            fputs(&mensaje,fpError);

        }
        fflush(stdin);
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


/** Cuento errores **/
void lista_errores(const t_alumno *alumno,int *errores, const t_fecha *fecha_actual)
{
    errores[0]=!(validar_dni(alumno->DNI));
    errores[1]=!(validar_apyn(&alumno->apyn));
    errores[2]=!(validar_fecha_nacimiento(&alumno->fNacimiento,fecha_actual));
    errores[3]=!(validar_sexo(alumno->sexo));
    errores[4]=!(validar_fecha_ingreso(&alumno->fIngreso,&alumno->fNacimiento,fecha_actual));
    errores[5]=!(validar_carrera(&alumno->carrera));
    errores[6]=!(validar_materias_aprobadas(alumno->mAprobadas));
    errores[7]=!(validar_fecha_ultima_materia(&alumno->fUltimaMateria,&alumno->fIngreso,fecha_actual));
    errores[8]=!(validar_estado(alumno->estado));
    errores[9]=!(validar_fecha_baja(&alumno->fBaja,&alumno->fIngreso));
    fflush(stdin);
}

/** Veo cuantos errores tengo en la estructura **/
int comprobar_errores(const int *errores)
{
    int i;
    for(i=0;i<10;i++)
    {
        if(errores[i]!=0)
            return ERROR;
    }
    return CORRECTO;
}


/** Nornalizador de Apellido y Nombre **/
char *normalizarNombre(char *nombre)
{
    int flag=0;
    int flagComa=0;

    char *origen = nombre;
    char *destino = nombre;
    char *conComa = nombre;

    //hace que empiece por la letras y descarta los espacios del principio
    while(*origen==' ')
        origen++;

    while(*origen)
    {
        //borra caracteres no letras que aparezcan al principio de los nombres
        while((tolower(*origen)<97 || tolower(*origen)>124)&&(*origen!=' ' || *origen!=','))
        {
                origen++;
        }

        //pone en mayusculas
        if(*origen!=' ' && *origen!=',')
        {
            *destino=toupper(*origen);
            origen++;
            destino++;
            flag=0;
        }

        //pone en minusculas hasta que encuentra un espacio
        while(*origen!=' ' && *origen!=',' && *origen)
        {
            if(tolower(*origen)>=97 && tolower(*origen)<123) //solo trabaja con letras
            {
                *destino=tolower(*origen);
                destino++;
            }
            origen++;
        }

        if(*origen==' ') //quita los espacios de mas
        {
            if(!flag)
            {
                *destino=*origen;
                *destino++;
                flag=1;
            }
            origen++;
        }

        //quita las comas de mas
        if(*origen==',')
        {
            if(!flagComa) //esto lo hace solo si es la primer coma
            {
                origen--; //a partir de aca es para quitar el espacio antes de la coma
                if(*origen==' ')
                {
                    destino--;
                    *origen=',';
                }
                else //si no hay espacio antes de la coma, vuelve todo a la normalidad
                {
                    origen++;
                }

                *destino=*origen;

                flagComa=1;//marca que ya hay una coma

                destino++;
                origen++;

                while(*origen==' ')//si hay espacios despues la coma, los borra
                    origen++;
            }
            else
                origen++;
        }
    }

    *destino='\0';

    while(!flagComa && *conComa) //si no hay coma, la pone despues de la primera palabra
    {
        if(*conComa==' ')
        {
            *conComa=',';
            flagComa=1;
        }

        conComa++;
    }

    return nombre;
}



char *txt_registros_invalidos(const t_alumno *alumno, const int *errores, const t_fecha *fecha_actual, char *mensaje)
{
    char auxTexto[100];
    int i;
    char nombresError[][40]={{"DNI"},
                             {"Apellido y nombre"},
                             {"Fecha de nacimiento"},
                             {"Sexo"},
                             {"Fecha de ingreso"},
                             {"Carrera"},
                             {"Materias aprobadas"},
                             {"Fecha de ultima materia aprobada"},
                             {"Estado"},
                             {"Fecha de baja"}};

    strcpy(mensaje,"\0");

    sprintf(auxTexto, "%d/%d/%d:\t",fecha_actual->dia, fecha_actual->mes, fecha_actual->anio);
    strcat(mensaje,auxTexto);

    sprintf(auxTexto, "%d", alumno->DNI);
    strcat(mensaje,auxTexto);
    strcat(mensaje," - ");
    strcat(mensaje,alumno->apyn);
    strcat(mensaje," - ");
    sprintf(auxTexto, "%d/%d/%d - %c - ", alumno->fNacimiento.dia,alumno->fNacimiento.mes,alumno->fNacimiento.anio ,alumno->sexo);
    strcat(mensaje,auxTexto);
    sprintf(auxTexto, "%d/%d/%d - ", alumno->fIngreso.dia, alumno->fIngreso.mes, alumno->fIngreso.anio);
    strcat(mensaje,auxTexto);
    strcat(mensaje,alumno->carrera);
    strcat(mensaje," - ");
    sprintf(auxTexto, "%d/%d/%d - %d - %c - ", alumno->fUltimaMateria.dia, alumno->fUltimaMateria.mes, alumno->fUltimaMateria.anio, alumno->mAprobadas,alumno->estado);
    strcat(mensaje,auxTexto);
    sprintf(auxTexto, "%d/%d/%d", alumno->fBaja.dia,alumno->fBaja.mes,alumno->fBaja.anio);
    strcat(mensaje,auxTexto);
    strcat(mensaje,"\n\t\t");


    for(i=0;i<10;i++)
    {
        if(errores[i])
        {
            strcat(mensaje,nombresError[i]);
            strcat(mensaje," - " );
        }

    }
    mensaje[strlen(mensaje)-2]='\n';
    mensaje[strlen(mensaje)-1]='\0';

    return mensaje;
}
