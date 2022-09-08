//libraries
  //dht
  #include "DHT.h"

  //lcd
  #include <LiquidCrystal.h>

//pin definitions
  //lcd (rs, enable, d4, d5, d6, d7)
  LiquidCrystal lcd(22, 24, 52, 50, 48, 46);

  //dht
  #define DHTPIN 8
  #define DHTTYPE DHT11
  DHT dht(DHTPIN, DHTTYPE);

  //hall sensor
  #define Hall_Sensor 2

//variables
  //hall sensor
  int mgnt;                                                                                                       //binary for if a magnet is detected
  unsigned long thsTm;                                                                                            //time since the program started currently in milliseconds
  unsigned long lstTm = 0;                                                                                        //time since the program started last revolution in milliseconds
  unsigned long dffrncTm;                                                                                         //time since last revolution in milliseconds
  float scndTm;                                                                                                   //time since last revolution in seconds
  float spd;                                                                                                      //speed of the vehicle in kilometres per hour
  float whlCrcmfrnc = 2.105;                                                                                      //wheel circumference in metres

  //humidity and temp
  float hmdty;                                                                                                    //raw humidity sensor reading
  float tmprtr;                                                                                                   //raw temperature sensor reading
  float htNdx;                                                                                                    //calculated temperature in celcius
  
void setup() {

  Serial.begin(115200);
  
  //make sure program is running
  Serial.println(F("Working!"));

  //lcd start (column, row) counting from 0
  lcd.begin(16, 2);
  lcd.clear();

  //dht start
  dht.begin();

  //hall sensor pin input mode
  pinMode(Hall_Sensor, INPUT);

}

void loop() {

  //set up screen with labels
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.setCursor(8, 0);
  lcd.print("Speed:");

  //speed sensor readings
  mgnt = digitalRead(Hall_Sensor);
  thsTm = millis();

  //error code if hall effect sensor not connected
  if (isnan(mgnt)){
    lcd.setCursor(8, 1);
    lcd.print("Workn't");
  }

  //calculate and print speed after every revolution
  if (mgnt == 1 && (thsTm - lstTm) > 100){                                                                        //if a magnet is sensed AND it's been more than 100ms since it was last detected then calculate the speed
    
    //speed calculation
    thsTm = millis();                                                                                             //update time to ensure correct calculation
    dffrncTm = thsTm - lstTm;                                                                                     //calculate time in milliseconds since last revolution
    scndTm = (float)dffrncTm / 1000.0;                                                                            //calculate time in seconds since last revolution
    spd = whlCrcmfrnc / scndTm * 3.6;                                                                             //calculate speed of kart in kilometres per hour ((wheel circumference in metres)/(time in seconds) * 3.6 (to convert to km/h))

    //print the speed with unit
    lcd.setCursor(8, 1);
    lcd.print(spd);
    lcd.print("Kph");

    //update the time at the last revolution
    lstTm = millis();

    //reset magnet variable to 0
    mgnt = 0;
    
  }
  
  //humidity and temptrature sensor readings
  hmdty = dht.readHumidity();
  tmprtr = dht.readTemperature();

  //error code if dht sensor not connected
  if (isnan(hmdty) || isnan(tmprtr)){                                                                             //if humidity OR temperature are not numbers then throw an error
    lcd.setCursor(0, 1);
    lcd.print("Workn't");
  }
  
  //calculate heat in celcius (temp reading, humidity reading, unit of temp (celcius false, farenheight true))
  htNdx = dht.computeHeatIndex(tmprtr, hmdty, false);

  //print heat with unit
  lcd.setCursor(0, 1);
  lcd.print(htNdx);
  lcd.print(char(223));
  lcd.print("C");

}
