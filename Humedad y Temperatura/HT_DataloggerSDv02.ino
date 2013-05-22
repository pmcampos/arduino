#include <SD.h>
#include "DHT.h"
#include "RTClib.h"
#include <Wire.h>

#define DHTPIN 7    // PIN de conexión con el sensor de humedad - pin 7
//#define DHTTYPE DHT11   //Sensor HR/T DHT 11 - Azul
#define DHTTYPE DHT22   //Sensor HR/T DHT 22  (AM2302) - Blanco - mayor precisión


DHT dht(DHTPIN, DHTTYPE);  //Inicia librería DHT
RTC_DS1307 RTC;            //Inicia libreria RTC

File myFile; 
 
int contador = 0;
int led = 10;  //led indicador conectado en el pin 10

void setup()
{
  float h = dht.readHumidity();  // Humedad Relativa
  float t = dht.readTemperature();  // Temperatura °C
  Wire.begin();  
  RTC.begin();  // Reloj
  DateTime now = RTC.now();
  pinMode(led, OUTPUT);  
  
  Serial.begin(9600);
  Serial.println("Prototipo Data Logger HR/T v0.2");
  Serial.println("Preparando tarjeta SD...");
  delay(1000);
  
  pinMode(8, OUTPUT);
   
	if (!SD.begin(8)) {
		Serial.println("Error: se requiere el archivo datos.txt , si no existe favor crearlo en el dispositivo de almacenamiento");
		return;
	}
    Serial.println("Almacenamiento... (ok)");delay(500); 

	if (isnan(t) || isnan(h)) {
    Serial.println("Ha fallado la lectura del sensor");
	return;
	}
	Serial.println("Sensor... (ok)");
  
  	digitalWrite(led, HIGH); 
	delay(500);
	digitalWrite(led, LOW);	
	delay(500);
  	digitalWrite(led, HIGH); 
	delay(500);
	digitalWrite(led, LOW);	

    delay(3000);
	
	Serial.println("Inicio de toma de datos...");delay(100); 
	
	myFile = SD.open("datos.txt", FILE_WRITE);
	myFile.print("Registro del ");
        myFile.print(now.day(), DEC);
        myFile.print('/');
        myFile.print(now.month(), DEC);
        myFile.print('/');
        myFile.print(now.year(), DEC);
        myFile.print(", ");
        myFile.print(now.hour(), DEC);
        myFile.print(':');
        myFile.print(now.minute(), DEC);
        myFile.print(':');
        myFile.print(now.second(), DEC);
        myFile.print(" horas.");
        myFile.println();
	myFile.println("Hora | % Humedad Relativa| Temperatura | Presion de Vapor | Presion de Saturacion | Tma");
	dht.begin();
}

void loop() {
//Declaración de Variables
  
  float h = dht.readHumidity();  // Humedad Relativa
  float t = dht.readTemperature();  // Temperatura °C
  float pvs;  //Presión de vapor de saturación
  float pv;   //Presión de vapor
  float p;    // Presión de vapor al 80%
  float tma;  // Temperatura minima aceptable °C
  
DateTime now = RTC.now();
  if (myFile) {     //Información a grabar en archivo datos.txt

myFile.print(now.hour(), DEC);
myFile.print(':');
myFile.print(now.minute(), DEC);
myFile.print(':');
myFile.print(now.second(), DEC);
myFile.print(", ");
myFile.print(h);
myFile.print(", ");
myFile.println(t);

//Información a mostrar en monitor serial
   
Serial.print(now.year(), DEC);
Serial.print('/');
Serial.print(now.month(), DEC);
Serial.print('/');
Serial.print(now.day(), DEC);
Serial.print(' ');
Serial.print(" , ");
Serial.print(now.hour(), DEC);
Serial.print(':');
Serial.print(now.minute(), DEC);
Serial.print(':');
Serial.print(now.second(), DEC);
      
Serial.print("HR: "); 
Serial.print(h);
Serial.print("% ");
Serial.print(" , ");
Serial.print("T: "); 
Serial.print(t);
Serial.println("C ");

    Serial.print("Contador: ");
    Serial.println(contador);
	contador=contador++;
	digitalWrite(led, HIGH); 
	delay(1000);         // las mediciones son cada 1 segundo  
	digitalWrite(led, LOW);	
	if (contador == 10)  //se estan tomando 10 mediciones

    {  
  
    myFile.close(); 
    Serial.println("Listo, los datos han sido guardados.");
	return;} 
	
  } 
	
  }
 
