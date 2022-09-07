#define Hall_Sensor_A A0
#define Hall_Sensor_D 2

int Val_A=0,Val_D=0; 


void setup() {
  
  Serial.begin(115200);
  pinMode(Hall_Sensor_D, INPUT);

}

void loop() {

  Val_A=analogRead(Hall_Sensor_A);
  Serial.println(Val_A);

  Val_D=digitalRead(Hall_Sensor_D);
  Serial.print(Val_D);
   
}
