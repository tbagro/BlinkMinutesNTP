# BlinkMinutesNTP
Exemplo de código para acionar em intervalos longos de minutos utilizando NTP  - ESP8286 - Arduino

exemplo de uso da função

void loop() {
  // obtem o horario da internet
  timeClient.update(); 
 // espera 1 seg  
  hold(1000);
  
  // pino, intervalo em minutos, Status do pino - Liga 2 min
  interval(LED_BUILTIN, 2, true); 
  
  // pino, intervalo em minutos, Status do pino - Desliga 40 min
  interval(LED_BUILTIN, 40, false); 
  
  // espera 1 seg
  hold(1000);
  //imprime o horario no formato data e hora
  Serial.println(timeClient.getFormattedTime()); 
  yield();
}
