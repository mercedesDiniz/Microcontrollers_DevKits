/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit:
 *  STM32: SPI 1 | SPI 2  | Mudulo SD (Vcc = 5V)
 *          PA4  |  PB12  |    cs
 *          PA5  |  PB13  |    sck
 *          PA6  |  PB14  |    MISO
 *          PA7  |  PB15  |    MOSI


*/

#include <SPI.h>
#include <SD.h>

#define DIRECTORY "teste123.txt"
File myFile;

void setup() {
  //SPI.setModule(2); // spi2 do stm32
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(PA4)) // pin do CS (SPI02 -> cs = PB12)
  {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open(DIRECTORY, FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("novo teste 123");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open(DIRECTORY);
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop() {
  // nothing happens after setup
}
