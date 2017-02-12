
//motori DC
const int DC1ap = 12;
const int DC1an = 13;
const int VelDC1 = 11; 
const int DC2ap = 8;
const int DC2an = 9;
const int VelDC2 = 10;
//motore step-to-step
const int a1 = 4;//rosso IN1
const int a2 = 5;//nero IN2
const int b1 = 6;//blue IN3
const int b2 = 7;//verde IN4
int VelStS = 10;
//telecomando
const int tele = 3;

void dcOra(int mA, int mB){
  digitalWrite(mA, LOW);
  digitalWrite(mB, HIGH);
}

void dcAnti(int mA, int mB){
  digitalWrite(mA, HIGH);
  digitalWrite(mB, LOW);
}

void dcStop(int mA, int mB){
  digitalWrite(mA, LOW);
  digitalWrite(mB, LOW);
}

void step (boolean vala1, boolean valb1, boolean vala2, boolean valb2){
digitalWrite(a1, vala1);
digitalWrite(b1, valb1);
digitalWrite(a2, vala2);
digitalWrite(b2, valb2);
}

void StSOra(int times) {
for (int i=0; i <= times; i++){
step(HIGH, LOW, LOW, LOW);
delay(VelStS);
step(LOW, LOW, HIGH, LOW);
delay(VelStS);
step(LOW, HIGH, LOW, LOW);
delay(VelStS);
step(LOW, LOW, LOW, HIGH);
delay(VelStS);}
}

void StSanti(int times) {
for (int i=0; i <= times; i++){
step(LOW, LOW, HIGH, LOW);
delay(VelStS);
step(HIGH, LOW, LOW, LOW);
delay(VelStS);
step(LOW, LOW, LOW, HIGH);
delay(VelStS);
step(LOW, HIGH, LOW, LOW);
delay(VelStS);}
}

void scatta(int tempo){
  Serial.println("scatto");
  digitalWrite(tele, 1);
  delay(tempo);
  digitalWrite(tele, 0);
  delay(tempo);
}

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(DC1ap, OUTPUT); //IN1 del modulo L298N
  pinMode(DC1an, OUTPUT); //IN2 del modulo L298N
  pinMode(VelDC1, OUTPUT); //Valore PWM del pin EN1
  pinMode(DC2ap, OUTPUT); //IN3 del modulo L298N
  pinMode(DC2an, OUTPUT); //IN4 del modulo L298N
  pinMode(VelDC2, OUTPUT); //Valore PWM del pin EN1
  analogWrite(VelDC1, 40);
  analogWrite(VelDC2, 40);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  step(LOW, LOW, LOW, LOW);
}

void loop() {
  int valScatto = analogRead(A2);
  valScatto = map(valScatto, 0, 1023, 0, 3);
  Serial.println(valScatto);
  if(valScatto == 0){
    scatta(1000);
    delay(10000);
    }
  if(valScatto == 2){
    scatta(3000);
    }
  int valMotDC = analogRead(A0);
  valMotDC = map(valMotDC, 0, 1023, 0, 3);
  if(valMotDC == 1){
    dcStop(DC2ap, DC2an);
    }
  if(valMotDC == 0){
    dcAnti(DC2ap, DC2an);
    }
  if(valMotDC == 2){
    dcOra(DC2ap, DC2an);
    }
  int valMotStS = analogRead(A1);
  valMotStS = map(valMotStS, 0, 1023, 0, 3);
  if(valMotStS == 1){
    step(LOW, LOW, LOW, LOW);
    }
  if(valMotStS == 0){
    StSanti(1);
    }
  if(valMotStS == 2){
    StSOra(1);
    }
}
