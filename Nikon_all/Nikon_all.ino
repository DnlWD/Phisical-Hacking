#include <ESP8266WiFi.h>
const char* ssid = "Vodafone-WZ";
const char* password = "ADADADAD";
WiFiServer server(80);
//motori DC
const int DC1ap = 16; // D0
const int DC1an = 5; // D1
const int VelDC1 = A0;//A0 
const int DC2ap = 10; // SD3
const int DC2an = 9; // SD2
const int VelDC2 = 4;// D2
//motore step-to-step
const int a1 = 11;//rosso IN1 D5
const int a2 = 10;//nero IN2 D6
const int b1 = 9;//blue IN3 D7
const int b2 = 8;//verde IN4 D8
int VelStS = 10;
//telecomando
const int tele = 2; // D4

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
  digitalWrite(tele, HIGH);
  delay(1000);
  digitalWrite(tele, LOW);
  delay(tempo);
}

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); // Connect to WiFi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  // Start the server
  server.begin();
  Serial.println("Server started");
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/"); // Print the IP address*/
  pinMode(DC1ap, OUTPUT); //IN1 del modulo L298N
  pinMode(DC1an, OUTPUT); //IN2 del modulo L298N
  pinMode(VelDC1, OUTPUT); //Valore PWM del pin EN1
  pinMode(DC2ap, OUTPUT); //IN3 del modulo L298N
  pinMode(DC2an, OUTPUT); //IN4 del modulo L298N
  pinMode(VelDC2, OUTPUT); //Valore PWM del pin EN1
  analogWrite(VelDC1, 255);
  analogWrite(VelDC2, 255);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  step(LOW, LOW, LOW, LOW);
  pinMode(tele, OUTPUT);
}

void loop() {
  Serial.println("scatto");
  scatta(3000);
 // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
  delay(1);
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  // Match the request
  if (request.indexOf("/LED=ON") != -1) {
  scatta(1000);
  }
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); // do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a>");
  client.println("</html>");
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
