#define MAXTECLAS 4
int teclado[];

int N;

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
    case 2:
      //longitud de la ventana de analisis
      _print("Elija el valor de la ventana de analisis\n");
      ventAnalisis = recogeNumeros();
      break;
    case 3:
      //tiempo de barrido
      _print("Elija el valor del tiempo de barrido\n");
      tBarrido = recogeNumeros();
    break;
    default:
      _printf("\n --- Opción elegida érronea. Vuelva a intentarlo. --- \n\n");
      break;
  }

	
}


int recogeNumeros (void) {
  // el cero en ASCII es 48
  //Le hago un int recogeNum? posibilidad
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
