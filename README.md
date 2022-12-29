# BlinkMinutesNTP
Exemplo de código para acionar em intervalos longos de minutos utilizando NTP  - ESP8286 - Arduino

exemplo de uso da função

void loop() {
  timeClient.update(); // obtem o horario da internet
  hold(1000);// espera 1 seg
  interval(LED_BUILTIN, 2, true);   // pino, intervalo em minutos, Status do pino - Liga 2 min
  interval(LED_BUILTIN, 40, false); // pino, intervalo em minutos, Status do pino - Desliga 40 min
  hold(1000);// espera 1 seg
  Serial.println(timeClient.getFormattedTime()); //imprime o horario no formato data e hora
  yield();
}
