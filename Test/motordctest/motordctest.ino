static int mA = 12; // D6 on NodeMCU
static int mB = 14; // D5 on NodeMCU
static int pinPotenza = 13; // D7 on NodeMCU
void setup() {
Serial.begin(115200);
//definisco tipologia pin
pinMode(mA, OUTPUT); //IN1 del modulo L298N
pinMode(mB, OUTPUT); //IN2 del modulo L298N
pinMode(pinPotenza, OUTPUT); //Valore PWM del pin EN1
//Definisco il senso di marcia del motore
/*
mA | mB | Evento
-----|-------|----------------------
LOW | LOW | Fermo
LOW | HIGH | Movimento ANTIORARIO
HIGH | LOW | Movimento ORARIO
HIGH | HIGH | Fermo
*/
analogWrite(pinPotenza, 255);
}
 
void loop() {
  Serial.println("sto girando in senso");
  digitalWrite(mA, LOW);
  digitalWrite(mB, HIGH);
  delay(1000);
  Serial.println("mi fermo");
  digitalWrite(mA, LOW);
  digitalWrite(mB, LOW);
  delay(1000);
  Serial.println("cambio giro!");
  digitalWrite(mA, HIGH);
  digitalWrite(mB, LOW);
  delay(1000);
  Serial.print("mi rifermo");
  digitalWrite(mA, LOW);
  digitalWrite(mB, LOW);
  delay(1000);
  
}
