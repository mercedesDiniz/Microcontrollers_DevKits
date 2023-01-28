/* Test basic SD Card - STM32
Library: https://www.arduinolibraries.info/libraries/sd-fat

Pin:
 *  STM32: SPI 1 | SPI 2  | Mudulo SD (Vcc = 5V)
 *          PA4  |  PB12  |    cs
 *          PA5  |  PB13  |    sck
 *          PA6  |  PB14  |    MISO
 *          PA7  |  PB15  |    MOSI

*/
 
#include <SPI.h>
//#include <SD.h>
#include "SdFat.h"

// pin SPI 1
#define MOSI PA7
#define MISO PA6
#define SCLK PA5
#define SD_CS_PIN PA4 
                           
static SPIClass mySPI1(MOSI, MISO, SCLK, SD_CS_PIN);
#define SD1_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(4), &mySPI1)

#define FILENAME "dir/test_long_name123456789.txt"

#include <SPI.h>
//#include <SD.h>
#include "SdFat.h"
SdFat SD;

#define SD_CS_PIN PA4
File myFile;

const char compile_date[] = __DATE__ " " __TIME__;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.printf("Compilation Date: %s\n",compile_date);
  Serial.print("Initializing SD card...");

  //if (!SD.begin(SD1_CONFIG)) {
  if (!SD.begin(SD_CS_PIN, SD_SCK_MHZ(4))) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open(FILENAME, FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open(FILENAME);
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
