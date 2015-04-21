//------------------------------------------------------------------------------
// temporizacion.c
//
//  Descripci�n: Este m�dulo permite la inicializaci�n, configuraci�n y control
//               de las interrupciones del m�dulo b�sico del proyecto.
//
// Autores: Equipo docente de SDII
//------------------------------------------------------------------------------

#include "temporizacion.h"


//------------------------------------------------------------------------------
// ZONA DE DEFINICI�N DE ESTRUCTURAS Y VARIABLES
//------------------------------------------------------------------------------

int dft_sin[N_FRECS];
int dft_cos[N_FRECS];
int *pSin[N_FRECS], *pCos[N_FRECS];
ULONG dft_mod_DB[N_FRECS];

static int sin10[NUM_MUESTRAS_SIN10] = {0, 12, 25, 38, 51, 64, 77, 89, 102, 115, 128, 140, 153, 166, 178, 191, 203, 216, 228, 240, 253, 265, 277, 289, 301, 313, 325, 336, 348, 360, 371, 383, 394, 405, 416, 427, 438, 449, 460, 470, 481, 491, 501, 511, 521, 531, 541, 551, 560, 569, 579, 588, 596, 605, 614, 622, 630, 639, 647, 654, 662, 669, 677, 684, 691, 698, 704, 711, 717, 723, 729, 735, 741, 746, 751, 756, 761, 766, 770, 774, 778, 782, 786, 790, 793, 796, 799, 802, 804, 806, 809, 810, 812, 814, 815, 816, 817, 818, 818, 819, 819, 819, 818, 818, 817, 816, 815, 814, 812, 811, 809, 807, 804, 802, 799, 796, 793, 790, 786, 783, 779, 775, 771, 766, 761, 757, 752, 746, 741, 736, 730, 724, 718, 712, 705, 698, 692, 685, 678, 670, 663, 655, 647, 639, 631, 623, 615, 606, 597, 588, 579, 570, 561, 552, 542, 532, 522, 512, 502, 492, 482, 471, 461, 450, 439, 428, 417, 406, 395, 384, 372, 361, 349, 338, 326, 314, 302, 290, 278, 266, 254, 242, 229, 217, 204, 192, 179, 167, 154, 142, 129, 116, 103, 91, 78, 65, 52, 39, 27, 14, 1, -12, -25, -38, -51, -63, -76, -89, -102, -115, -127, -140, -153, -165, -178, -190, -203, -215, -228, -240, -252, -264, -277, -289, -301, -313, -324, -336, -348, -360, -371, -382, -394, -405, -416, -427, -438, -449, -460, -470, -481, -491, -501, -511, -521, -531, -541, -551, -560, -569, -579, -588, -597, -605, -614, -622, -631, -639, -647, -655, -662, -670, -677, -684, -691, -698, -705, -711, -718, -724, -730, -735, -741, -746, -752, -757, -762, -766, -771, -775, -779, -783, -787, -790, -794, -797, -800, -802, -805, -807, -809, -811, -813, -815, -816, -817, -818, -819, -819, -820, -820, -820, -819, -819, -818, -817, -816, -815, -813, -812, -810, -808, -806, -803, -800, -798, -794, -791, -788, -784, -780, -776, -772, -768, -763, -758, -753, -748, -743, -737, -731, -725, -719, -713, -707, -700, -693, -686, -679, -672, -665, -657, -649, -641, -633, -625, -616, -608, -599, -590, -581, -572, -563, -554, -544, -534, -524, -515, -504, -494, -484, -473, -463, -452, -441, -431, -420, -408, -397, -386, -375, -363, -351, -340, -328, -316, -304, -292, -280, -268, -256, -244, -231, -219, -207, -194, -182, -169, -156, -144, -131, -118, -106, -93, -80, -67, -55, -42, -29, -16};
static int paso_frecs[N_FRECS] =  {5, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170,180, 190};

//------------------------------------------------------------------------------
// ZONA DE IMPLEMENTACI�N DE FUNCIONES
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// void timers_init(void)
//
// Descripci�n:
//   Funci�n de inicializaci�n del TIMER0
//
//  Argumentos de Entrada: VOID
//  Argumentos de Salida: VOID
//
// Autores: Equipo docente de SDII
//------------------------------------------------------------------------------
void timers_init (void)
{
	mbar_writeByte(MCFSIM_PIVR,V_BASE);			   // Fija comienzo de vectores de interrupci�n en V_BASE.

	ACCESO_A_MEMORIA_LONG(DIR_VTMR0)= (ULONG)_prep_TOUT0;      // Escribimos la direcci�n de la funci�n para TMR0
	mbar_writeShort(MCFSIM_TMR0, (PRESCALADO_TMR0-1)<<8|0x3D); // TMR0: PS=1-1=0 CE=00 OM=1 ORI=1 FRR=1 CLK=10 RST=1
	mbar_writeShort(MCFSIM_TCN0, 0x0000);		           // Ponemos a 0 el contador del TIMER0
	mbar_writeShort(MCFSIM_TRR0, CNT_INT0);	                   // Fijamos la cuenta final del contador

}

//------------------------------------------------------------------------------
// void setICR1(void)
//
//  Descripci�n: Actualiza el vector ICR1 a 0x8888CB88, donde se marcan como no
//               pendientes las interrupciones TIMER0 TIMER1 y se establecen
//				 sus prioridades como 4 y 3 respectivamente.
//               Fijamos mayor prioridad al TIMER 0 para que podamos emplear el
//               DAC respetando la temporizaci�n.
//
//  Argumentos de Entrada: VOID
//  Argumentos de Salida: VOID
//
// Autores: Equipo docente de SDII
//------------------------------------------------------------------------------
void ICR1_set(void)
{
	mbar_writeLong(MCFSIM_ICR1, 0x8888C888);
}

//------------------------------------------------------------------------------
// void DFT_init(void)
//
// Descripci�n:
//   Funci�n de inicializaci�n de los recursos empleados en la estimaci�n de
//   la DFT.
//
//  Argumentos de Entrada: VOID
//  Argumentos de Salida: VOID
//
// Autores: Equipo docente de SDII
//------------------------------------------------------------------------------
void DFT_init (void)
{
	int f = 0; 
	for (f = 0; f < N_FRECS; f++)
	{
		dft_sin[f] = dft_cos[f] = 0;
		dft_mod_DB[f] = 0;
		pSin[f] = sin10;
		pCos[f] = sin10 + COS_BIAS;
	}
}

//------------------------------------------------------------------------------
// void ActualizaPunterosABases(int frec)
//
//  Descripci�n: Actualiza los punteros pSin[frec] y pCos[frec] a la direcci�n
//               de la siguiente muestra del seno de 10Hz (sin10) que se debe 
//               emplear para la frecuencia frec.
//
//  Argumentos de Entrada: frec (frecuencia objetivo)
//  Argumentos de Salida: VOID
//
// Autores: Equipo docente de SDII
//------------------------------------------------------------------------------
inline void ActualizaPunterosABases(int frec)
{

	pSin[frec] += paso_frecs[frec];
	pCos[frec] += paso_frecs[frec];
	if ( pSin[frec] >= (sin10 + NUM_MUESTRAS_SIN10) ) // Check borders of circular buffer for sin
	{
		pSin[frec] -= NUM_MUESTRAS_SIN10;
	}

	if ( pCos[frec] >= (sin10 + NUM_MUESTRAS_SIN10) ) // Check borders of circular buffer for cos
	{
		pCos[frec] -= NUM_MUESTRAS_SIN10;
	}

}

//------------------------------------------------------------------------------
// inline ULONG EstimaDFTModulo2 (int dft_sin, int dft_cos)
//
//  Descripci�n: 
//
//  Argumentos de Entrada: dft_sin, dft_cos (acumuladores partes real e imaginaria)
//  Argumentos de Salida:  M�dulo al cuadrado de la DFT 
//
// Autores: Equipo docente de SDII
//------------------------------------------------------------------------------
inline ULONG EstimaDFTModulo2 (int dft_sin, int dft_cos)
{
	dft_sin = dft_sin >> DESESCALADO;
	dft_cos = dft_cos >> DESESCALADO;

	return (dft_sin * dft_sin) + (dft_cos * dft_cos);

}

//------------------------------------------------------------------------------
// inline int ConversionAdB (int dft_mod2)
//
//  Descripci�n: 
//
//  Argumentos de Entrada: dft_mod2 (m�dulo^2 de la DFT en natural
//  Argumentos de Salida:  M�dulo de la DFT proporcional a dB (en escala del DAC)
//
// Autores: Equipo docente de SDII
//------------------------------------------------------------------------------
inline int ConversionAdB (int dft_mod2)
{

	static int TablaLog [N_NIVELES] = {122, 245, 368, 491, 614, 737, 860, 983, 1105, 1228,
		1351, 1474, 1597, 1720, 1843, 1966, 2088, 2211, 2334, 2457,
		2580, 2703, 2826, 2949, 3072, 3194, 3317, 3440, 3563, 3686,
		3809, 3932};

	static ULONG Niveles[N_NIVELES] = {63095, 84924, 114304, 153849, 207075, 278715, 375140, 504923, 679607, 914724,
		1231182, 1657123, 2230422, 3002059, 4040653, 5438559, 7320085, 9852544, 13261133, 17848959,
		24023991, 32335339, 43522083, 58578997, 78845006, 106122250, 142836338, 192252044, 258763624, 348285572,
		468778561, 686492401};

	int i = 0;
	int aux = 0;

	for (i = 0; i < N_NIVELES; i++)
	{
		if ( dft_mod2 >= Niveles[i] )
		{
			aux = TablaLog[i];
		}
		else {
			break;
		}
	} //end for

	return aux;
}


//------------------------------------------------------------------------------
// void rutina_tout0(void)
//
// Descripci�n: Funci�n de atenci�n a la interrupci�n interna TOUT0.
//              Esta funci�n toma una muestra cada 125us (8kHz)
//
//  Argumentos de Entrada: VOID
//  Argumentos de Salida: VOID
//
// Autores: Equipo docente de SDII
//------------------------------------------------------------------------------

void rutina_tout0(void)
{
	static UBYTE n       = 0;
	static UINT  nComp   = 0;
	static UBYTE OutFrec = 0;

	ULONG aux_dft_mod2 = 0;

	int muestra = 0;

	UBYTE  f = 0;

	static int Pulso_ON = FALSE;

	mbar_writeShort(MCFSIM_TER0,BORRA_REF); // Reset del bit de fin de cuenta

	if (Pulso_ON)
	{
		set16_puertoS (0x0000);
		Pulso_ON = FALSE;
	}

	// LEEMOS DATO DEL ADC
	muestra = ADC_dato();

	// 
	for (f = 0; f < N_FRECS; f++)
	{
		// ACUMULA COMPONENTES REAL E IMAGINARIA DE LA dft USANDO MUESTRA ACTUAL
		dft_sin[f] += muestra * *(pSin[f]);
		dft_cos[f] += muestra * *(pCos[f]);

		// ACTUALIZA PUNTEROS A LA SIGUIENTE MUESTRA DE CADA BASE (SENOS Y COSENOS DE UNA FREC. F)
		ActualizaPunterosABases(f);
	} //for f

	// SI SE HAN PROCESADO N MUESTRAS, SE ESTIMA EL M�DULO^2 Y CONVERTIMOS a DB
	if (n >= N)
	{
		for (f = 0; f < N_FRECS; f++)
		{
			// SE ESTIMA EL M�DULO AL CUADRADO DE LA DFT
			aux_dft_mod2  = EstimaDFTModulo2(dft_sin[f], dft_cos[f]);

			// CONVIERTE EL M�DULO AL CUADRADO AL M�DULO EN dB 
			dft_mod_DB[f] = ConversionAdB (aux_dft_mod2);

			// RESET ACUMULADORES DFT
			dft_sin[f] = dft_cos[f] = 0;

			// RESET DE PUNTEROS A CADA BASE (SENOS Y COSENOS DE UNA FREC. F)
			pSin[f]  = sin10;
			pCos[f]  = sin10 + COS_BIAS;
		}

		n = 0;  // RESET DE VENTANA DE AN�LISIS DE LA DFT
		flag++; // INFORMAMOS A BUCLEMAIN PARA QUE MUESTRE POR LA PANTALLA DEL TERMINAL
	}
	else
	{
		n++;
	}


	// SI HAN TRANSCURRIDO T_COMP SEGUNDOS (N_COMP muestras)
	if (nComp >= N_COMP)
	{
		nComp = 0;
		if (OutFrec == 0)
		{
			Pulso_ON = TRUE;
			set16_puertoS (0x0001);
		}
		// SE ENV�A EL MOD DE LA SIGUIENTE FRECUENCIA A VISUALIZAR
		DAC_dato (dft_mod_DB[OutFrec]);

		OutFrec++;
		if (OutFrec >= N_FRECS)
			OutFrec = 0;

	}
	else
		nComp++;

} // end rutina_tout0 ()


//----------------------------------------------------------------
// Definici�n del resto de rutinas de atenci�n a la interrupci�n
// Es necesario definirlas aunque est�n vac�as
void rutina_int1(void){}
void rutina_int2(void){}
void rutina_int3(void){}
void rutina_int4(void){}
void rutina_tout1(void){}
void rutina_tout2(void){}
void rutina_tout3(void){}
