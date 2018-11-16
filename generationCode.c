#include <stdio.h>
#include <stdlib.h>

#include "generationCode.h"


int menu() // Menu et choix du mode d'affichage du rythme avec le coeur de LEDs
{
    int choix;
    printf("------------------Menu de gestion du coeur de LEDs------------------\n\n");
    printf("Entrez 0 pour allumer les LEDs en mode chenille\n\n");
    printf("Entrez 1 pour allumer une LED toute les X LEDs \n\n");
    printf("Entrez 2 pour allumer une LED au choix \n\n");
    printf("Entrez 3 pour allumer toutes les LEDs \n\n");
    scanf("%i", &choix);

    return choix;
}

void code(int choix)
{

    switch(choix)// Selon le choix, execute la fonction correpondante
    {
        case 0: // Mode 0 : CHENNILE
            chenille();
            break;

        case 1:
            blinkEachXLED(); //Mode permettant de faire clignoter une led sur X que l'utilisateur choisi
            break;

        case 2:
            chooseLED(); //fonctionne sur une seul led au choix
            break;

        case 3:
            allTurnedON(); //fonctionne sur la totalité des LED
            break;
    }
}

void chenille(){
    writeFile(0,0,2);
}

void chooseLED(){
    int pin;
    printf("\n\n Quel LED voulez-vous allumer ? (De 0 a 9) \n\n\t-> ");
    scanf("%i", &pin);
    writeFile(2,pin,2);
}

void blinkEachXLED(){
    int eachXLED;
    printf("\n\n Quel intervalle de LED eteinte souhaitez vous entre chaque DEL allumee ? (De 0 a 9) \n\n\t-> ");
    scanf("%i", &eachXLED);
    writeFile(1,0,eachXLED);
}

void allTurnedON(){
    writeFile(3,0,2);

}

void writeFile(int choice, int LED, int eachXLED){ //évite de repeter fois le meme code
    FILE* fichier = NULL; // Ouverture du param.h
    fichier = fopen("coeur/param.h", "w+"); //param.h dans le dossier coeur contenant le code Arduino C
    if (fichier != NULL)
    {
        fprintf(fichier,"#define CHOIX %i \n#define LED %i\n#define eachXLED %i\n", choice, LED, eachXLED); //macros pour definir le mode pour le programme + écriture dans le fichier
        printf("\n\nLe fichier param.h a recupere le mode d'affichage\n");
        fclose(fichier);
    }
}
