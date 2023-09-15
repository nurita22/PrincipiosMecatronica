#define PIN_ANALOGO 15 //Definir el pin 15 como análogo
#define PWM_PIN 16 //Definir el pin 16 como pwm

int lectura; //declarar la variable 
int pwmVal;
void setup() {
  pinMode(PWM_PIN, OUTPUT); //Inicializar PWM_PIN como salida
  Serial.begin(9600); //Inicilaizar el serial a 9600 baudios
}

void loop() {
  lectura = analogRead(PIN_ANALOGO); //leemos la entrada del pin análogo (el fotorresistor)

  pwmVal = map(lectura,300,1500,0,255); //mapeamos los valores del fotorresistor a valores para el LED

  //Si el valor es negativo, convertirlo a cero
  if (pwmVal < 0){ 
    pwmVal = 0;
  }

  analogWrite(PWM_PIN,pwmVal); //darle el valor mapeado al LED (PWM_PIN)

  //Imprimir valores originales y mapeados para corroborar que funcione correctamente
  Serial.print("Valor original: "); 
  Serial.print(lectura);
  Serial.print("Valor mapeado:  ");
  Serial.println(pwmVal);
}
