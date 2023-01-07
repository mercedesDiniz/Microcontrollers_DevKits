/* millis():
- Descrição: Retorna o número de milissegundos passados desde que a placa Arduino começou a executar o programa atual. Sofre o overflow(é zerado) em aproximadamente 50 dias.
- Retorno: unsigned long com a tempo em milissegundos passados.

Link 01: https://www.arduino.cc/reference/pt/language/functions/time/millis/  */


/* Ex.01: imprime na porta serial o tempo em milissegundos passado desde que a placa começou a executar o código em si.*/

unsigned long t_ms;
unsigned long t_s;

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("Time: ");
  t_ms = millis();
  t_s = t_ms/1000;

  Serial.print(t_ms); // imprime o tempo desde que o programa iniciou
  Serial.print("ms = ");
  Serial.print(t_s);
  Serial.println("s");
  delay(1000);          // espera um segundo, para não enviar quantidades massivas de dados
}
  