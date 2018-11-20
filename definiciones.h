#ifndef DEFINICIONES_H_INCLUDED
#define DEFINICIONES_H_INCLUDED

#define esBisiesto(x)   (((x)%4==0 && (x)%100==0) || ((x)%400==0))

#define FECHAERRORANIO  3
#define FECHAERRORMES   2
#define FECHAERRORDIA   1
#define FECHAOK         0


#define ARCHDATOS       "datos.txt"
#define ARCHALUMNOK     "alumnosOK.dat"
#define ARCHINDICEOK    "indiceOK.dat"
#define ARCHIDICEBAJA   "indiceBAJA.dat"



#endif // DEFINICIONES_H_INCLUDED
