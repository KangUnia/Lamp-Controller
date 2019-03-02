#include <SoftwareSerial.h>
SoftwareSerial BTSerial(3, 5);
int tem=1;
int buzzer=2;
int cds=0;
int onoff=LOW;

void setup(){
   Serial.begin(9600);
   BTSerial.begin(9600);
   pinMode(buzzer, OUTPUT);
}
void loop(){
  int temperture0=temper();
  int ligth=Ligth();
  
  if(temperture0<300){
    if(onoff==LOW&&light<20){
        int humen_number=btserial();
        if(humen_number>0){
          onoff=HIGH;
          digitalWrite(12, HIGH);
        }else{
          onoff=LOW;
          digitalWrite(12, HIGH);
        }
    }
  }
  delay(500);
}

int btserial(){
  int val=0;
  if(BTSerial.available()){
    val = BTSerial.read();
    Serial.println(val);
  }
  return val;
}
int Ligth(){
  int lightLevel = analogRead(cds);
  Serial.println(lightLevel);
  return lightLevel;
}
int temper(){
  int temperature = analogRead(tem);
  Serial.println("temperature="+temperature);
  return temperature;
}
void Buzzer(int k) {//1일 때만 동작
  if(k==1){
    for (int x=0; x<180; x++) {
      float sinval = (sin(x+(3.1412/15)));
      int toneVal = 350+(int(sinval*1000));
      tone(buzzer, toneVal);
      delay(2);
    }
  }  
}
