#ifndef DEFINICIONES_H_INCLUDED
#define DEFINICIONES_H_INCLUDED

#define esBisiesto(x)   (((x)%4==0 && (x)%100==0) || ((x)%400==0))

#define FECHAERRORANIO  3
#define FECHAERRORMES   2
#define FECHAERRORDIA   1
#define FECHAOK         0

#define ARCHALUMNOK     "alumnos_OK.dat"
#define ARCHALUMNERROR  "alumnos_errores.txt"
#define ARCHINDICEOK    "indice_REGULAR.dat"
#define ARCHIDICEBAJA   "indice_BAJA.dat"

#define TAM             50
#define TAM_MENU        20

#define CORRECTO        1
#define ERROR           0

#define ORDEN           1
#define DESORDEN        0

#endif // DEFINICIONES_H_INCLUDED
