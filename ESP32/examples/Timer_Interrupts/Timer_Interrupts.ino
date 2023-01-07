/*  ESP32 Arduino: Timer interrupts
 *  Link: https://techtutorialsx.com/2017/10/07/esp32-arduino-timer-interrupts/
 *  
 * Os contadores do temporizador podem ser configurados para contagem crescente ou regressiva e suportam recarga automática e recarga de software.
 *  Eles também podem gerar alarmes quando atingem um valor específico, definido pelo software.
*/

/* Variaveis Globais: */
// contador que será usado pela ISR para sinalizar ao loop principal que ocorreu uma interrupção(compartilhada entre o loop principal e o ISR)
volatile int interruptCounter;
// contador adicional para rastrear quantas interrupções já ocorreram desde o início do programa 
int totalInterruptCounter;

hw_timer_t * timer = NULL; // ponteiro
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED; // p/ cuidar da sincronização

/* Rotina de Tratamento da Interrupção: 
 * uma função que retorne void e não receba argumentos;
 * deve ter o  atributo IRAM_ATTR  , para que o compilador coloque o código no IRAM
 */
void IRAM_ATTR onTimer() { 
  // Seção crítica (variável compartilhada):
  portENTER_CRITICAL_ISR(&timerMux); // o argumento é a variável global portMUX_TYPE
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux);
 
}
 
void setup() { // 
 
  Serial.begin(115200);
/* Configurando o timer: */

  /* Inicializando o timer: 
   * - retornar um ponteiro para uma estrutura do tipo hw_timer_t) 
   * - recebe o número do timer que queremos usar (de 0 a 3), o valor do prescaler e um flag
   * indicando se o contador deve contar p/ cima (true) ou p/ baixo (falso). */
  timer = timerBegin(0, 80, true); 

  /* Vinculando o timer a uma função de manipulação, que será executada quando a interrupção for gerada.
   *  - recebe como entrada um ponteiro para o timer inicializado, o endereço da função que irá tratar a 
   *  interrupção e um sinalizador indicando se a interrupção a ser gerada é borda (true) ou nível (false) . 
   */
  timerAttachInterrupt(timer, &onTimer, true);

  /* Especificar o valor do contador no qual a interrupção do temporizador será gerada
   * - recebe como entrada o ponteiro para o timer, o contador no qual a interrupção deve ser gerada 
   * e um sinalizador indicando se o timer deve recarregar automaticamente ao gerar a interrupção
   */
  timerAlarmWrite(timer, 1000000, true);
  
  /* Habilitando o timer.
   * receber como entrada nossa variável timer
   */
  timerAlarmEnable(timer);
 
}
 
void loop() {
  // verificar o valor do sinalizador de interrupções
  if (interruptCounter > 0) {
    // Seção crítica (variável compartilhada):
    portENTER_CRITICAL(&timerMux); // o argumento é a variável global portMUX_TYPE
    interruptCounter--; // decrementar o contador de interrupções
    portEXIT_CRITICAL(&timerMux);
 
    totalInterruptCounter++; // incrmenta o total de interrupções
 
    Serial.print("An interrupt as occurred. Total number: ");
    Serial.println(totalInterruptCounter);
 
  }
}
