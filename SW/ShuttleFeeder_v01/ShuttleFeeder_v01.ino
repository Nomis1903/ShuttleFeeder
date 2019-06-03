/*
 * Badminton Shuttle Feeder v01
 * 
 * Features:
 *  - 
 *  -
 *  -
 *  -
 *  
 * 
 */

// ----------------------------- Pins -----------------------------
// Motor-Speeder
const int pinMotorLeftSpeederFwd = 5;
const int pinMotorLeftSpeederBwd = 18;
const int pinMotorRightSpeederFwd = 17;
const int pinMotorRightSpeederBwd = 16;

// Motor-Magazin
const int pinMotorMagazinEnable = 23;
const int pinMotorMagazinIn3 = 22;
const int pinMotorMagazinIn4 = 1;

// Motor-Feeder
const int pinMotorFeederEnable = 3;
const int pinMotorFeederIn1 = 21;
const int pinMotorFeederIn2 = 19;

// Motor-Kette
const int pinMotorKetteEnable = 14;
const int pinMotorKetteIn1 = 12;
const int pinMotorKetteIn2 = 13;

// Stepper-Vertical
const int pinStepperVerticalDirection = 34;
const int pinStepperVerticalStep = 35;
const int pinStepperVerticalEnable = 32;

// Stepper-Horizontal
const int pinStepperHorizontalDirection = 33;
const int pinStepperHorizontalStep = 25;
const int pinStepperHorizontalEnable = 26;

// ----------------------------- PWM -----------------------------
const int motorChannel = 0;
const int motorFreq = 5000;
const int resolution = 8;

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

void setup() {
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  
  // put your setup code here, to run once:
  ledcSetup(motorChannel, motorFreq, resolution);
  ledcAttachPin(pinMotorLeftSpeederFwd, motorChannel);

}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  
  for(int i = 0; i < 20; i++) {
    ledcWrite(motorChannel, 10*i);
    Serial.println(10*i);
    delay(2000);
  }
  // put your main code here, to run repeatedly: 

}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
