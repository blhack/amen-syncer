#include <CapSense.h>

int highpin = 3;
int sensepin = 4;
int ledpin = 2;
int rolling_buffer_array[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int rolling_baseline_array[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int average = 0;
int baseline = 0;
boolean touching = false;
CapSense   cs_3_4 = CapSense(highpin,sensepin);

mySerial = SoftwareSerial(

void setup()  
  {
  Serial.begin(9600);
  analogWrite(ledpin, 128);
  delay(100);
  analogWrite(ledpin, 0);
  for (int i; i < 20; i++) {
    long total1 =  cs_3_4.capSense(30);
    rolling_baseline_array[i] = total1;
  }
 }
  
int rolling_buffer(int senseval) {
  int rolling_average;
  int rolling_total;
  
  for (int i = 1; i < 10; i++) {
    rolling_buffer_array[i] = rolling_buffer_array[i-1];
  }
  rolling_buffer_array[0] = senseval;
  
  for (int i = 0; i < 20; i++) {
    rolling_total = rolling_total + rolling_buffer_array[i];
  }
  
  rolling_average = (rolling_total / 20);
  return(rolling_average);
}

int rolling_baseline(int senseval) {
  int rolling_average;
  int rolling_total;
  
  for (int i = 1; i < 10; i++) {
    rolling_baseline_array[i] = rolling_buffer_array[i-1];
  }
  rolling_baseline_array[0] = senseval;
  
  for (int i = 0; i < 20; i++) {
    rolling_total = rolling_total + rolling_baseline_array[i];
  }
  
  rolling_average = (rolling_total / 20);
  return(rolling_average);
}

void loop()                    
{
    long total1 =  cs_3_4.capSense(30);
    average = rolling_buffer(total1);
    if (average > 100) {
      analogWrite(ledpin, 128);
      if (touching == false) {
        Serial.println("TOUCHING!");
      }
      touching = true;  
    }
    else {
      analogWrite(ledpin, 0);
      baseline = rolling_baseline(total1);
      if (touching == true) {
        Serial.println("NO TOUCHING!");
      }
      touching = false;
     }
    Serial.println(float(average)/float(baseline));
    delay(100);                             // arbitrary delay to limit data to serial port 
}
