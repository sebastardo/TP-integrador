#include "funciones.h"
#include "lista.h"


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
int desarme_archivo_txt(char *archivo_maestro, const t_fecha *fecha_actual)
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


int crear_indice_baja(char *OK, char *INDICE, char *BAJA)
{
    t_alumno alumno;
    t_reg_indice registro;
    int ubicacion;
    FILE *ok=fopen(OK, "rb");
    FILE *indice=fopen(INDICE,"wb");
    FILE *baja=fopen(BAJA,"wb");

    if(!ok && !indice && !baja) // muy mal, vago
        return 0;

    fread(&alumno,sizeof(t_alumno),1,ok);
    ubicacion=1;

    while(!feof(ok))
    {
        registro.dni=alumno.DNI;
        registro.nro_reg=ubicacion;

        if(alumno.estado=='R')
        {
            fwrite(&registro,sizeof(t_reg_indice),1,indice);
        }
        else
        {
            fwrite(&registro,sizeof(t_reg_indice),1,baja);
        }

        fread(&alumno,sizeof(t_alumno),1,ok);
        ubicacion++;
    }

    ubicacion--;
    fclose(ok);
    fclose(indice);
    fclose(baja);

    return ubicacion;
}


int cargar_listas(char *INDICE, char *BAJAS,t_lista *lIndice,t_lista *lBajas)
{
    FILE *indice=fopen(INDICE,"rb");
    FILE *baja=fopen(BAJAS,"rb");
    t_reg_indice dato_indice;
    t_reg_indice dato_baja;

    if(!indice && !baja) // muy mal, vago
        return 0;

    fread(&dato_indice, sizeof(t_reg_indice),1,indice);
    while(!feof(indice))
    {
        if(!poner_lista_en_orden(lIndice,&dato_indice,comparar))
            return 0;
        fread(&dato_indice, sizeof(t_reg_indice),1,indice);
    }
    fclose(indice);


    fread(&dato_baja,sizeof(t_reg_indice),1,baja);
    while(!feof(baja))
    {
        if(!poner_lista_al_final(lBajas,&dato_baja))
            return 0;
        fread(&dato_baja,sizeof(t_reg_indice),1,baja);
    }
    fclose(baja);

    return 1;
}


char menu(const char matriz[][TAM_MENU],const char *titulo)
{
    char opcion;
    int i;
    int flag=0;

    printf("%s\n", titulo);
    fflush(stdin);
    for(i=0;i<strlen(matriz[0]);i++)
    {
        printf("%c - %s\n",matriz[0][i], matriz[i+1]);
    }

    do{
        fflush(stdin);
        printf("\nSeleccion una opcion: ");
        scanf("%c",&opcion);
        opcion=toupper(opcion);

        for(i=0;i<strlen(matriz[0]);i++)
        {
            if(opcion==matriz[0][i])
            {
                flag=1;
                break;
            }
        }
    }while(!flag);

    return opcion;
}


int ingresar_alumno(t_lista *lista, const char *OK, int ubicacion, const t_fecha *fecha_proceso)
{
    t_reg_indice nuevo;
    t_alumno alumno_nuevo;
    int errores[10];
    int i;

    do
    {
        printf("DNI de alumno a dar de alta: ");
        scanf("%ld", &alumno_nuevo.DNI);
    }while(!validar_dni(alumno_nuevo.DNI));

    nuevo.dni=alumno_nuevo.DNI;

    if(buscar_en_lista(lista,&nuevo, comparar))
    {
        printf("El alumno ya esta ingresado\n");
        return ubicacion;
    }

    ingresar_datos_alumno(&alumno_nuevo);


    lista_errores(&alumno_nuevo,errores, fecha_proceso);

    //comprobar si esta bien ingresado
    if(!comprobar_errores(errores))
    {
        printf("\nDatos mal ingresados\n");
        return ubicacion;
    }

    /** se pone al final, sea "ab"**/
    if(!grabar_en_archivo(&alumno_nuevo,ARCHALUMNOK))
    {
        printf("Error con archivo\n");
        return ubicacion;
    }

    ubicacion++;

    nuevo.nro_reg=ubicacion;

    poner_lista_en_orden(lista, &nuevo, comparar);

    return ubicacion;
}

int dar_de_baja_alumno(t_lista *lista_R, t_lista *lista_B, const char *OK)
{
    long dni=0;

    while(!validar_dni(dni))
    {
        printf("DNI de alumno a dar de baja: ");
        scanf("%ld", &dni);
    }

    //si la busqueda da la posicion, se edita


    // eliminar_de_lista(lista, registro)
    // poner_lista_al_final(lista_baja, registro)
    // editar_en_archivo(ARCHIVOOK, registro->posicion, t_alumno)
            // se cambia R por B


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



void ingresar_datos_alumno(t_alumno *alumno)
{
    int i;
    printf("\nIngrese los datos del alumno: \n");

    printf("\nApellido y nombre (separados por ','): ");
    fflush(stdin);
    fgets(alumno->apyn, 40, stdin);

    fflush(stdin);

    ingresar_fecha(&alumno->fNacimiento,"Fecha de nacimiento: ");

    fflush(stdin);
    printf("Sexo: ");
    scanf("%c",&alumno->sexo);
    fflush(stdin);

    ingresar_fecha(&alumno->fIngreso,"Fecha de ingreso: ");


    fflush(stdin);
    printf("Carrera: ");
    fgets(alumno->carrera, 4, stdin);

    for(i=0;i<4;i++)
    {
        alumno->carrera[i] = toupper(alumno->carrera[i]);
    }


    fflush(stdin);
    printf("Materias aprobadas: ");
    scanf("%d",&alumno->mAprobadas);
    fflush(stdin);

    ingresar_fecha(&alumno->fUltimaMateria,"Fecha de ultima materia aprobada: ");

    alumno->estado='R';

    alumno->fBaja.dia=31;
    alumno->fBaja.mes=12;
    alumno->fBaja.anio=9999;
}
