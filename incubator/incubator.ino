#include "DHT.h"

#define DHTPIN 2

#define DHTTYPE DHT22

int HeatingPad = 6;                          // 릴레이 핀
int buttonPin = 5; 

const int Buzzer = 10;

DHT dht(DHTPIN,DHTTYPE);



void riningBuzzerHigh(){
  tone(Buzzer, 2000); // Send 1KHz sound signal...
  delay(100);        // ...for 1 sec
  noTone(Buzzer);     // Stop sound...
  delay(100);
}

void riningBuzzerLow(){
  tone(Buzzer, 500); // Send 1KHz sound signal...
  delay(100);        // ...for 1 sec
  noTone(Buzzer);     // Stop sound...
  delay(100);
}



void setup() {
    Serial.begin(9600);
    pinMode(HeatingPad, OUTPUT);  
    pinMode(buttonPin, OUTPUT);
    pinMode(DHTPIN, OUTPUT);
    pinMode(Buzzer, OUTPUT);
    dht.begin();  
}

void loop() {
    int turningkey = 1;
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (!isnan(humidity)&&humidity<=3600) {
      Serial.print("습도: ");
      Serial.println(humidity);
      if(55>humidity){
      riningBuzzerLow();
    }
    else if(60<humidity){
      riningBuzzerHigh();
    }
	  }

    if (!isnan(temperature) ) {
      Serial.print("온도: ");
       Serial.println(temperature);
        if(temperature<=36&&turningkey==1){
           digitalWrite(buttonPin,HIGH ); // turn on heating element 5 seconds
           digitalWrite(HeatingPad,LOW );
           turningkey=0;
        }
        else if(38<=temperature&&turningkey==1 ){
           digitalWrite(buttonPin,LOW ); // turn on heating element 5 seconds
           digitalWrite(HeatingPad,HIGH );
           turningkey=0;
        }
        else if(36<temperature&&temperature<38){
          turningkey=1;
        }
	  }

}
