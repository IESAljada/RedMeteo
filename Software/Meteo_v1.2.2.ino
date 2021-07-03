/*
 * Dirección automática dada desde DHCP y sino está disponible espera hasta que lo este
 * 
 */
#include <Ethernet.h>
#include <DHT.h>

#include "secrets.h"
//#include "ThingSpeak.h"

#define DHT_PIN 5
#define DHT_TYPE DHT11
#define HALL_OUT A0
#define ANEM_OUT A1
#define PLUVIOMETRO_IN 2

#define THING_SPEAK_ADDRESS "api.thingspeak.com"
#define TIMEOUT 5000

byte mac[] = SECRET_MAC;

DHT dht(DHT_PIN, DHT_TYPE);

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(10,32, 42, 223);
IPAddress myDns(10, 32, 42, 1);
//IPAddress ip(192, 168, 0, 177);
//IPAddress myDns(192, 168, 0, 1);

EthernetClient client;

unsigned long myChannelNumber = SECRET_CH_ID;
//const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

float temp_DHT11, humedad_DHT11, velocidad, direccion, lluvia;
float tiempo1=0, tiempo2;
int offset=0;

void setup() {
  Ethernet.init(10);  // Most Arduino Ethernet hardware
  Serial.begin(115200);  //Initialize serial
  Serial.println("Estación Metereológica versión 1.2.2");
  Serial.println("INICIANDO");
    
  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  /*if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
       delay(1); // do nothing, no point running without Ethernet hardware
     }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }*/

  /************************************************
  // Esperar hasta recibir la dirección IP por DHCP
  /*************************************************/

  while(Ethernet.begin(mac)==0)
  {
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
       delay(1); // do nothing, no point running without Ethernet hardware
     }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    delay(1500);
  }
  Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  
  // give the Ethernet shield a second to initialize:
  delay(1000);
  
  // ThingSpeak.begin(client);  // Initialize ThingSpeak

  pinMode(PLUVIOMETRO_IN, INPUT_PULLUP);  // Interrupcion pluviometro
  pinMode(DHT_PIN, INPUT);
  attachInterrupt(0, calcular_lluvia, RISING);
  Serial.println("Setup terminado correctamente.");
  dht.begin();
  
  delay(100);
  
 
}

void calcular_lluvia() {
  tiempo2 = millis();
  if (tiempo2 > tiempo1) {lluvia = 7*3600/(tiempo2-tiempo1);}
  tiempo1 = tiempo2;
}

void HacerLecturas() {

  temp_DHT11 = dht.readTemperature();
  humedad_DHT11 = dht.readHumidity();
  //*****************************************
  velocidad = 0.0964*analogRead(ANEM_OUT)+2.0187;
  direccion = map(analogRead(HALL_OUT), 0, 1024, 360-offset, 0-offset);
  if (direccion < 0) {direccion+=360;}
  if((millis()-tiempo1)>=36000000) {lluvia=0;}
  //*******************************************
  //12.6 l/h = 210 l/h
  //0,116 l/h si ponemos una hora

  /*temp_DHT11=random(15.00, 35.00);
  humedad_DHT11=random(25.00, 95.00);
  velocidad=random(1.00, 30.00);
  direccion=random(0, 360);
  lluvia=random(0, 10);

  // set the fields with the values
  ThingSpeak.setField(1,temp_DHT11);
  ThingSpeak.setField(2,humedad_DHT11);
  ThingSpeak.setField(3,velocidad);
  ThingSpeak.setField(4,direccion);
  ThingSpeak.setField(5,lluvia);
  */
}

void plotCanalSerie() {  // Visualizar datos por canal serie
  //Serial.begin(9600);
  delay(50);
  Serial.print("Temperature DHT11 = ");
  Serial.print(temp_DHT11);
  Serial.println("ºC");
  Serial.print("Humidity DHT11 = ");
  Serial.print(humedad_DHT11);
  Serial.println(" %");
  Serial.print("Velocidad del viento = ");
  Serial.print(velocidad);
  Serial.println(" m/s");
  Serial.print("Dirección del viento = ");
  Serial.print(direccion);
  Serial.println(" ºN");
  Serial.print("Lluvia = ");
  Serial.print(lluvia);
  Serial.println(" mm3/m");
  Serial.println("--------------------------------");
}

// Wait for a response from the server indicating availability,
// and then collect the response and build it into a string.

String getResponse(){
  String response;
  long startTime = millis();

  delay( 200 );
  while ( client.available() < 1 && (( millis() - startTime ) < TIMEOUT ) ){
        delay( 5 );
  }
  
  if( client.available() > 0 ){ // Get response from server.
     char charIn;
     do {
         charIn = client.read(); // Read a char from the buffer.
         response += charIn;     // Append the char to the string response.
        } while ( client.available() > 0 );
    }
  client.stop();
  client.flush();
        
  return response;
}


void enviar_lecturas() {
  // write to the ThingSpeak channel 
  /*
    
   int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  */
  if (client.connect( THING_SPEAK_ADDRESS , 80 )){
  
    // Build the postData string.  
    // If you have multiple fields, make sure the sting does not exceed 1440 characters.
    String postData= "api_key=" + String(SECRET_WRITE_APIKEY) ;
    postData+= "&field1="+String(temp_DHT11);
    postData+= "&field2="+String(humedad_DHT11);
    postData+= "&field3="+String(velocidad);
    postData+= "&field4="+String(direccion);
    postData+= "&field5="+String(lluvia);       

    // POST data via HTTP.
    Serial.println( "Connecting to ThingSpeak for update..." );
    Serial.println();
        
    client.println( "POST /update HTTP/1.1" );
    client.println( "Host: api.thingspeak.com" );
    client.println( "Connection: close" );
    client.println( "Content-Type: application/x-www-form-urlencoded" );
    client.println( "Content-Length: " + String( postData.length() ) );
    client.println();
    client.println( postData );
        
       
    String answer=getResponse();
    Serial.println( answer );
    


    //==================================
    Serial.println("Conectado");
  } else {
    Serial.println("Fallo en la conexion");
  }
  if (!client.connected()) {
    Serial.println("Disconnected!");
  }

  
  
}

void loop() {
  HacerLecturas();
  enviar_lecturas();
  plotCanalSerie();
  delay(300000); // Wait 5 min to update the channel again
  //delay(1000);
}
