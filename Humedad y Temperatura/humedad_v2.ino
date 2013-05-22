#include "DHT.h"

#define DHTPIN 7    // PIN de conexión con el sensor

#define DHTTYPE DHT11   // DHT 11 - Azul, es más básico
//#define DHTTYPE DHT22   // DHT 22  (AM2302) - Blanco

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  
  
    
  Serial.begin(9600);               //inicio Monitor Serial a 9600bps 
  Serial.println("Prototipo2 v0.1");
  Serial.println("Comanzando toma de datos");
  delay(2000);
  Serial.println("HR | Temp C | TMA C | P.Vapor | PVSaturacion");
  delay(100); 
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

  //Validación de datos e impresión en pantallas
  if (isnan(t) || isnan(h)) {
    Serial.println("Ha fallado la lectura del sensor");
  
    delay(3000);
  } else {
    
   
/*
//:::CALCULOS

pvs = 610.5*exp((17.269*t)/(237.3+t));
pv = h/100*pvs;
p = pv/0.8;

if (p>=610.5) { 

  tma = (237.3*log(p/610.5))/(17.269-log(p/610.5));

}else{

  tma=2;
}

*/

//:::TEXTOS ::::

   Serial.print("HR: "); 
    Serial.print(h);
    Serial.print("% ");
    Serial.print(" | ");
    Serial.print("T: "); 
    Serial.print(t);
    Serial.println("C ");
/*    Serial.print(" | ");
    Serial.print("Tma: ");
    Serial.print(tma);
    Serial.print("C ");
    Serial.print(" | ");
    Serial.print("Pv: ");
    Serial.print(pv);
    Serial.print("Pa ");
    Serial.print(" | ");
    Serial.print("Psat: ");
    Serial.print(pvs);
    Serial.println("Pa");*/

  }
}
