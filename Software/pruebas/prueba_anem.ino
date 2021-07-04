#define HALL_OUT A0
#define ANEM_OUT A1

float velocidad, direccion;
int offset=18;
int a=0;

void setup() {
  Serial.begin(115200);  //Initialize serial
  Serial.println("INICIANDO");
  Serial.println("Setup terminado correctamente.");
  delay(100);
}

void HacerLecturas() {
  velocidad = analogRead(ANEM_OUT);
  direccion = map(analogRead(HALL_OUT), 0, 1024, 360-offset, 0-offset);
  if (direccion < 0){direccion+=360;}
}

void plotCanalSerie() {  // Visualizar datos por canal serie
  Serial.print("Voltaje = ");
  Serial.println(velocidad);
  Serial.print("Dirección del viento = ");
  Serial.print(direccion);
  Serial.println(" ºN");
  Serial.print("--------------------------------");
  Serial.println(a);
  a++;
}

void loop() {
  HacerLecturas();
  plotCanalSerie();
  delay(200); // Wait 300 seconds to update the channel again
}
