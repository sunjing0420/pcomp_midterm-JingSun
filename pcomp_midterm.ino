#include <Servo.h>

//color sensor
int s0Pin=2;
int s1Pin=4;
int s2Pin=7;
int s3Pin=8;
int outPut= 9;

//RGB LED
const int redPin = 5;
const int greenPin = 6;
const int bluePin = 3;

unsigned int frequencyR = 0;
unsigned int frequencyG = 0;
unsigned int frequencyB = 0;

//touch sensor
int touchPin=13;

//servo
int servoPin=12;
Servo myservo;  
int pos = 0;

//yellow led
int yellowLedPin=10;
int yellowLedVal=0;

//white led
int whiteLedPin=11;
int whiteLedVal=0;

int waitTime = 100;
bool ledState = true;
unsigned long lastBlinkTime = 0;

bool swi = false;
 
 
void setup()
{
       Serial.begin(9600);
       
       pinMode(s0Pin, OUTPUT);
       pinMode(s1Pin, OUTPUT);
       pinMode(s2Pin, OUTPUT);
       pinMode(s3Pin, OUTPUT);
      
       pinMode(outPut, INPUT);

       digitalWrite(s0Pin,HIGH);
       digitalWrite(s1Pin,LOW);//setting frequency selection

       pinMode(redPin, OUTPUT);
       pinMode(greenPin, OUTPUT);
       pinMode(bluePin, OUTPUT);

       myservo.attach(servoPin);

       pinMode(yellowLedPin, OUTPUT);
       pinMode(whiteLedPin, OUTPUT);
       
       pinMode(touchPin, INPUT);
}

float t= 0;

      void moving(){
        
         float amplitude=127;
         float frequency1=0.1;
         float frequency2=0.5;
         float baseLine=128;

         for (pos = 0; pos <= 180; pos += 1) { 
              myservo.write(pos);

         yellowLedVal= amplitude*sin(frequency1*radians(t))+baseLine;
         whiteLedVal= amplitude*sin(frequency2*radians(t))+baseLine;
         digitalWrite(yellowLedPin,HIGH);
         analogWrite(whiteLedPin,whiteLedVal);   
         t+=20;     
              delay(20);                       
              }
         for (pos = 180; pos >= 0; pos -= 1) { 
              myservo.write(pos);      
         yellowLedVal= amplitude*sin(frequency1*radians(t))+baseLine;
         whiteLedVal= amplitude*sin(frequency2*radians(t))+baseLine;
         digitalWrite(yellowLedPin,HIGH);
         analogWrite(whiteLedPin,whiteLedVal);       
         t+=20; 
              delay(20);                       
              }             
}


      void blinking(){
        for(int i = 0; i<1000; i++){
          
           unsigned long currentTime = i;
           if (currentTime - lastBlinkTime > waitTime) {
           ledState = !ledState;
           lastBlinkTime = i;
          }
  Serial.println(ledState);
  if (ledState) {
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(whiteLedPin, LOW);
  } else {
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(whiteLedPin, HIGH);
  }        
        }
//         float amplitude=127;
//         float frequency1=0.2;
//         float frequency2=0.5;
//         float t=radians(millis());
//         float baseLine=128;
//
//         for(int i = 0; i<4000 ; i+=5){
//         yellowLedVal= amplitude*sin(frequency1*radians(i))+baseLine;
//         whiteLedVal= amplitude*sin(frequency2*radians(i))+baseLine;
//  
//         analogWrite(yellowLedPin,yellowLedVal);
//         analogWrite(whiteLedPin,whiteLedVal);
//         delay(10);
          }



      void loop(){
        Serial.println(swi);
        if(swi==true){
       //Red         
       digitalWrite(s2Pin,LOW);
       digitalWrite(s3Pin,LOW);//setting for RED color sensor
       frequencyR = pulseIn(outPut, LOW);//reading frequency
//       int frequencyRR = map(frequencyR, 25,72,255,0);
               
       //Blue 
       digitalWrite(s2Pin,LOW);
       digitalWrite(s3Pin,HIGH);// setting for BLUE color sensor
       frequencyB = pulseIn(outPut, LOW);// reading frequency
//       int frequencyBB = map(frequencyB, 25,70,255,0);
               
       //Green          
       digitalWrite(s2Pin,HIGH);
       digitalWrite(s3Pin,HIGH);// setting for GREEN color sensor
       frequencyG = pulseIn(outPut, LOW);// reading frequency
//       int frequencyGG = map(frequencyG, 30,90,255,0);
       
       Serial.print("R: ");
       Serial.print(frequencyR);
       Serial.print("/  G: ");
       Serial.print(frequencyG);
       Serial.print("/  B: ");
       Serial.print(frequencyB);
       Serial.println(" ;");
       delay(100);

       if(frequencyR>40&&frequencyR<60&&frequencyG>90&&frequencyG<110&&frequencyB>40&&frequencyB<60){

       analogWrite(redPin, frequencyR+100);
       analogWrite(greenPin, frequencyG-50);
       analogWrite(bluePin, frequencyB+80);
      
       }

       else if(frequencyR>55&&frequencyR<75&&frequencyG>180&&frequencyG<200&&frequencyB>170&&frequencyB<190){

       analogWrite(redPin, frequencyR+20);
       analogWrite(greenPin, frequencyG+150);
       analogWrite(bluePin, frequencyB+140);
      
       }else if(frequencyR>15&&frequencyR<35&&frequencyG>30&&frequencyG<50&&frequencyB>20&&frequencyB<40){

       analogWrite(redPin, frequencyR+200);
       analogWrite(greenPin, frequencyG+140);
       analogWrite(bluePin, frequencyB+170);
      
       }else if(frequencyR>45&&frequencyR<65&&frequencyG>25&&frequencyG<45&&frequencyB>10&&frequencyB<30){

       analogWrite(redPin, frequencyR+200);
       analogWrite(greenPin, frequencyG+140);
       analogWrite(bluePin, frequencyB+170);
      
       }else if(frequencyR>30&&frequencyR<50&&frequencyG>40&&frequencyG<60&&frequencyB>30&&frequencyB<50){

       analogWrite(redPin, frequencyR+140);
       analogWrite(greenPin, frequencyG+140);
       analogWrite(bluePin, frequencyB+120);
      
       }else if(frequencyR>10&&frequencyR<30&&frequencyG>30&&frequencyG<50&&frequencyB>50&&frequencyB<70){

       analogWrite(redPin, frequencyR+200);
       analogWrite(greenPin, frequencyG+150);
       analogWrite(bluePin, frequencyB-50);
      
       }else{
       
       analogWrite(redPin, 0);
       analogWrite(greenPin, 105);
       analogWrite(bluePin, 220);
      
       }
       
        }else{
          digitalWrite(yellowLedPin, LOW);
          digitalWrite(whiteLedPin, LOW);
       analogWrite(redPin, 0);
       analogWrite(greenPin, 0);
       analogWrite(bluePin, 0);
          }
       
  
         if(digitalRead(touchPin)==HIGH){ 
           moving();
           blinking(); 
           swi = !swi;
         }else{   
           Serial.println("OFF");
         }  
   }         
