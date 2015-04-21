//
//
// REVISAR TODOS LOS NOMBRES
//
//


#include "Menus.h"
#include "temporizacion.h"

//#include "m5272lcd.c"

int opcion=0; 
// Variables para el mezclador

int entradaUno = 0;
int entradaDos = 0;
int entradasMezcladas = 0;



void MenuPrincipal(void) {

      char tecla; // Inicializacion de la variable.
 

      tecla = teclado(); // Leo la tecla pulsada del teclado matricial.

      switch (tecla) {
          case '1':
            //output (" Configuracion por teclado\n"); //CONFIGURAR POR TECLADO
            //opcion = 1;
            break;
          case '2':
            //opcion = 2; //EMOTICONOS
            break;
          case '3':
            opcion = 3;
            break;
          default:
            output("Tecla erronea\n");
            break;
      }
}


// -----------------------------------------------------
// void mezclarEntradas(void)
// 
// Descripcion:
// Menú para escoger si usamos el mezclador o no.
// Se ha implementado una variable (o flag) para evitar que el caso default ocurra infinitas veces.
//------------------------------------------------------ 

void mezclarEntradas(void) {

  int menuMezclar = 1;
  char tecla;
  

  while(menuMezclar == 1) {
    tecla = teclado();
    menuMezclar = 0;
    


    switch (tecla) {
      case '1':
        entradaUno = 1;
        entradaDos = 0;
        entradasMezcladas = 0;
        output("Entrada 1 escogida. \n");
        break;
      case '2':
        entradaUno = 0;
        entradaDos = 1;
        entradasMezcladas = 0;
        output("Entrada 2 escogida. \n");
        break;
      case '3':
        entradaUno = 1;
        entradaDos = 1;
        entradasMezcladas = 1;
        output("Mezclador escogido. \n");
        break;
      case 'F':
        opcion = 0;
        break;
      default:
        menuMezclar = 1;
        output("Tecla erronea\n");
        break;
    }
  }
}