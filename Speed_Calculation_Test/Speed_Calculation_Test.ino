#define Hall_Sensor 2

int mgnt = 0;
unsigned long thsTm;
unsigned long lstTm = 0;
unsigned long dffrncTm;
float scndTm;
float spd = 0;
float whlCrcmfrnc = 2.105;

#include <LiquidCrystal.h>
LiquidCrystal lcd(22, 24, 52, 50, 48, 46);

void setup() {
  
  Serial.begin(115200);
  pinMode(Hall_Sensor, INPUT);

  lcd.begin(16, 2);
  lcd.clear();

}

void loop() {

  lcd.setCursor (0, 0);
  
  mgnt = digitalRead(Hall_Sensor);
  thsTm = millis();
  
  if(mgnt == 1 && (thsTm - lstTm) > 100){
    thsTm = millis();
    dffrncTm = thsTm - lstTm;
    scndTm = (float)dffrncTm / 1000.0;
    spd = whlCrcmfrnc / scndTm * 3.6;
    lstTm = thsTm;

    lcd.print("Speed: ");
    lcd.print(spd);
    lcd.print("Km/h");
  
  }

}
