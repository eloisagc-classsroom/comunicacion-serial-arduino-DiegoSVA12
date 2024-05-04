// VARIABLES
const byte ledPin[] = {5,6,7,8}; // Pines a los que están conectados los LEDs
int ledPinLength = sizeof(ledPin) / sizeof(ledPin[0]); // Longitud del arreglo de pines LED
int option; // Variable para almacenar la opción seleccionada por el usuario

// CONFIGURACIÓN INICIAL
void setup()
{
  	for (int i=0; i<ledPinLength; i++) {
   		pinMode(ledPin[i], OUTPUT);  // Configura los pines LED como salidas
 	}
  Serial.begin(9600); // Inicia la comunicación serial a 9600 baudios
}

// BUCLE PRINCIPAL
void loop() {
  
  // Muestra las opciones al usuario
  Serial.println("Seleccione el orden del conteo binario");
  Serial.println("1. Ascendente ");
  Serial.println("2. Descendente ");
  
  // Espera a que el usuario seleccione una opción
  while (Serial.available()== 0)
  {
  }
  option = Serial.parseInt(); // Lee la opción ingresada por el usuario
  
  // Limpia el buffer de entrada de la comunicación serial
  while (Serial.available() > 0) {
    Serial.read();
  }

  // Realiza la acción correspondiente a la opción seleccionada
  if(option == 1){
      //Ascendente
    for (int num = 0; num < Exponente(ledPinLength); num++) { // Cuenta de 0 a (2^n - 1)
      Serial.print("Numero decimal: ");Serial.print(num);
      String numBit = "";
      for (int i = 0; i < ledPinLength; i++) {
        if (num & (1 << i)) { // Verifica si el bit en la posición i está encendido
          digitalWrite(ledPin[i], HIGH); // Enciende el LED si el bit está encendido
          numBit += "1";
        } else {
          digitalWrite(ledPin[i], LOW); // Apaga el LED si el bit está apagado
          numBit += "0";
        }

      }
      Serial.print(", Numero binario: ");Serial.println(invertirCadena(numBit)); // Muestra el número binario
      delay(500); // Espera medio segundo antes de mostrar el siguiente número
    }
  }
  
  else if (option == 2){
    //Descendente
    for (int num = Exponente(ledPinLength) - 1; num >= 0; num--) {
      Serial.print("Numero decimal: ");Serial.print(num);
      String numBit = "";
      for (int i = 0; i < ledPinLength; i++) {
        if (num & (1 << i)) {
          digitalWrite(ledPin[i], HIGH);
          numBit += "1";
        } else {
          digitalWrite(ledPin[i], LOW);
          numBit += "0";
        }
      }
      Serial.print(", Numero binario: ");Serial.println(invertirCadena(numBit)); // Muestra el número binario
      delay(500); // Espera medio segundo antes de mostrar el siguiente número
    }
    
  }
  else {Serial.println("Opcion invalida!");} // Muestra un mensaje si la opción ingresada es inválida

  delay(1000); // Espera un segundo antes de iniciar un nuevo ciclo
  
}

// Función para calcular 2^n
int Exponente(int num){
  int resultado = 1;
  for(int i = 0 ; i<num ; i++){
    resultado = resultado * 2;
  }
  return resultado;
}

// Función para invertir una cadena de caracteres
String invertirCadena(String s) {
  String temporal = "";
  for (int m = s.length() - 1; m >= 0; m--)
    temporal += s[m]; // Agrega cada carácter en orden inverso
  return temporal; // Devuelve la cadena invertida
}
