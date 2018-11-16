#include "param.h"

#define MAX_MILLIS 500 // Définit le nombre maximum de données du tableau 


// Déclaration de variables
long oldMillis = 0;
int pinLED[10] = {2, 3, 5, 7, 9, 11, 10, 8, 6, 4};
int i = 0;     // 0, 1, 2, 3, 4, 5,  6,  7, 8, 9
float HR = 120; //seulement à affecter ic si on nécessite de simuler un batement cardiaque
bool wasHigh = false;
int millisOfHigh[MAX_MILLIS]; // Tableau pour le [MAX_MILLIS]
int highCounter = 0; // Compteur de pic sur deltaTime (millisecondes)
int deltaTime = 3000; 


void setup() {
  Serial.begin (9600);
  for (int i = 0 ; i < 10 ; i++){
    pinMode (pinLED[i], OUTPUT);   // Définit chaque pin de LED en tant que sortie
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
      millisOfHigh[j] = 0;//--------------------------------------------Initialisation de la totalité des variable a 0
  }
}


int delayFromHeartRate(float HR){ // Définition de la fonction simulateur de pouls
  return int((1/(HR/60))*1000);
}
float valueOfPhotoTransistor(){ // Définition de la fonction qui lit les informations en A0
  return analogRead(A0);
}


void loop() {
  switch (CHOIX) {

    case 0:
      if (millis() >= (oldMillis + delayFromHeartRate(HR))){ // Comparaison entre le temps actuel et l'ajout du précedent + le temps qu'un pulsation se produise 
        oldMillis = millis(); // Actualisation de millis
        //Serial.println(i);
        digitalWrite (pinLED[i], HIGH); // Allumer LED du PIN i
        if(i == 0){
          digitalWrite (pinLED[9], LOW); // Il faut éteindre la led 9 car la pin 0-1 n'existe pas
        }else{
          digitalWrite (pinLED[i-1], LOW); // Création de l'effet de chenille a l'exception de la pin 0 
        }
        i++;
        if (i >= 10){ // Creation de la boucle
          i = 0;
        }
      }
      break;
    
    case 1:
      if (millis() >= (oldMillis + delayFromHeartRate(HR))){ // Comparaison entre le temps actuel et l'ajout du précedent + le temps qu'un pulsation se produise
        oldMillis = millis(); // Actualisation de millis
        for (int i = 0 ; i < 10 ; i++){ // Exctinction des LED pour l'initialisation
          digitalWrite (pinLED[i], LOW); 
        }
        for (int j = 0 ; j < 10 ; j++){
          if ((j+i)%eachXLED == 0){ // Calcul de la LED à choisir pour l'allumer, et si le calcul du modulo = 0 c'est donc un multiple ex: 0,2,4....
            digitalWrite (pinLED[(j)], HIGH);
          }
        }
        i++; 
        if (i >= eachXLED){ // Une fois le i incrémenté on le compare au saut de LED possible, et si il est dépassé on le réinitialise pour pouvoir recommencer
          i = 0;
        }
      }
      break;
 
    case 2:
      if (millis() >= (oldMillis + delayFromHeartRate(HR))){ // Comparaison entre le temps actuel et l'ajout du précedent + le temps qu'un pulsation se produise
        oldMillis = millis(); // Actualisation de millis
        if (i==0){ 
          digitalWrite (pinLED[LED], HIGH); // On allume la LED choisie 
          i=1;
        }else{
          digitalWrite (pinLED[LED], LOW); // On éteint la LED choisie
          i=0;
        }
      }
      break;
      
    case 3:
      if (millis() >= (oldMillis + delayFromHeartRate(HR))){ // Comparaison entre le temps actuel et l'ajout du précedent + le temps qu'un pulsation se produise
        oldMillis = millis(); // Actualisation de millis
        if (i==0){
          for (int i = 0 ; i < 10 ; i++){
            digitalWrite (pinLED[i], HIGH); // On allume toute les LED
          }
          i=1;
        }else{
          for (int i = 0 ; i < 10 ; i++){
            digitalWrite (pinLED[i], LOW); // On eteint toute les LED
          }
          i=0;
        }
      }
      break;      
  }
  
  if ((valueOfPhotoTransistor() > 375) && !wasHigh && (millis()-millisOfHigh[highCounter] > 250)){ // Permet de détecter un pic 
    millisOfHigh[highCounter] = millis();
    highCounter++; // ajout de 1 au compteur de pics
    wasHigh = true;
  }else if (valueOfPhotoTransistor() <= 375){ 
    wasHigh = false; // Défini qu'il n'y a pas de pic
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
