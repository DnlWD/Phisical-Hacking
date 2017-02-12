// set pin numbers:
const int a1 = 11;//rosso
const int a2 = 10;//nero
const int b1 = 9;//blue
const int b2 = 8;//verde
int tempo = 10;

void setup() {
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);  
  digitalWrite(a1, LOW);
  digitalWrite(a2, LOW); 
  digitalWrite(b1, LOW); 
  digitalWrite(b2, LOW); 
}

void loop(){
orario(90);
step(LOW, LOW, LOW, LOW);
delay(10000);
antiorario(90);
step(LOW, LOW, LOW, LOW);
delay(10000);
}

void step (boolean vala1, boolean valb1, boolean vala2, boolean valb2){
  digitalWrite(a1, vala1);
  digitalWrite(b1, valb1); 
  digitalWrite(a2, vala2); 
  digitalWrite(b2, valb2); 
}

void orario(int times) {
  for (int i=0; i <= times; i++){
step(HIGH, LOW, LOW, LOW);
    delay(tempo); 
  step(LOW, LOW, HIGH, LOW);
    delay(tempo);  
 step(LOW, HIGH, LOW, LOW);
    delay(tempo); 
  step(LOW, LOW, LOW, HIGH);
    delay(tempo);}
  }

void antiorario(int times) {
  for (int i=0; i <= times; i++){
  step(LOW, LOW, HIGH, LOW);
    delay(tempo); 
  step(HIGH, LOW, LOW, LOW);
    delay(tempo);  
 step(LOW, LOW, LOW, HIGH);
    delay(tempo); 
  step(LOW, HIGH, LOW, LOW);
    delay(tempo);}
    }


