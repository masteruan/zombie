/*
 * Laser offertorio
 * per Zombieville
 * 28 Marzo 2018
 * ############### Quando spegni il laser parte
 */

boolean switches = false;
int relay = 7;
void setup() {
  Serial.begin(9600);
  pinMode(6, INPUT);
  pinMode(relay, OUTPUT);
  
  digitalWrite(relay, HIGH); // change in HIGH for laser OFF
}

void loop() {
  switches = digitalRead(6);
  if(switches){
    while(1){
     digitalWrite(relay, LOW); // change in LOW for laser ON
     Serial.println("OK");
     delay(300); 
    }
  }
}

