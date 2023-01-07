#include <SoftwareSerial.h>
#define rxPin 27
#define txPin 25
#define button 33
SoftwareSerial mySerial(rxPin, txPin); // RX, TX

void setup() {
   pinMode(button, INPUT_PULLUP); // button no modo pull-up
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Usart ok");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
}

void loop() { 
  if (digitalRead(button) == 0){
    mySerial.write("L");
    Serial.println("Comando p/ habilitar o Led enviado.");
  }
}
