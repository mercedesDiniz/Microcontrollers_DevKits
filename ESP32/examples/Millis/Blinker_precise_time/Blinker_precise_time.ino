/* Ex.02: o LED ficará aceso e apagado por exatamente um segundo.
Link: https://www.delftstack.com/pt/howto/arduino/arduino-millis/ */

unsigned long startTime;  // tempo de inicio
unsigned long currentTime; // tempo atual
const unsigned long period = 1000; // periodo de 1s
const byte ledPin = 2; // led do ESP

void setup()
{
    pinMode(ledPin, OUTPUT);
    startTime = millis();  //inicializando 
}

void loop()
{
    currentTime = millis(); // atualizando 
    if (currentTime - startTime >= period) // verificando se o período já passou
    {
        digitalWrite(ledPin, !digitalRead(ledPin)); //se sim, muda o estado do LED.
        startTime = currentTime; 
    }
}