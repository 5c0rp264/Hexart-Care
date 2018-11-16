

#include<stdio.h>
#include<stdlib.h>
#include"action.c"
#include"menu.h"
#include<conio.h>
#include"generationCode.c"

#define CLS printf("\n\nAppuyer sur une touche pour continuer\n");\
			getch();\
			system("cls");


void displayMenu(){
	system("cls");//efface tout
	system("color 0C"); //change la couleur
	system("TITLE HEXART CARE"); //change titre
	while(1){
		printf("\n\n");
		printf("    /|    //| |                              \n");
		printf("   //|   // | |     ___       __             \n");
		printf("  // |  //  | |   //___) ) //   ) ) //   / / \n");          ///C'est pas beau caaaaa ???
		printf(" //  | //   | |  //       //   / / //   / /  \n");
		printf("//   |//    | | ((____   //   / / ((___( (   \n");
		printf("\n\n");
		printf("Que souhaitez-vous realiser ?\n");
		printf("[  0  ] Generer un param.h\n");
        printf("[  1  ] Ouvrir le fichier Arduino\n");
        printf("[  2  ] Recuperer les donnees de l'arduino\n");
		printf("[  3  ] Afficher, trier ou chercher au sein du CSV\n");
		printf("[ 10  ] Instruction d'utilisation\n");
		printf("[ 42  ] Nous contacter");
		printf("\n[ 264 ] Quitter\n");
	    int answer;
	    scanf("%d", &answer);
	    if (answer == 0){
            CLS
            code(menu());
	    }else if (answer == 1){
            system("start coeur/coeur.ino");
	    }else if (answer == 2){
	    	system("start generateCSVWithConnexionToArduino/generateCSVWithConnexionToArduino.pde");
	    }else if (answer == 3){
	    	openFile("generateCSVWithConnexionToArduino/ALEQ.csv");
	    }else if (answer == 10){
	    	printf("Les instructions pour le bon fonctionnement de ce système sont a suivre etape par etape :\n");
            printf("\n");
            printf("-Dans le menu principale selectionner \"Generer un param.h\" puis choisissez l'option que vous preferez\n");
            printf("-Dans le menu principale selectionner \"Ouvrir le fichier Arduino\" puis televerse le et fermer l'IDE\n");
            printf("-Dans le menu principale selectionner \"Recuperer les donnees de l'arduino\" puis execute et \n     ferme a la fin de la recuperation des donnee\n");
            printf("-Dans le menu principale selectionner \"Afficher, trier ou chercher au sein du CSV\" puis faites ce que vous souhaitez\n");
	    }else if (answer == 42){
	    	printf("Nos mails:\n");
            printf("lloyd.gervot@viacesi.fr\n");
            printf("alex.brianceau@viacesi.fr\n");
            printf("enzo.lebrun@viacesi.fr\n");
            printf("quentin;aoustin@viacesi.fr\n");
	    }else{
	    	printf("\n\nAdios humanos, heureux d'avoir pu t'etre un peu utile\n\n");
	    	CLS
	    	system("color 0f"); //reset as default
	    	exit(0);
	    }
	    CLS
	}
}
