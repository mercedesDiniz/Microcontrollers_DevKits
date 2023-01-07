/* Ex.02: refazendo o exemplo 01 (teste01_Millis) sem o delay.*/

unsigned long t0_ms; // tempo inicial (em ms)
unsigned long t0_s; // tempo inicial (em s)

unsigned long t_atual_ms; // tempo atual (em ms)
const unsigned long period_espera = 1000; // definindo a espera como 1s

void setup() {
  Serial.begin(115200);
  t0_ms = millis();
  t0_s = t0_ms/1000;
}

void loop() {
  t_atual_ms = millis(); // atualizando

  if ((t_atual_ms - t0_ms) >= period_espera){ // verificando se o período já passou
    Serial.print("Time: ");
    Serial.print(t0_ms); 
    Serial.print("ms = ");
    Serial.print(t0_s);
    Serial.println("s");

    t0_ms = t_atual_ms; 
    t0_s = t0_ms/1000;
  }
  
}
  