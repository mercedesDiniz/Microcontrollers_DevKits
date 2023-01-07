#include <SoftwareSerial.h>
#define rxPin PA10
#define txPin PA11
#define led1 PB0
SoftwareSerial mySerial(rxPin, txPin); // RX, TX

void setup() {
   pinMode(led1, OUTPUT);
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  Serial.println("Usart ok");
}

void loop() { 
  if (mySerial.available()) {
    if (mySerial.read() == 'L'){
      digitalWrite(led1, HIGH);
      //Serial.println("Comando p/ habilitar o Led recebido.");
    }
  }
  digitalWrite(led1, LOW);
}
