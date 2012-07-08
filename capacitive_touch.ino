#include <CapSense.h>
int highpin = 3;
int sensepin = 4;
boolean calib = 0;
int baseline = 0;

CapSense amen = CapSense(highpin,sensepin);

void setup() {
  Serial.begin(9600);
  calib = true;
}

void loop() {
  if (calib == true) {
    Serial.println("calibrating");
    int calib_total = 0;
    for (int i = 0; i<=100; i++) {
      calib_total = calib_total + amen.capSense(30);
    }
    baseline = (calib_total / 100.0);
    calib = false;
    Serial.println(baseline);
    delay(1000);
  }
  int risetime = amen.capSense(30);
  Serial.println(risetime);
  delay(10);
}
