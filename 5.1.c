#define MAXTECLAS 4
int teclado[];
int num=0;
int N;

void MenuConfiguracion(void){
	
	char tecla;
	tecla = teclado();


	//Opciones de la interfaz del usuario
	switch(tecla) {
    case 1:
      //numero de frec de interes 
      _print("Elija el numero de frecuencias de interes\n");
       nFrecs = componNumero();
      _print("El valor de las frecuencias de interes es %d\n",nFrecs);    
      break;
    case 2:
      //Valor de las frecuencias de interes
      _print("Elija el valor de las frecuencias de interes\n");
      _print("Deben ser numeros multiplos de 10\n");
      _print("Y en el rango 50-->2000Hz\n");
      for( i=0; i< nFrecs; i++){
        paso[i]= componNumero()/10;

      }
      break;
    case 2:
      //longitud de la ventana de analisis
      _print("Elija el valor de la ventana de analisis\n");
      ventAnalisis = componNumero();
      break;
    case 3:
      //tiempo de barrido
      _print("Elija el valor del tiempo de barrido\n");
      tBarrido = componNumero();
    break;
    default:
      _printf("\n --- Opción elegida érronea. Vuelva a intentarlo. --- \n\n");
      break;
  }

	
}


void recogeNumeros (void) {
  // el cero en ASCII es 48
  
  int numero;
  while( tecla=! F || num< MAXTECLAS){
    numero = teclado();
    teclado[num]= (int)(numero - 0)
        num++;
  }
}

void componNumero (void){
  
  while (i>0){
    N+= (int) (teclado[num]- 0)*10^num;
    num--;

  } 
  
}

void numeros