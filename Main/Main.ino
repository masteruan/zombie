/* ********************
* 8 Marzo 2018
* per Zombieville
* v 0.1.1
* Giovanni Gentile
* 0lab.it projectg.it
* 
* OUTPUT
* Porte
* P1 ingresso
* P2 chiesa
* P3 uscita
*
* Games
* C1 Candele Q
* C2 Offertorio W
* C3 Acqua E
* C4 Lapide R
* C5 Vaso T
* C6 Faretto statua Y
* C7 Testa U
*
* Instructions
* Send to serial
* "_startGame" to start the game
*
* "_openAll" open all the doors and magnets
* "_reset" open all the doors and switch on the lights
* "_preparation" to close all the doors all the magnets and switch on all the lights
* ***********************/

// switch
boolean start_game = false;
boolean game_started = false;
boolean preparation = false;

// serial
boolean stringComplete = false;
String input = ""; //String
char inChar ;

int pauseTens = 20;

// calamite
int C1 = 30; // Candele Q
int C2 = 31; // Offertorio W
int C3 = 32; // Acqua E
int C4 = 33; // Lapide R
int C5 = 34; // Cappellina T
int C6 = 26; // Relay statua Y
int C7 = 22; // Testa U

// Porte
int P1 = 28; // Porta ingresso 1 !
int P2 = 27; // Porta chiesa 2 @
int P3 = 29; // Porta Uscita 3 =

// Arrays
int doors[] = {P1,P2,P3}; // 3 doors
int magnets[] = {C1,C2,C3,C4,C5,C6,C7}; // giochi e armadi

void setup() {
  Serial.flush();
  // Declare output
  // da 22 a 37 16 relay
  for (int i = 22; i < 38; i++){
    pinMode(i, OUTPUT);
    delay(20);
    digitalWrite(i, HIGH);
  }
  // Start up serial connection
  Serial.begin(9600); //default 115200
  input.reserve(200);

  Serial.println("####################################");
  Serial.println("You are Welcome into Breakout System");
  Serial.println("Zombieville v 1.0.1");
}

void loop() {

  if (stringComplete) {
    seriale();
    delay(20);
    input = "";
    stringComplete = false;
  }
  game();
}

void game () {
   if (start_game){
      // reset booleane
      
      // Close all doors
      digitalWrite(P1, LOW);
      delay(pauseTens);
      digitalWrite(P2, LOW);
      delay(pauseTens);
      digitalWrite(P3, LOW);
      delay(pauseTens);
      // Close all armadi
      digitalWrite(C1, LOW);
      digitalWrite(C2, LOW);
      
      digitalWrite(C4, LOW);
      digitalWrite(C5, LOW);
      digitalWrite(C7, LOW);
      
      // variables
      start_game = false;
      game_started = true;
      Serial.println("gameStarted");
  }

  else if (game_started){
    
    }
  }

void serialEvent() {
  Serial.flush();
  delay(20);
  // Read any serial input
  while (Serial.available())
  {
    inChar = (char)Serial.read(); // Read in one char at a time
    input += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
