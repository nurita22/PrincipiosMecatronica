//Definimos los pines con otros nombres
#define VERDE_A 33
#define VERDE_B 32
#define AMARILLO_A 27
#define AMARILLO_B 14
#define ROJO_A 23
#define ROJO_B 21
#define PR_PIN 25
#define TRIG_PIN 26
#define ECHO_PIN 34
#define IR_PIN 35 //En el sensor se llama OUT
#define TOUCH_A 12
#define TOUCH_B 4
#define TOUCH_C 15

//Declaramos las banderas que se activarán con el touch como booleanos
bool banderas[3] = {1,0,0};

void setup() {
  //Inicializamos los LEDs como salidas
  pinMode(VERDE_A,OUTPUT);
  pinMode(VERDE_B,OUTPUT);
  pinMode(AMARILLO_A,OUTPUT);
  pinMode(AMARILLO_B,OUTPUT);
  pinMode(ROJO_A,OUTPUT);
  pinMode(ROJO_B,OUTPUT);

  //Inicializamos los TRIG y ECHO del sensor ultrasónico como salidas
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);

  //Inicializamos el OUT del sensor infrarrojo como salida
  pinMode(IR_PIN,INPUT);

  //Inicializamos el serial a 115200 baudios
  Serial.begin(115200);

}

//Creamos la función para los LEDs de la primera rutina
void ledPrimeraRutina(){
  //Declaramos los valores de los LEDs como 255 para prendido y 0 para apagado
  int todosPrendidos[] = {255,255,255,255,255,255};
  int todosApagados[] = {0,0,0,0,0,0};

  //Les añadimos un delay de 0.1 segundos para que parpadeen a 5Hz
  ledControlIndividual(todosPrendidos);
  delay(100);
  ledControlIndividual(todosApagados);
  delay(100);
}

//Creamos función para poder controlar a todos los LEDs a la vez (con 1 y 0 nada más)
void ledControles(int senial){
  digitalWrite(VERDE_A,senial);
  digitalWrite(VERDE_B,senial);
  digitalWrite(AMARILLO_A,senial);
  digitalWrite(AMARILLO_B,senial);
  digitalWrite(ROJO_A,senial);
  digitalWrite(ROJO_B,senial);
}

//Creamos la función para la primera rutina
void primeraRutina(){
  int irInput;
  int todosApagados[] = {0,0,0,0,0,0};

  irInput = digitalRead(IR_PIN); //Leemos el OUT del infrarrojo

  //Imprimimos el OUT del infrarrojo (0 si detecta obstáculo, 1 si no lo detecta)
  Serial.print("Obst:  ");
  Serial.print(irInput);
  Serial.println(" -- Dist: 0 0 0 0 0 0 -- Lum: 0%"); //Imprimimos los demás valores en cero

  //Si se detecta obstáculo se activa la rutina de LEDs en la que parpadean a 5Hz
  if (irInput == 0){
    ledPrimeraRutina();
  }else{
    ledControlIndividual(todosApagados); //Si no se detecta obstáculo, todos los LEDs se apagan
  }
}

//Creamos la segunda rutina
void segundaRutina(){
  double lecturaDist;
  int ledEstados[6]; //Definimos ledEstados como un vector de tamaño 6

  lecturaDist = distancia(); //Declaramos la lecturaDist como la distancia en cm del ultrasónico que regresa la función distancia (definida más abajo)

  //Realizaremos una condicional para cada 5cm que detecte el ultrasónico
  if (lecturaDist <= 5){ //Primeros 5cm

    for (int i=0;i<6;i++){
      ledEstados[i] = 0;
    }

  }
  
  if (lecturaDist >5 && lecturaDist<=10){ //De 5 a 10cm
    //Se prende el primer LED
    ledEstados[0] = 255;

    for (int i=1;i<6;i++){
      ledEstados[i] = 0;
    }

  }
  
  if (lecturaDist >10 && lecturaDist<=15){ //De 10 a 15cm
    //Se prenden los primeros 2 LEDs
    ledEstados[0] = 255;
    ledEstados[1] = 255;

    for (int i=2;i<6;i++){
      ledEstados[i] = 0;
    }

  }
  
  if (lecturaDist >15 && lecturaDist<=20){ //De 15 a 20cm
    //Se prenden los primeros 3 LEDs
    ledEstados[0] = 255;
    ledEstados[1] = 255;
    ledEstados[2] = 255;

    for (int i=3;i<6;i++){
      ledEstados[i] = 0;
    }

  }
  
  if (lecturaDist >20 && lecturaDist<=25){ //De 20 a 25cm
    //Se prenden los primeros 4 LEDs
    ledEstados[0] = 255;
    ledEstados[1] = 255;
    ledEstados[2] = 255;
    ledEstados[3] = 255;

    for (int i=4;i<6;i++){
      ledEstados[i] = 0;
    }

  }
  
  if (lecturaDist >25 && lecturaDist<=30){ //De 25 a 30cm
    //Se prenden los primeros 5 LEDs
    ledEstados[0] = 255;
    ledEstados[1] = 255;
    ledEstados[2] = 255;
    ledEstados[3] = 255;
    ledEstados[4] = 255;

    for (int i=5;i<6;i++){
      ledEstados[i] = 0;
    }

  }
  
  if (lecturaDist >30){ //Más de 30cm
    //Se prenden todos los LEDs
    ledEstados[0] = 255;
    ledEstados[1] = 255;
    ledEstados[2] = 255;
    ledEstados[3] = 255;
    ledEstados[4] = 255;
    ledEstados[5] = 255;
  }

  Serial.print("Obst: 0 -- Dist: "); //Imprimir el valor de la primera rutina en cero
  for (int i = 0; i<6; i++){

    if (ledEstados[i] == 255) //Imprimimos los valores de qué LEDs están prendidos como 1
      Serial.print(1); 
    else
      Serial.print(0); //Imprimimos los valores de los LEDs apagados como cerp
    Serial.print(" ");
  }
  ledControlIndividual(ledEstados); //Prender los LEDs de acuerdo al arreglo definido anteriomente mediante la función definida abajo

  Serial.println("-- Lum: 0%"); //Imprimir el valor de la tercera rutina en cero
}

//Creamos una función para controlar cada LED analógicamente con pwm
void ledControlIndividual(int arreglo[]){
  //Mandas a cada LED el valor del arreglo (de 0 a 255) para que se iluminen
  analogWrite(VERDE_B,arreglo[0]);
  analogWrite(VERDE_A,arreglo[1]);
  analogWrite(AMARILLO_A,arreglo[2]);
  analogWrite(AMARILLO_B,arreglo[3]);
  analogWrite(ROJO_A,arreglo[4]);
  analogWrite(ROJO_B,arreglo[5]);

}

//Creamos la función distancia, que medirá la distancia en cm para el sensor ultrasónico
int distancia(){
  int duracion;
  int calculoDistancia;

  digitalWrite(TRIG_PIN, 0); //Reseteamos el TRIG
  delayMicroseconds(2); //Esperamos 2ms

  digitalWrite(TRIG_PIN, 1); //Mandamos una señal positiva del TRIG
  delayMicroseconds(10); //Esperamos 10ms
  digitalWrite(TRIG_PIN, 0); //Reseteamos TRIG nuevamente

  duracion = pulseIn(ECHO_PIN, 1); //Regresa el tiempo que tarda en llegar el rebote de la señal del TRIG a ECHO
  calculoDistancia = duracion * 0.0343 / 2; //Calculamos la distancia en centímentros ponderando por la velocidad del sonido
  delay(50); //Espoeramos 50ms

  return calculoDistancia; //Regresas la distancia en cm que midió el sensor ultrasónico
}

//Creamos la función ledControlPwm para controlar los LEDs individualmente de acuerdo al valor de la fotorresistencia
void ledControlPwm(int entrada){ //Recibe el valor de la fotorresistencia
  int arregloLeds[6]; //Definimos un vector de tamaño 6

  float valorMapeado = map(entrada, 0, 100, 600, 0); //Mapear el valor de la fotorresistencia en valores más amplios e inversos

  //Dividimos los valores mapeados de la fotorresistencia en rangos equitativos y los mapeamos a valores para prender cada LED (0 a 255)
  //A su vez guardamos cada uno de los valores para los LEDs en un espacio del vector
  arregloLeds[0] = map(valorMapeado, 0,60, 0,255);
  arregloLeds[1] = map(valorMapeado, 61,120, 0,255);
  arregloLeds[2] = map(valorMapeado, 121,180, 0,255);
  arregloLeds[3] = map(valorMapeado, 181,240, 0,255);
  arregloLeds[4] = map(valorMapeado, 241,300, 0,255);
  arregloLeds[5] = map(valorMapeado, 301,360, 0,255);

  for(int i = 0; i< 6; i++){
    if (arregloLeds[i]> 255){ //Si el valor es mayor a 255 bajarlo a 255
      arregloLeds[i] = 255;
    }

    if (arregloLeds[i] < 0){ //Si el valor es menor a 0 subirlo a 0
      arregloLeds[i] = 0;
    }
  }

  ledControlIndividual(arregloLeds); //Metemos el arreglo a la función ledControlIndividual (definida más arriba) para controlar cada LED analógicamente con pwm
}

//Creamos la tercera rutina
void tercerRutina(){
  //Declaramos la lectura del fotorresistor
  int prLectura;
  //Definimos el máximo y el mínimo del fotorresistor
  int minAnalogo = 1300;
  int maxAnalogo = 4095;
  
  int valorSerial, ledValor;

  prLectura = analogRead(PR_PIN); //Asignamos a prLectura el valor del fotorresistor
  valorSerial = map(prLectura,minAnalogo,maxAnalogo,0,100); //Lo mapeamos en valores del 0 al 100 para que escriba ese procentaje en el serial

  if (valorSerial < 0){ //Si es menor a cero subir el valor a 0
    valorSerial = 0;
  }

  Serial.print("Obst: 0 -- Dist: 0 0 0 0 0 0 -- Lum: "); //Imprimir los valores de las otras dos rutinas en cero
  Serial.print(valorSerial); //Imprimir el valor del porcentaje en el serial
  Serial.println("%"); //Imprimir signo de %

  delay(50); //Esperar 50ms
  ledControlPwm(valorSerial); //Enviamos el porcentaje a la función ledControlPwm para controlar los LEDs proporcionalmente
}

void loop() {
  //Creamos una condición para activar cada rutina mediante una resistencia capacitiva de contacto
  if (touchRead(TOUCH_A) < 50 && touchRead(TOUCH_B) >= 50 && touchRead(TOUCH_C) >= 50){
    //Si tocamos el primer touch, se activa la primera bandera
    banderas[0] = 1;
    banderas[1] = 0;
    banderas[2] = 0;
  }
  
  if (touchRead(TOUCH_A) >= 50 && touchRead(TOUCH_B) < 50 && touchRead(TOUCH_C) >= 50){
    //Si tocamos el segundo touch, se activa la segunda bandera
    banderas[0] = 0;
    banderas[1] = 1;
    banderas[2] = 0;
  }
  
  if (touchRead(TOUCH_A) >= 50 && touchRead(TOUCH_B) >= 50 && touchRead(TOUCH_C) < 50){
    //Si tocamos el tercer touch, se activa la tercera bandera
    banderas[0] = 0;
    banderas[1] = 0;
    banderas[2] = 1;
  }

  if (banderas[0]) //Si se activa la primera bandera, se activa la primera rutina
    primeraRutina();
  if (banderas[1]) //Si se activa la segunda bandera, se activa la segunda rutina
    segundaRutina();
  if (banderas[2]) //Si se activa la tercera bandera, se activa la tercer rutina
    tercerRutina();
}
