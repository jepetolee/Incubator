#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

const int HeatingPad = A5;
int directionPinDC = 12;
int pwmPinDC = 3;
int brakePinDC = 9;

const int Buzzer = 10;
unsigned long previousMillis = 0;  // 이전 실행 시간
const long interval = 6 * 60 * 60 * 1000;  // 6시간을 밀리초로 변환
bool directionState;


DHT dht(DHTPIN,DHTTYPE);



void riningBuzzerHigh(){
  tone(Buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(Buzzer);     // Stop sound...
  delay(1000)
}

void riningBuzzerLow(){
  tone(Buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(Buzzer);     // Stop sound...
  delay(1000)
}

int humidity(){
  return dht.readHumidity();
}

int temperature(){
  return dht.readTemperature();
}

void controlHeat(int delayTime){
  digitalWrite(HeatingPad, HIGH); // turn on heating element 5 seconds
  delay(delayTime);
  digitalWrite(HeatingPad, LOW);  // turn off heating element 5 seconds
  delay(delayTime);
}

/*void controlDC(){
  directionState = !directionState;
  if(directionState == false){
  digitalWrite(directionPinDC, LOW);
  }
  else{
  digitalWrite(directionPinDC, HIGH);
  }
  digitalWrite(brakePinDC, LOW);
  analogWrite(pwmPinDC, 30);
  delay(2000);
  digitalWrite(brakePinDC, HIGH);
  analogWrite(pwmPinDC, 0);
  delay(2000);
} if you get a bug, then check this code.*/


void controlFlip(){
 
  digitalWrite(directionPinDC, HIGH);

  digitalWrite(brakePinDC, LOW);
  analogWrite(pwmPinDC, 30);
  delay(2000);
  digitalWrite(brakePinDC, HIGH);
  analogWrite(pwmPinDC, 0);
  delay(2000);
}


// The main codes are there


void setup() {
    Serial.begin(9600);
    pinMode(HeatingPad, OUTPUT);
    pinMode(HumidTempSensor, OUTPUT);
    pinMode(directionPinDC, OUTPUT);
    pinMode(pwmPinDC, OUTPUT);
    pinMode(brakePinDC, OUTPUT);
    pinMode(Buzzer, OUTPUT);

}

void loop() {
    int heatDelay =500;
    if(controlHeat()<=38){
      controlHeat(heatDelay--);
    }
    else if(36<=controlHeat() ){
      controlHeat(heatDelay++);
    }
    if(55>humidity()){
      riningBuzzerLow();
    }
    else if(60<humidity()){
      riningBuzzerHigh();
    }
  unsigned long currentMillis = millis();  // 현재 시간 가져오기

  // 일정 간격마다 실행
  if (currentMillis - previousMillis >= interval) {
     controlFlip();
    // 이전 실행 시간 갱신
    previousMillis = currentMillis;
  }


}
