#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
 
#include <Wire.h>
#include <SSD1306Wire.h>

#include <WiFi_Logo.h>
 
// WiFi Configuration
const char* ssid     = "...."; // WiFi Name
const char* password = "........"; // WiFi Password
 
// NTP Server Configuration
const char* servidorNTP = "a.st1.ntp.br"; // NTP Server
 
const int fusoHorario = -10800; // Timezone Adjust (-03h = -10800 seg)
const int taxaDeAtualizacao = 1800000; // NTP Server Refresh Rate
 
WiFiUDP ntpUDP; // UDP Protocol Declaration
NTPClient timeClient(ntpUDP, servidorNTP, fusoHorario, 60000);
 
// OLED Display Configuration
SSD1306Wire display(0x3C, 5, 4);
 
void setup()
{  
  // Init Serial Communication for Debug
  Serial.begin(115200);
  delay(10);
 
 
  // Connect to the WiFi Network
  WiFi.begin(ssid, password);
 
  // Start Display
  display.init();
  display.clear();
  display.flipScreenVertically();
  //display.setFont(ArialMT_Plain_24); // Opções de tamanho de fonte: 10, 16, 24
  //display.setTextAlignment(TEXT_ALIGN_CENTER); // Opções de alinhamento: CENTER, LEFT, RIGHT
 
 
  // Waiting for WiFi Connection
  while (WiFi.status() != WL_CONNECTED)
  { // Display WiFi Logo
      display.clear();
      display.drawXbm(34, 2, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
      display.setFont(ArialMT_Plain_10);
      display.drawString(86, 2, "TM");
      display.display();
      delay(1000);
      display.clear();
      //display.drawString(63, 12, "Getting info");
      display.drawXbm(34, 2, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
      display.setFont(ArialMT_Plain_10);
      display.drawString(86, 2, "TM");
      display.setFont(ArialMT_Plain_24);
      display.drawString(53, 22, ".");
      display.display();
      delay(1000);
      display.clear();
      //display.drawString(63, 12, "Getting info");
      display.drawXbm(34, 2, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
      display.setFont(ArialMT_Plain_10);
      display.drawString(86, 2, "TM");
      display.setFont(ArialMT_Plain_24);
      display.drawString(53, 22, "..");
      display.display();
      delay(1000);
      display.clear();
      //display.drawString(63, 12, "Getting info");
      display.drawXbm(34, 2, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
      display.setFont(ArialMT_Plain_10);
      display.drawString(86, 2, "TM");
      display.setFont(ArialMT_Plain_24);
      display.drawString(53, 22, "...");
      display.display();
      delay(1000);
      display.display();
 
      Serial.print(".");
      //delay(500);
  }
   
  Serial.println("");
  Serial.print("WiFi connected. IP: ");
  Serial.println(WiFi.localIP());
 
  // Start Time Acquisition Client
  timeClient.begin();
}
  
void loop() {
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
 
  String horario = timeClient.getFormattedTime();
  int long rssi = WiFi.RSSI();
  
  display.clear(); // Clean Display
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0, "Time: " + horario);
  display.drawString(0, 12, "IP: " + WiFi.localIP().toString());
  display.drawString(0, 24, "Gateway: " + WiFi.gatewayIP().toString());
  display.drawString(0, 36, "Subnet: " + WiFi.subnetMask().toString());
  display.drawString(0, 48, WiFi.SSID() + " | Signal: " + WiFi.RSSI());

  if (rssi > -1) {
    // Zero (0) Bar
  } else if (rssi <= -1 & rssi > -45) { 
    display.fillRect(100, 10, 3, 3);
    display.fillRect(105, 8, 3, 5);
    display.fillRect(110, 6, 3, 7);
    display.fillRect(115, 4, 3, 9);
    display.fillRect(120, 2, 3, 11);
    display.fillRect(125, 0, 3, 13);
    // Six (6) Bars
  } else if (rssi <= -45 & rssi > -55) {
    display.fillRect(100, 10, 3, 3);
    display.fillRect(105, 8, 3, 5);
    display.fillRect(110, 6, 3, 7);
    display.fillRect(115, 4, 3, 9);
    display.fillRect(120, 2, 3, 11);
    // Five (5) Bars
  } else if (rssi <= -55 & rssi > -65) {
    display.fillRect(100, 10, 3, 3);
    display.fillRect(105, 8, 3, 5);
    display.fillRect(110, 6, 3, 7);
    display.fillRect(115, 4, 3, 9);
    // Four (4) Bars
  } else if (rssi <= -65 & rssi > -75) {
    display.fillRect(100, 10, 3, 3);
    display.fillRect(105, 8, 3, 5);
    display.fillRect(110, 6, 3, 7);
    // Three (3) Bars
  } else if (rssi <= -75 & rssi > -85) {
    display.fillRect(100, 10, 3, 3);
    display.fillRect(105, 8, 3, 5);
    // Two (2) Bars
  } else if (rssi <= -85 & rssi > -96) {
    display.fillRect(100, 10, 3, 3);
    // One (1) Bar
  } else {
    // Zero (0) Bar
  }
  display.display(); // Writes the Information on the Display
  delay(800);
}
