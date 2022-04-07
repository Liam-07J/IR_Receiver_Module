#include "IRremote.h"

// setup variables
int allOn = false;
int button;
char buttonChar;
int receiver = 13;

IRrecv irrecv(receiver);
decode_results results;

void translateIR() // takes action based on IR code received
{
  // Detects Input
  switch (results.value)
  {
    case 0xFFA25D: buttonChar = 'p'; break;
    case 0xFFE21D: // FUNC/STOP break;
    case 0xFF629D: // VOL + break;
    case 0xFF22DD: // FAST BACK    break;
    case 0xFF02FD: // PAUSE   break;
    case 0xFFC23D: // Fast Forward  break;
    case 0xFFE01F: // DOWN   break;
    case 0xFFA857:// VOL -    break;
    case 0xFF906F: // UP  break;
    case 0xFF9867: // EQ    break;
    case 0xFFB04F: // ST/REPT    break;
    case 0xFF6897: button = 0;  break;
    case 0xFF30CF: button = 1;     break;
    case 0xFF18E7: button = 2;     break;
    case 0xFF7A85: button = 3;     break;
    case 0xFF10EF: button = 4;     break;
    case 0xFF38C7: button = 5;    break;
    case 0xFF5AA5: button = 6;     break;
    case 0xFF42BD: button = 7;     break;
    case 0xFF4AB5: button = 8;     break;
    case 0xFF52AD: button = 9;     break;
    case 0xFFFFFFFF: Serial.println(" REPEAT"); break;

    default:
      Serial.println(" other button : ");
      Serial.println(results.value);

  }// End Case

  delay(500); // Do not get immediate repeat


}
void setup()
{

  Serial.begin(9600);   // Begians Serial
  irrecv.enableIRIn(); // Start the receiver

  // Setups pins
  for (int i = 0; i <= 12; i++) {
    pinMode(i, OUTPUT);
  }
}


void loop()
{
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    translateIR();
    irrecv.resume(); // receive the next value
  }

  // OUTPUT
  //Detects if POWER button is pressed
  if (buttonChar == 'p') {
    if (allOn == true) {
      for (int i = 0; i <= 12; i++) {
        digitalWrite(i, HIGH);
        allOn = false;
      }
    }
    else if (allOn == false) {
      for (int i = 0; i <= 12; i++) {
        digitalWrite(i, LOW);
        allOn = true;
      }

    }
    buttonChar = 'n';
  }
  if (button == 0) {
    digitalWrite(10, HIGH);
    delay(1000);
    digitalWrite(10, LOW);
  }
  else if (button == 1) {
    digitalWrite(11, HIGH);
    delay(1000);
    digitalWrite(11, LOW);
  }
  else {
    digitalWrite(button, HIGH);
    delay(1000);
    digitalWrite(button, LOW);
  }
  button = -1;
}
