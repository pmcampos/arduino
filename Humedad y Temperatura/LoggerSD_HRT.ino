#include <SD.h>
#include "DHT.h"

#define DHTPIN 7    // PIN de conexión con el sensor
#define DHTTYPE DHT11   //Sensor HR/T DHT 11 - Azul, es más básico
//#define DHTTYPE DHT22   //Sensor HR/T DHT 22  (AM2302) - Blanco

DHT dht(DHTPIN, DHTTYPE);

File myFile;

//Declaración de Variables
  
  float h = dht.readHumidity();  // Humedad Relativa
  float t = dht.readTemperature();  // Temperatura °C
//  float pvs;  //Presión de vapor de saturación
//  float pv;   //Presión de vapor
//  float p;    // Presión de vapor al 80%
//  float tma;  // Temperatura minima aceptable °C






void setup()
{

  Serial.begin(9600);
  Serial.println("Prototipo 2 Data Logger HR/T v0.1");
  Serial.println("Preparando tarjeta SD...");
  delay(2000);
  
   pinMode(8, OUTPUT);
   
  if (!SD.begin(8)) {
    Serial.println("fallo en la inicialización de tarjeta SD!");
    return;
  }
    Serial.println("la tarjeta está lista.");delay(50); 
	Serial.print("Comenzando toma de datos...");delay(100); 
	Serial.println("HR | Temp C | TMA C | P.Vapor | PVSaturacion");delay(100); 
	
	myFile = SD.open("datos.txt", FILE_WRITE);
	dht.begin();
}

void loop() {

 if (isnan(t) || isnan(h)) {  //SACAR ESTO DEL LOOP Y AVISAR ANTES
    Serial.println("Ha fallado la lectura del sensor");
  
    delay(3000);
  } else {
    
	
	
	
	if (myFile) {
		
	myFile.println("HR | Temp C | TMA C | P.Vapor | PVSaturacion");
	myFile.print(h);
        myFile.print(", ");
        myFile.println(t);
		
	Serial.print("HR: "); 
        Serial.print(h);
        Serial.print("% ");
        Serial.print(" | ");
        Serial.print("T: "); 
        Serial.print(t);
        Serial.println("C ");
	
		
	// close the file:
    myFile.close();
    Serial.println("Listo, los datos han sido guardados.");
  } else {
  
    
    Serial.println("ha ocurrido un error al grabar los datos");
	
  }
  
  
}

}

