/* o LED ficará aceso e apagado por exatamente um segundo. */

#define OCIOSO_ANTES_DE_LIG 0
#define OCIOSO_ANTES_DE_DES 1
#define ESTADO_LED_LIGADO 2
#define ESTADO_LED_DESLIGADO 3   

volatile int estado_atual;
 
unsigned long startTime;  // tempo de inicio
unsigned long currentTime; // tempo atual
const unsigned long period = 1000; // periodo de 1s
const byte ledPin = 2; // led do ESP

void setup()
{
    pinMode(ledPin, OUTPUT);
    startTime = millis();  //inicializando 
    estado_atual = ESTADO_LED_LIGADO; // estado inicial
}

void loop()
{   
    switch (estado_atual){
    case ESTADO_LED_LIGADO:
        digitalWrite(ledPin, HIGH); // Liga o LED 
        estado_atual = OCIOSO_ANTES_DE_DES;
        break;
        
    case OCIOSO_ANTES_DE_DES:
        currentTime = millis(); // atualizando
        if (currentTime - startTime >= period) // verificando se o período já passou
        {   
            startTime = currentTime; 
            estado_atual = ESTADO_LED_DESLIGADO; //se sim, muda o estado do LED.    
        }else{
            estado_atual = OCIOSO_ANTES_DE_DES;
        }
        break;

    case ESTADO_LED_DESLIGADO:
        digitalWrite(ledPin, LOW); // Desliga o LED
        estado_atual = OCIOSO_ANTES_DE_LIG;
        break;

    case OCIOSO_ANTES_DE_LIG:
        currentTime = millis(); // atualizando
        if (currentTime - startTime >= period) // verificando se o período já passou
        {   
            startTime = currentTime; 
            estado_atual = ESTADO_LED_LIGADO; //se sim, muda o estado do LED.    
        }else{
            estado_atual = OCIOSO_ANTES_DE_LIG;
        }
        break;       

    default:
        estado_atual = ESTADO_LED_LIGADO; // estado inicial
        break;
    }
    
}