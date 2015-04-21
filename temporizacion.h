//------------------------------------------------------------------------------
// temporizacion.h
//
//  Descripción: Este módulo permite la inicialización, configuración y control
//               de las interrupciones del módulo básico del proyecto.
//
// Autores: Equipo docente de SDII
//------------------------------------------------------------------------------

#ifndef __TEMP_H__
#define __TEMP_H__

//------------------------------------------------------------------------------
// ZONA DE DEFINICIÓN DE ETIQUETAS
//------------------------------------------------------------------------------

#define V_BASE    0x40 // Dirección de inicio de los vectores de interrupción
#define DIR_VTMR0 4*(V_BASE+5) // Dirección del vector de TMR0
#define DIR_VTMR1 4*(V_BASE+6) // Dirección del vector de TMR1

#define FREC_INT0 4000      // Frec. de interr. TMR0 = 8000 Hz (125us)

#define PRESCALADO_TMR0 2
#define CNT_INT0 MCF_CLK/(FREC_INT0 * PRESCALADO_TMR0 * 16)  // Valor de precarga del temporizador de interrupciones TRR0
#if CNT_INT0 > 0xFFFF
#error PRESCALADO_TMR0 demasiado pequeño para esa frecuencia (CNT_INT0 > 0xFFFF)
#endif

#define BORRA_REF 0x0002     // Valor de borrado de interr. pendientes de tout0 para TER0

#define OFFSET 0x800
#define N_FRECS 20
#define NUM_MUESTRAS_SIN10 400
#define COS_BIAS NUM_MUESTRAS_SIN10 / 4

#define REFRESCO 25                          // Frecuencia de refresco (en Hz) del subsistema de visualización 
#define N_COMP FREC_INT0 / (REFRESCO * N_FRECS) 
#define N_NIVELES 32
#define DESESCALADO 10
#define N 80

//------------------------------------------------------------------------------
// ZONA DE DEFINICIÓN DE FUNCIONES
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// void timers_init(void)
//
// Descripción:
//   Función de inicialización del TIMER0 y TIMER1
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
//  Descripción: Actualiza el vector ICR1 a 0x8888C888, donde se marca como no
//               pendiente la interrupción TIMER0 y se establece 
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
// Descripción:
//   Función de inicialización de los recursos empleados en la estimación de
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
//  Descripción: Actualiza los punteros pSin[frec] y pCos[frec] a la dirección
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
//  Descripción: 
//
//  Argumentos de Entrada: dft_sin, dft_cos (acumuladores partes real e imaginaria)
//  Argumentos de Salida:  Módulo al cuadrado de la DFT 
//
// Autores: Equipo docente de SDII
//------------------------------------------------------------------------------
inline ULONG EstimaDFTModulo2 (int dft_sin, int dft_cos);

//------------------------------------------------------------------------------
// inline int ConversionAdB (int dft_mod2)
//
//  Descripción: 
//
//  Argumentos de Entrada: dft_mod2 (módulo^2 de la DFT en natural
//  Argumentos de Salida:  Módulo de la DFT proporcional a dB (en escala del DAC)
//
// Autores: Equipo docente de SDII
//------------------------------------------------------------------------------
inline int ConversionAdB (int dft_mod2);

//------------------------------------------------------------------------------
// void rutina_tout0(void)
//
// Descripción: Función de atención a la interrupción interna TOUT0.
//              Esta función toma una muestra cada 250us (4 kHz) y estima el 
//              módulo de la DFT para un conjunto de N_FRECS frecuencias.
//
//              El módulo de la DFT es enviado a través del DAC al subsistema 
//              externo de visualización (c. rampa + oscioscopio).
//
//  Argumentos de Entrada: VOID
//  Argumentos de Salida: VOID
//
// Autores: Equipo docente de SDII
//------------------------------------------------------------------------------
void rutina_tout0(void);


#endif
