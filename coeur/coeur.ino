#include "param.h"

#define MAX_MILLIS 500


// Déclaration de variables
long oldMillis = 0;
int pinLED[10] = {2, 3, 5, 7, 9, 11, 10, 8, 6, 4};
int i = 0;         // 0,1,2,3,4,5,6,7,8,9
float HR = 120; //seulement à affecter ic si on nécessite de simuler un batement cardiaque
bool wasHigh = false;
int millisOfHigh[MAX_MILLIS];
int highCounter = 0;
int deltaTime = 3000;


void setup() {
  Serial.begin (9600);
  for (int i = 0 ; i < 10 ; i++){
    pinMode (pinLED[i], OUTPUT);   // Définit chaque pin de LED
  }

  //--------------------Petite animation---------------------------
  for (int i = 0 ; i < 10 ; i++){
        digitalWrite (pinLED[i], HIGH);
        delay(50);
  }
  for (int i = 0 ; i < 10 ; i++){
    digitalWrite (pinLED[i], LOW);
    delay(50);
  }
  //--------------------------------------------------------------
  for (int j = 0; j < 500; j++){
      millisOfHigh[j] = 0;//--------------------------------------------Initialisation de la totalité de la variable a 0
  }
}


int delayFromHeartRate(float HR){
  return int((1/(HR/60))*1000);
}
float valueOfPhotoTransistor(){
  return analogRead(A0);
}


void loop() {
  switch (CHOIX) {

    case 0:
      if (millis() >= (oldMillis + delayFromHeartRate(HR))){
        oldMillis = millis();
        //Serial.println(i);
        digitalWrite (pinLED[i], HIGH); // Allumer LED du PIN
        if(i == 0){
          digitalWrite (pinLED[9], LOW);
        }else{
          digitalWrite (pinLED[i-1], LOW);
        }
        i++;
        if (i >= 10){
          i = 0;
        }
      }
      break;
    
    case 1:
      if (millis() >= (oldMillis + delayFromHeartRate(HR))){
        oldMillis = millis();
        for (int i = 0 ; i < 10 ; i++){
          digitalWrite (pinLED[i], LOW);
        }
        for (int j = 0 ; j < 10 ; j++){
          if ((j+i)%eachXLED == 0){
            digitalWrite (pinLED[(j)], HIGH);
          }
        }
        i++;
        if (i >= eachXLED){
          i = 0;
        }
      }
      break;
 
    case 2:
      if (millis() >= (oldMillis + delayFromHeartRate(HR))){
        oldMillis = millis();
        if (i==0){
          digitalWrite (pinLED[LED], HIGH);
          i=1;
        }else{
          digitalWrite (pinLED[LED], LOW);
          i=0;
        }
      }
      break;
    case 3:
      if (millis() >= (oldMillis + delayFromHeartRate(HR))){
        oldMillis = millis();
        if (i==0){
          for (int i = 0 ; i < 10 ; i++){
            digitalWrite (pinLED[i], HIGH);
          }
          i=1;
        }else{
          for (int i = 0 ; i < 10 ; i++){
            digitalWrite (pinLED[i], LOW);
          }
          i=0;
        }
      }
      break;      
  }
  
  if ((valueOfPhotoTransistor() > 375) && !wasHigh && (millis()-millisOfHigh[highCounter] > 250)){
    millisOfHigh[highCounter] = millis();
    highCounter++;
    wasHigh = true;
  }else if (valueOfPhotoTransistor() <= 375){
    wasHigh = false;
  }
  while ((millisOfHigh[0]<= (millis()-deltaTime) && highCounter>0)){
    for (int j = 0; j < highCounter; j++){
      millisOfHigh[j] = millisOfHigh[j+1];
    }
    highCounter = highCounter - 1;
  }
  if (highCounter != 0){
    HR = (highCounter*60000)/(millis()-millisOfHigh[0]);
    if (HR > 35) {
          Serial.println(HR);
    }else{
      for (int j = 0; j < 500; j++){
        millisOfHigh[j] = 0;
      }
      highCounter = 0;
    }
  }
}
