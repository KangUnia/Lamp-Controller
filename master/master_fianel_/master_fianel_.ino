#include<SoftwareSerial.h>
SoftwareSerial BTSerial(2,3);
int clockPin = 7;  //74HC595의 클럭핀과 연결
int latchPin = 6;  //74HC595의 래치핀과 연결
int dataPin = 8;  //74HC595의 데이터핀과 연결
int switcha = 9;
int switchs = 10;
int switchclockon = 11;
int switchclockoff = 12;
byte data1[]={0b00000000,0b00000000};
int number=0;
int IRspace=6;
int IRmotion=4;
int limitspace1=70;

void setup(){
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(IRmotion, INPUT);
  pinMode(switcha, INPUT);
  pinMode(switchs, INPUT);
  pinMode(switchclockon, INPUT);
  pinMode(switchclockoff, INPUT);
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop(){
  Switchcontrol();
  BTSERIAL(number);
  if(analogRead(IRspace)<limitspace1){//거리 센서 반응 들어오는거 확인
    for(int k=0;k<1000;k++){
      if(digitalRead(IRmotion)==1){
        number++;
        _595_out(number);
        BTSERIAL(number);
        Serial.println("human comein");
        delay(10);
      }else{
        Serial.println("human ready");
        delay(10);
      }
    }
  }else if(digitalRead(IRmotion)==1){//모션센서 반응 나가는거 확인
    for(int k0=0;k0<1000;k0++){
      if(analogRead(IRspace)<limitspace1){
        while(1){
          int Space=analogRead(IRspace);
          delay(10);
          if(Space+10<analogRead(IRspace)&&analogRead(IRspace)>limitspace1+5){//상승 기울기 감지
            number--;
            BTSERIAL(number);
            _595_out(number);
            break;
          }
        }
        delay(10);
      }else{
        delay(10);
      }
    }
  }else if(digitalRead(IRmotion)==1&&analogRead(IRspace)<limitspace1){
    Serial.println("errer checking at the same time");
  }
}

void BTSERIAL(int qjsgh){
  BTSerial.write(qjsgh);
  Serial.write(qjsgh);
  delay(100);
}
void Switchcontrol() {
  _595_out(number);
  if(digitalRead(switchclockon)==LOW&&digitalRead(switchclockoff)==HIGH){
    Serial.println("111111111111111111111");
   for(int k=0;;k++){
     if(digitalRead(switcha)==HIGH){
       number++;
       Serial.println(number);
       _595_out(number);   
       delay(400);
     }else if(digitalRead(switchs)==HIGH){
       number--;
       Serial.println(number);
       _595_out(number);
       delay(400);
     }
     if(digitalRead(switchclockon)==HIGH&&digitalRead(switchclockoff)==LOW){
       Serial.println("22222222222222222222");
       break;
     }
   } 
  } 
}

void _595_out(int k){
  switch(k){
    case 13:
    data1[0]=0b01010101;
    data1[1]=0b01011010;
    break;
    case -12:
    data1[0]=0b01111111;
    data1[1]=0b01111011;
    break;
    case -11:
    data1[0]=0b01111111;
    data1[1]=0b01111001;
    break;
    case -10:
    data1[0]=0b01111111;
    data1[1]=0b01110001;
    break;
    case -9:
    data1[0]=0b01111111;
    data1[1]=0b01100001;
    break;
    case -8:
    data1[0]=0b01111111;
    data1[1]=0b01000001;
    break;
    case -7:
    data1[0]=0b01111111;
    data1[1]=0b00000001;
    break;
    case -6:
    data1[0]=0b01111110;
    data1[1]=0b00000001;
    break;
    case -5:
    data1[0]=0b01111100;
    data1[1]=0b00000001;
    break;
    case -4:
    data1[0]=0b01111000;
    data1[1]=0b00000001;
    break;
    case -3:
    data1[0]=0b01110000;
    data1[1]=0b00000001;
    break;
    case -2:
    data1[0]=0b01100000;
    data1[1]=0b00000001;
    break;
    case -1:
    data1[0]=0b01000000;
    data1[1]=0b00000001;
    break;
    case 0:
    data1[0]=0b00000000;
    data1[1]=0b00000000;
    break;
    case 1:
    data1[0]=0b01000000;
    data1[1]=0b00000000;
    break;
    case 2:
    data1[0]=0b01100000;
    data1[1]=0b00000000;
    break;
    case 3:
    data1[0]=0b01110000;
    data1[1]=0b00000000;
    break;
    case 4:
    data1[0]=0b01111000;
    data1[1]=0b00000000;
    break;
    case 5:
    data1[0]=0b01111100;
    data1[1]=0b00000000;
    break;
    case 6:
    data1[0]=0b01111110;
    data1[1]=0b00000000;
    break;
    case 7:
    data1[0]=0b01111111;
    data1[1]=0b00000000;
    break;
    case 8:
    data1[0]=0b01111111;
    data1[1]=0b01000000;
    break;
    case 9:
    data1[0]=0b01111111;
    data1[1]=0b01100000;
    break;
    case 10:
    data1[0]=0b01111111;
    data1[1]=0b01110000;
    break;
    case 11:
    data1[0]=0b01111111;
    data1[1]=0b01111000;
    break;
    case 12:
    data1[0]=0b01111111;
    data1[1]=0b01111010;
    break;
  }
  digitalWrite(latchPin, LOW);  
  shiftOut(dataPin, clockPin, MSBFIRST, data1[0]); 
  shiftOut(dataPin, clockPin, MSBFIRST, data1[1]); 
  digitalWrite(latchPin, HIGH);   // 74hc595 출력핀으로 출력 시키기
}
