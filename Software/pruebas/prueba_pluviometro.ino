#define PLUVIOMETRO_IN 2

float lluvia;
float tiempo1=0, tiempo2;

void setup() {
  Serial.begin(9600);
  Serial.println("INICIANDO");

  pinMode(PLUVIOMETRO_IN, INPUT_PULLUP);  // Interrupcion pluviometro 
  attachInterrupt(digitalPinToInterrupt(PLUVIOMETRO_IN), calcular_lluvia, RISING) ;
  
  delay(100);
}

/////////////////////////////////////////////////////////////////////////////////////////////
void calcular_lluvia() {
  tiempo2 = millis();
  if(tiempo2 > tiempo1 && tiempo2-tiempo1 >=120) {
    Serial.println(tiempo1);
    Serial.println(tiempo2);
    Serial.println("----------lluvia------------");
    //6ml*pulso en 9cm de diametro
    //63.061cm2 =0.0063061m2    158.57 de estos en 1m2
    lluvia = 6*158.57*3600/(tiempo2-tiempo1);
    Serial.print(lluvia);
    Serial.println(" mm/h");
    tiempo1 = tiempo2;
    }
}

//12.6 l/h =210 l/h
//0,116 l/h si ponemos una hora
void loop() {   
  Serial.println("-"); 
  delay(1000);     
}
