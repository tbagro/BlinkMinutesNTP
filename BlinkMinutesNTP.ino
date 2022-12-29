#include <NTPClient.h>    //Biblioteca do NTP
#include <ESP8266WiFi.h>  //Biblioteca do WiFi.
#include <WiFiUDP.h>      //Biblioteca do UDP.
#include <WiFiManager.h>  //https://github.com/tzapu/WiFiManager

WiFiManager wifiManager;
WiFiServer server(80);

WiFiUDP udp;                                                  //Cria um objeto "UDP".
int Tz = -4; // zona UTC
NTPClient timeClient(udp, "a.st1.ntp.br", Tz * 3600, 60000);  //Cria um objeto "NTP" com as configurações.

void hold(const unsigned int &ms) { //rotina de delay com millis, não usar para mais de 2 min
  // Non blocking delay
  unsigned long m = millis();
  while (millis() - m < ms) {
    yield(); // função de atraso, roda em segundo plano
  }
}


unsigned long getTime() { //converte o Time Epoch em segundos
  timeClient.update();
  unsigned long now = timeClient.getEpochTime();
  return now;
}


void interval(int PIN, const unsigned int &min, bool Status) { // pino, minuto, status do pino
  // Non blocking delay
  digitalWrite(PIN, Status);
  unsigned long intervalo = min * 60; // converte minutos para segundos

  unsigned long sec = getTime();  //salva o tempo inicial em EpochTime
  while ((getTime()) - sec < intervalo) { //compara o tempo inicial com o tempo final em relação ao intervalo
    Status = !Status;
    Serial.print("diff   :");
    Serial.println(getTime() - sec); // calcula e exibe os segundos da ação
    hold(1000);
  }
  Serial.print("status :");
  Serial.println(Status);
  hold(1000);
}


void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  wifiManager.setConfigPortalTimeout(180);
  wifiManager.autoConnect("ESPWebServer");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(F("Conectado"));
  server.begin();

  timeClient.begin();//Start NTP
}


void loop() {
  timeClient.update(); // obtem o horario da internet
  hold(1000);// espera 1 seg
  interval(LED_BUILTIN, 2, true);   // liga  pino X por 2 min
  interval(LED_BUILTIN, 40, false); // Desliga  pino X por 40 min
  hold(1000);// espera 1 seg
  Serial.println(timeClient.getFormattedTime()); imprime o horario no formato data e hora
  yield();
}
