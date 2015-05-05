//------------------------------------------------------------------------------
//template.c
//
// M�dulo_B�sico_1415
//
//  Descripci�n: https://moodle.upm.es/titulaciones/oficiales/course/view.php?id=5484
//
// Autores: Equipo docente de SDII
//------------------------------------------------------------------------------

#include "m5272.h"
#include "m5272lib.h"
#include "printf.h"
#include "m5272adc_dac.h"
#include "temporizacion.h"
#include "menus.h"
//#include "teclado.h"

#define MUESTRA_CADA_CIEN 100

int flag;

extern int paso_frecs[N_FRECS];
extern ULONG dft_mod_DB[N_FRECS];


//------------------------------------------------------
// void __init(void)
//
// Descripci�n:
//   Funci�n por defecto de inicializaci�n del sistema
//
// Autores: Equipo docente de SDII
//------------------------------------------------------
void __init(void)
{
	cli();
	
	flag = 0;

	DFT_init();      // Inializamos recurso para la estimaci�n de la DFT 
	DAC_ADC_init();  // Inicializamos el ADC y el DAC 
	ICR1_set();      // Fijamos prioridad de cada una de las interrupciones
	timers_init ();  // Inicializamos la rutinas de atenci�n a las interrupciones internas TOUT0 y TOUT1

	sti();           // Se activan las interrupciones

	output("COMIENZA EL PROGRAMA\r\n\n");

}

//------------------------------------------------------
// void bucleMain(void)
//
// Descripci�n:
//   Funci�n del programa principal. Ofrece informaci�n
//  por pantalla cuando se estima la DFT de una ventana.
//
// Autores: Equipo docente de SDII
//------------------------------------------------------

void bucleMain(void)
{

	int f = 0;

	//Opciones de la interfaz del usuario
  	switch(opcion) {
      case 0:
        MenuPrincipal();
        break;
      case 1:
        //CONFIGURAR POR TECLADO
      	MenuConfiguracion();
        break;
      case 2:
	    //LCD 
	    break;
      case 3:
        mezclarEntradas();     
	    break;
	  case 4:
	  //Microfono
      default:
        _printf("\n --- Opci�n elegida �rronea. Vuelva a intentarlo. --- \n\n");
        break;
    }


	

	if (flag >= MUESTRA_CADA_CIEN)
	{
		_printf("f (Hz)\t ");
		for (f = 0; f < N_FRECS; f++)
			_printf("\t %d", 10 * paso_frecs[f]);
		_printf ("\n");

		_printf("|H(jf)|  \t");
		for (f = 0; f < N_FRECS; f++)
			_printf("\t %d", dft_mod_DB[f]);
		_printf ("\n\n\n");

		flag = 0;
	}

} // End main


/* Inclusi�n de ficheros fuente del proyecto*/

#include "m5272lib.c"
#include "m5272gpio.c"		// Incluye funciones del m�dulo general de I/O
#include "printf.c"
#include "m5272adc_dac.c"
#include "menus.c"
#include "teclado.c"
#include "temporizacion.c"

