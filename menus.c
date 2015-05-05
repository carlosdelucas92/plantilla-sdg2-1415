//
//
// REVISAR TODOS LOS NOMBRES
//
//


#include "menus.h"
#include "temporizacion.h"

//#include "m5272lcd.c"
#define MAXTECLAS 4

int teclado[];
int ventAnalisis;
int nFrecs;
int frecNow;

int N;
int paso[];
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
//-------------------------------------------------------------------------------
//
//
//
//
//-------------------------------------------------------------------------------

void MenuConfiguracion(void){
	
	char tecla;
	tecla = teclado();


	//Opciones de la interfaz del usuario
	switch(tecla) {
    case 1:
      //numero de frec de interes 
      _print("Elija el numero de frecuencias de interes\n");
       nFrecs = recogeNumeros();
      _print("El valor de las frecuencias de interes es %d\n",nFrecs);    
      break;
    case 2:
      //Valor de las frecuencias de interes
      _print("Elija el valor de las frecuencias de interes\n");
      _print("Deben ser numeros multiplos de 10\n");
      _print("Y en el rango 50-->2000Hz\n");
      int frecNow=0;
      // tocar frecNow para ver como recorrer mejor el bucle quillo
      while(frecNow< nFrecs){
      //for( i=0; i< nFrecs; i++){
        paso[frecNow]= recogeNumeros()/10;
        frecNow++;
      }
      break;
      }
    case 3:
      //longitud de la ventana de analisis
      _print("Elija el valor de la ventana de analisis\n");
      ventAnalisis = recogeNumeros();
      break;
    case 4:
      //tiempo de barrido
      _print("Elija el valor del tiempo de barrido\n");
      tBarrido = recogeNumeros();
    break;
    default:
    	nFrecs=20;
    	ventAnalisis=80;
    	tBarrido= 2; // 2 ms falta pasarlo a unidades intrr
      _printf("\n --- Opción elegida érronea. Vuelva a intentarlo. --- \n\n");
      break;
  }

	
}


int recogeNumeros (void) {
  // el cero en ASCII es 48
  int num =0;
  int teclaConf = teclado();
  if (teclaConf == (A||B||C||D||E) || num == 0 ){
    _print("Has introducido un caracter no un numero, o puede que ningun numero")
  }
  while( teclaConf=! F || num< MAXTECLAS){
    teclado[num]= (int)(numero - 0);
        num++;
  }
  if ( teclaConf== F || num == MAXTECLAS){
    while (num>0){
    N+= (int) (teclado[num]*10^num);
    num--;
  }
  return N;
}