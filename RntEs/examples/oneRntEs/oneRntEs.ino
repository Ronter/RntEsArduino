#include <RntEs.h>

#define RNT_PIN						12
#define RNT_TIMEOUT_MS		2000

RntEs rnt(RNT_PIN);

void setup() {
  Serial.begin(9600);
}

void loop() {

  Serial.println("");

  if(rnt.getData(RNT_TIMEOUT_MS)) {

    Serial.print("SN: 0x");
    Serial.println(rnt.getSerial(), HEX);

    Serial.print("T : ");
    Serial.print(rnt.getTemperature(),1);
    Serial.println(" stC");

    Serial.print("P : ");
    Serial.print(rnt.getPressure(),1);
    Serial.println(" hPa");

    Serial.print("RH: ");
    Serial.print(rnt.getRH(),1);
    Serial.println(" %");

    Serial.print("AH: ");
    Serial.print(rnt.getAH(),1);
    Serial.println(" g/m3");

    Serial.print("DP: ");
    Serial.print(rnt.getDP(),1);
    Serial.println(" stC");

  } else {
    Serial.println("Timeout...");
  }
}
