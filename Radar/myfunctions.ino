/* 
Funktionen mäter distansen från ultraljudsensorn.
Parametrar: void.
Returnerar distans.
*/
int measureDist() {
  digitalWrite(trig, HIGH);
  delay(0);
  digitalWrite(trig, LOW);
  delay(0);
  unsigned int duration = pulseIn(echo, HIGH);  //Mäter tiden det tar för ljudet att skickas ut och studsa tillbaka till sensorn
  unsigned int distans = duration / 29 / 2;     // Omvandlar tiden till en distants genom att delvis dividera med ljudets hastighet
  return distans;
}