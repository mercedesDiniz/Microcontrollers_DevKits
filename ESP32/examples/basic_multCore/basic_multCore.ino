// Criando identificador de tarefa
TaskHandle_t idTask1;
TaskHandle_t idTask2;

// Variaveis Globais:
int delay1 = 10000;
int delay2 = 5000;

void setup() {
  Serial.begin(115200);

  // Criando a tarefa 1:
  // Cria uma nova tarefa e adiciona à lista de tarefas que estão prontas para serem executadas
  xTaskCreatePinnedToCore(
                    Task1,      /*Função de tarefa. */
                    "Task1",     /* nome da tarefa. */
                    100000,     /* Tamanho da pilha da tarefa */
                    NULL,       /* parâmetro da tarefa */
                    1,          /* prioridade da tarefa */
                    &idTask1,   /* Identificador de tarefas para acompanhar a tarefa criada */
                    0);         /* núcleo em que a tarefa será executada*/                  
  delay(500); // boa pratica

  // Criando a tarefa 2:
  // Cria uma nova tarefa e adiciona à lista de tarefas que estão prontas para serem executadas
  xTaskCreatePinnedToCore(
                    Task2,      /*Função de tarefa. */
                    "Task2",     /* nome da tarefa. */
                    100000,     /* Tamanho da pilha da tarefa */
                    NULL,       /* parâmetro da tarefa */
                    2,          /* prioridade da tarefa */
                    &idTask2,   /* Identificador de tarefas para acompanhar a tarefa criada */
                    1);         /* núcleo em que a tarefa será executada*/                  
  delay(500); // boa pratica

  
}

// Função da tarefa 1:
void Task1(void * pvParameters){
  Serial.println("");
  String taskMessage = "Eu sou a Tarefa 1, estou no Core ";
    taskMessage = taskMessage + xPortGetCoreID();
    Serial.print(taskMessage);
    //
    Serial.print(".");
    delay(delay1);
    Serial.println("");
    
}

// Função da tarefa 2:
void Task2(void * pvParameters){
  Serial.println("");
  String taskMessage = "Eu sou a Tarefa 2, estou no Core ";
    taskMessage = taskMessage + xPortGetCoreID();
    Serial.print(taskMessage);
       //
    Serial.print(".");
    delay(delay2);
    Serial.println("");
    
}


void loop() {}
