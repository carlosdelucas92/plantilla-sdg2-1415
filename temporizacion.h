//------------------------------------------------------------------------------
// temporizacion.h
//
//  Descripci�n: Este m�dulo permite la inicializaci�n, configuraci�n y control
//               de las interrupciones del m�dulo b�sico del proyecto.
//
// Autores: Equipo docente de SDII
//------------------------------------------------------------------------------

#ifndef __TEMP_H__
#define __TEMP_H__

//------------------------------------------------------------------------------
// ZONA DE DEFINICI�N DE ETIQUETAS
//------------------------------------------------------------------------------

#define V_BASE    0x40 // Direcci�n de inicio de los vectores de interrupci�n
#define DIR_VTMR0 4*(V_BASE+5) // Direcci�n del vector de TMR0
#define DIR_VTMR1 4*(V_BASE+6) // Direcci�n del vector de TMR1

#define FREC_INT0 4000      // Frec. de interr. TMR0 = 8000 Hz (125us)

#define PRESCALADO_TMR0 2
#define CNT_INT0 MCF_CLK/(FREC_INT0 * PRESCALADO_TMR0 * 16)  // Valor de precarga del temporizador de interrupciones TRR0
#if CNT_INT0 > 0xFFFF
#error PRESCALADO_TMR0 demasiado peque�o para esa frecuencia (CNT_INT0 > 0xFFFF)
#endif

#define BORRA_REF 0x0002     // Valor de borrado de interr. pendientes de tout0 para TER0

#define OFFSET 0x800
#define N_FRECS 20
#define NUM_MUESTRAS_SIN10 400
#define COS_BIAS NUM_MUESTRAS_SIN10 / 4

#define REFRESCO 25                          // Frecuencia de refresco (en Hz) del subsistema de visualizaci�n 
#define N_COMP FREC_INT0 / (REFRESCO * N_FRECS) 
#define N_NIVELES 32
#define DESESCALADO 10
#define N 80

//------------------------------------------------------------------------------
// ZONA DE DEFINICI�N DE FUNCIONES
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// void timers_init(void)
//
// Descripci�n:
//   Funci�n de inicializaci�n del TIMER0 y TIMER1
//
//  Argumentos de Entrada: VOID
//  Argumentos de Salida: VOID
//
// Autores: Equipo docente de SDII
//------------------------------------------------------------------------------
void timers_init (void);

//------------------------------------------------------------------------------
// void setICR1(void)
//
//  Descripci�n: Actualiza el vector ICR1 a 0x8888C888, donde se marca como no
//               pendiente la interrupci�n TIMER0 y se establece 
//               su prioridad como 3.
//
//  Argumentos de Entrada: VOID
//  Argumentos de Salida: VOID
//
// Autores: Equipo docente de SDII
//------------------------------------------------------------------------------
void ICR1_set(void);

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
void DFT_init (void);

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
inline void ActualizaPunterosABases(int frec);

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
inline ULONG EstimaDFTModulo2 (int dft_sin, int dft_cos);

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
inline int ConversionAdB (int dft_mod2);

//------------------------------------------------------------------------------
// void rutina_tout0(void)
//
// Descripci�n: Funci�n de atenci�n a la interrupci�n interna TOUT0.
//              Esta funci�n toma una muestra cada 250us (4 kHz) y estima el 
//              m�dulo de la DFT para un conjunto de N_FRECS frecuencias.
//
//              El m�dulo de la DFT es enviado a trav�s del DAC al subsistema 
//              externo de visualizaci�n (c. rampa + oscioscopio).
//
//  Argumentos de Entrada: VOID
//  Argumentos de Salida: VOID
//
// Autores: Equipo docente de SDII
//------------------------------------------------------------------------------
void rutina_tout0(void);


#endif
