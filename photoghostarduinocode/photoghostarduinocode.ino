//By Marcos Hernández, for Intro to IM. 2024.

int value;  //This will help in receiving the data from P5.js and processing it.

int SpiezoPinUL;
int SpiezoPinUR;
int SpiezoPinDL;
int SpiezoPinDR;

//Movement strings
int move_up;
int move_left;
int move_down;
int move_right;

int brightness = 0;               //The only float value to send.
int currentflashlightstatus = 0;  //0 = OFF, 1 = ON.
int flashlightcountdown = 0;      //Is a range that if it reaches 0, it breaks the loop.
int buttonFlashlight = 0;         //Variable to read the button inputs.

const int buttonAPin = 3;   //Right
const int buttonBPin = 5;   //Up
const int buttonCPin = 6;   //Left
const int buttonDPin = 9;   //Down
const int buttonEPin = 10;  //Flashlight

const int piezoPinUL = 4;
const int piezoPinUR = 2;
const int piezoPinDL = 7;
const int piezoPinDR = 8;

const int bin1Pin = 12;  //For the flashlight in the game.

void setup() {
  Serial.begin(9600);  //Data is read quickly.
  pinMode(buttonAPin, INPUT);
  pinMode(buttonBPin, INPUT);
  pinMode(buttonCPin, INPUT);
  pinMode(buttonDPin, INPUT);
  pinMode(buttonEPin, INPUT);
  pinMode(bin1Pin, OUTPUT);

  //Start the handshake
  while (Serial.available() <= 0) {
    digitalWrite(LED_BUILTIN, HIGH);              // on/blink while waiting for serial data
    Serial.println("Waiting for communication");  // send a starting message
    delay(300);                                   // wait 1/3 second
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    Serial.println(brightness);
  }
}

void loop() {
  while (Serial.available()) {
    digitalWrite(LED_BUILTIN, HIGH);  //Led on while receiving data

    //Controller inputs
    move_up = digitalRead(buttonBPin);
    move_left = digitalRead(buttonCPin);
    move_down = digitalRead(buttonDPin);
    move_right = digitalRead(buttonAPin);


    //Flashlight
    buttonFlashlight = digitalRead(buttonEPin);
    //Serial.println("Handshake!"); //Is this necessary?
    
    value = Serial.parseInt();  //We read the value here.

    SpiezoPinUL = Serial.parseInt();  //We read the values of the piezos here.
    SpiezoPinUR = Serial.parseInt();
    SpiezoPinDL = Serial.parseInt();
    SpiezoPinDR = Serial.parseInt();

    currentflashlightstatus = Serial.parseInt();

    flashlightcountdown = Serial.parseInt();

    //HANDSHAKE!
    if (Serial.read() == '\n') {

      //------ Buzzers -------//

      /* SpiezoPinUL = Serial.parseInt();  //We read the values of the piezos here.
      SpiezoPinUR = Serial.parseInt();
      SpiezoPinDL = Serial.parseInt();
      SpiezoPinDR = Serial.parseInt(); */

      if (SpiezoPinUL == 2) {
        tone(piezoPinUL, 500);
      } else if (SpiezoPinUL == 1) {
        tone(piezoPinUL, 1000);
      } else if (SpiezoPinUL == 0) {
        noTone(piezoPinUL);
      }

      if (SpiezoPinUR == 2) {
        tone(piezoPinUR, 500);
      } else if (SpiezoPinUR == 1) {
        tone(piezoPinUR, 1000);
      } else if (SpiezoPinUR == 0) {
        noTone(piezoPinUR);
      }

      if (SpiezoPinDL == 2) {
        tone(piezoPinDL, 500);
      } else if (SpiezoPinDL == 1) {
        tone(piezoPinDL, 1000);
      } else if (SpiezoPinDL == 0) {
        noTone(piezoPinDL);
      }

      if (SpiezoPinDR == 2) {
        tone(piezoPinDR, 500);
      } else if (SpiezoPinDR == 1) {
        tone(piezoPinDR, 1000);
      } else if (SpiezoPinDR == 0) {
        noTone(piezoPinDR);
      }

      if (flashlightcountdown == 1) {
        brightness = analogRead(A0);

        //We map the values.
        brightness = map(brightness, 800, 1200, 1, 12);  //4 is the minimum in the game.

        ;
        //Turn it ON.
        digitalWrite(bin1Pin, HIGH);

        //And send it.

      } else {
        //Just in case, we assign it the value of 0 to avoid continously charging the battery.
        brightness = 0;
        digitalWrite(bin1Pin, LOW);
      }
    }

    //I send you data and you send me more data!
    Serial.print(brightness);
    Serial.print(",");

    //Flashlight
    Serial.print(buttonFlashlight);
    Serial.print(",");

    //Movement
    Serial.print(move_up);
    Serial.print(",");
    Serial.print(move_left);
    Serial.print(",");
    Serial.print(move_down);
    Serial.print(",");
    Serial.println(move_right);
  }
  digitalWrite(LED_BUILTIN, LOW);
}