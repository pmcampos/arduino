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
  Serial.println("Prototipo Data Logger HR/T v0.3");
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
        Serial.println("Hora | % Humedad Relativa| Temperatura | Presion de Vapor | Presion de Saturacion | Tma");
        	
	myFile = SD.open("datos.txt", FILE_WRITE);
	myFile.println(" ");
        myFile.print("Nuevo Registro: ");
        myFile.print(now.day(), DEC);
        myFile.print('/');
        myFile.print(now.month(), DEC);
        myFile.print('/');
        myFile.print(now.year(), DEC);
        myFile.print(" - ");
        myFile.print(now.hour(), DEC);
        myFile.print(':');
        myFile.print(now.minute(), DEC);
        myFile.print(':');
        myFile.println(now.second(), DEC);

	myFile.println("id, Hora, Humedad Relativa, Temperatura, P.Vapor, P.Saturacion, Tma");
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
  
  int tiempo = 1;
  int cantidad = 10;
  
  

DateTime now = RTC.now();

//CALCULOS

pvs = 610.5*exp((17.269*t)/(237.3+t));
pv = h/100*pvs;
p = pv/0.8;

if (p>=610.5) { 

  tma = (237.3*log(p/610.5))/(17.269-log(p/610.5));

}else{

  tma=2;
}

 
if (myFile) {     //Información a grabar en archivo datos.txt

myFile.print(contador);
myFile.print(", ");
myFile.print(now.hour(), DEC);
myFile.print(':');
myFile.print(now.minute(), DEC);
myFile.print(':');
myFile.print(now.second(), DEC);
myFile.print(", ");
myFile.print(h);
myFile.print(", ");
myFile.print(t);
myFile.print(", ");
myFile.print(pv);
myFile.print(", ");
myFile.print(pvs);
myFile.print(", ");
myFile.println(tma);

//Información a mostrar en monitor serial
   
Serial.print("ID ");   
Serial.print(contador);
Serial.print(": ");
Serial.print(now.hour(), DEC);
Serial.print(':');
Serial.print(now.minute(), DEC);
Serial.print(':');
Serial.print(now.second(), DEC);
Serial.print(" - ");      
Serial.print("HR: "); 
Serial.print(h);
Serial.print("%, ");
Serial.print("T: "); 
Serial.print(t);
Serial.print("C, P.Vapor: ");
Serial.print(pv);
Serial.print(", P.Saturacion: ");
Serial.print(pvs);
Serial.print(", Tma: ");
Serial.print(tma);
Serial.println("C");

	contador=contador++;
	digitalWrite(led, HIGH); 
	delay(tiempo*1000);         // las mediciones son cada 1 segundo  
	digitalWrite(led, LOW);	
	if (contador == cantidad)  //se estan tomando 10 mediciones
    {  
  
    
    myFile.close(); 
    Serial.println("...(ok)");
    Serial.println(" ");
    Serial.println("Listo, los datos han sido guardados.");
	return;} 
	
  } 
	
  }
 
