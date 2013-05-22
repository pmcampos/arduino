#include <SD.h>
#include "DHT.h"
#include "RTClib.h"
#include <Wire.h>

#define DHTPIN 7    // PIN de conexión con el sensor de humedad
//#define DHTTYPE DHT11   //Sensor HR/T DHT 11 - Azul, es más básico
#define DHTTYPE DHT22   //Sensor HR/T DHT 22  (AM2302) - Blanco


DHT dht(DHTPIN, DHTTYPE);  //Inicia librería DHT
RTC_DS1307 RTC;            //Inicia libreria RTC

File myFile; //Crea archivo
 
int contador = 0;

void setup()
{
  float h = dht.readHumidity();  // Humedad Relativa
  float t = dht.readTemperature();  // Temperatura °C
  Wire.begin();  
  RTC.begin();  // Reloj
  DateTime now = RTC.now();
  
  Serial.begin(9600);
  Serial.println("Prototipo 2 Data Logger HR/T v0.1");
  Serial.println("Preparando tarjeta SD...");
  delay(2000);
  
   pinMode(8, OUTPUT);
   
	if (!SD.begin(8)) {
		Serial.println("fallo en la inicialización de tarjeta SD!");
		return;
	}
    Serial.println("Tarjeta SD... ok!");delay(500); 

	if (isnan(t) || isnan(h)) {
    Serial.println("Ha fallado la lectura del sensor");
	return;
	}
	Serial.println("Sensor... ok!.");
  
    delay(3000);
	
	Serial.print("Comenzando una nueva toma de datos...");delay(100); 
	Serial.println("Humedad Relativa, Temperatura");delay(100); 
	
	myFile = SD.open("datos.txt", FILE_WRITE);
	myFile.print("Nuevo Registro: ");
        myFile.print(now.year(), DEC);
        myFile.print('/');
        myFile.print(now.month(), DEC);
        myFile.print('/');
        myFile.print(now.day(), DEC);
        myFile.print(' ');
        myFile.print(" , ");
        myFile.print(now.hour(), DEC);
        myFile.print(':');
        myFile.print(now.minute(), DEC);
        myFile.print(':');
        myFile.print(now.second(), DEC);
        myFile.println();
	myFile.println("Humedad Relativa, Temperatura");
	dht.begin();
}

void loop() {
 //Declaración de Variables
  
  float h = dht.readHumidity();  // Humedad Relativa
  float t = dht.readTemperature();  // Temperatura °C
//  float pvs;  //Presión de vapor de saturación
//  float pv;   //Presión de vapor
//  float p;    // Presión de vapor al 80%
//  float tma;  // Temperatura minima aceptable °C
  
DateTime now = RTC.now();


	if (myFile) {
		
//Información a grabar en archivo datos.txt

myFile.print(now.year(), DEC);
myFile.print('/');
myFile.print(now.month(), DEC);
myFile.print('/');
myFile.print(now.day(), DEC);
myFile.print(' ');
myFile.print(" , ");
myFile.print(now.hour(), DEC);
myFile.print(':');
myFile.print(now.minute(), DEC);
myFile.print(':');
myFile.print(now.second(), DEC);
    
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
	
	delay(1000);         // las mediciones son cada 1 segundo  
		
	if (contador == 10)  //se estan tomando 10 mediciones

    {  
  
    myFile.close(); 
    Serial.println("Listo, los datos han sido guardados.");
	return;} 
	
  } 
	
  }
 
