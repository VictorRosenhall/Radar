/*
Fil: Radar.ino
Skribent: Victor Rosenhall
Datum: 2025/02/06
Programmet är kod till en radar som använder en ultraljudsensor för att få en distans som input till en u8glib oled-skärm och servomotor.
*/

// Bibliotek
#include "Servo.h"
#include "U8glib.h"

// Pins
const int servoPin = 9;
const int trig = 12;
const int echo = 11;

// Objekt
U8GLIB_SSD1306_128X64 u8g;
Servo myservo;

// Globala Variabler
const int centerX = 63;  // X-koordinat för centrum
const int centerY = 0;   // Y-koordinat för centrum
const int radius = 63;   // Radie på halvcirkel
const int mapDist = 120;

void setup() {

  // Startar seriell kommunikation
  Serial.begin(9600);
  Serial.println("Start");

  // Starta Hårdvara
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  myservo.attach(servoPin);

  // Inställningar
  u8g.setFont(u8g_font_6x10);
}

void loop() {
  // svep från 0 to 180 grader:
  for (int angle = 0; angle <= 179; angle += 5) {  //Inkrementerar angle med 5
    u8g.firstPage();
    Serial.println(measureDist());
    int calcMeasureDist = measureDist();  //Gör funktionens värde till en variabel  (viktigt för att x och y uträkningarna)
    Serial.println("Vinkel: " + String(angle) + "Distans: " + String(measureDist()));
    do {
      u8g.drawCircle(centerX, centerY, radius);
      float radian = angle * 3.14159 / 180;                                         // Omvandlar grader till radianer
      int x = centerX + map(calcMeasureDist, 0, mapDist, 0, radius) * cos(radian);  // Beräkna x-koordinat i slutet av linjen
      int y = centerY + map(calcMeasureDist, 0, mapDist, 0, radius) * sin(radian);  // Beräkna y-koordinat i slutet av linjen
      delay(5);
      u8g.drawLine(centerX, centerY, x, y);  //Ritar ut radarlinjen
      delay(5);
    } while (u8g.nextPage());

    myservo.write(180 - angle);  //Roterar servomotorn höger till vänster
    delay(5);
  }
}