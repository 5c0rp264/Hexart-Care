#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<float.h>
#include"donnee.h"
#include"action.h"

void append(char *s, char c) {  ///fonction ajoutant un char a la fin d'un string
     int len = strlen(s);
     s[len] = c;
     s[len+1] = '\0';
}


void printData(data* dataToPrint,int size){ /// Fonction affichant la totalité du tableau contenant les données du fichiers CSV
	for (int i = 0; i < size; ++i)
	{
		printf("Temps : %.9ld Rythme cardiaque : %.4f\n",dataToPrint[i].timestamp, dataToPrint[i].heartRate );
	}
}


void calcAverageInbetweenInterval(data* dataToPrint,int size,long min, long max){ ///Fonction permettant de calculer la moyenne dans un intervalle de temps
	long sum = 0;
	int count = 0;
	for ( int i = 0; i<size; ++i){  ///Additionne tous les pouls compris dans cette intervalle
		if (dataToPrint[i].timestamp >= min && dataToPrint[i].timestamp <= max){
			sum+= dataToPrint[i].heartRate;
			count++;
		}
	}
	if (count != 0){
		double average = sum/count;
		printf("\n\nLa moyenne de pouls sur cette intervalle de temps est:%g\n", average);
	}else{
		printf("\n\nErreur aucune valeure dans cette intervalle");
	}

}


void searchForHeartRateOrHeartRate(data* dataToPrint,int size, double value, double choice){ ///Fonction de recherche séquentielle permettant de rechercher les pouls ou les temps
	printf("\n\nVoila les resultat:\n");
	for (int i = 0; i < size; ++i){
		//printf("timestamp : %.9ld heartRate %.4f value: %.3lf\n",dataToPrint[i].timestamp, dataToPrint[i].heartRate,value);
		if (choice == 0 && dataToPrint[i].timestamp == value){ ///recherche pouls
			printf("Temps : %.9ld Rythme cardiaque : %.4f\n",dataToPrint[i].timestamp, dataToPrint[i].heartRate );
		}else if (choice == 1 && ((int)dataToPrint[i].heartRate == (int)value)){///recherche temps
			printf("Temps : %.9ld Rythme cardiaque : %.4f\n",dataToPrint[i].timestamp, dataToPrint[i].heartRate );
		}
	}
}


void orderData(data* dataToPrint,int size){ ///Fonction de tri par sélection d'un élément au choix dans un order au choix
	//printData(arrayOfData, size);

	printf("Par quel mesure voulez vous que l'affichage soit tri ?\n");
	printf("[ 0 ] Temps\n");
	printf("[ 1 ] Rythme cardiaque\n");
	int whatToOrder;
	scanf("%d", &whatToOrder);
	printf("Comment voulez vous le trier ?\n");
	printf("[ 0 ] Croissant\n");
	printf("[ 1 ] Decroissant\n");
	int inWhatOrder;
	scanf("%d", &inWhatOrder);
	for (int i = 0; i < size; ++i){ ///Boucle au dans le tableau
		int oneToExchange = 0;

		if (inWhatOrder == 0) {///ordre croissant
			long double min = LONG_MAX;
			for (int j = i; j < size; ++j){
				if (whatToOrder == 1) {
					if (dataToPrint[j].heartRate <= min){ ///tri par BPM
						min = dataToPrint[j].heartRate;
						oneToExchange = j;
					}
				}else {
					if (dataToPrint[j].timestamp <= min ){ /// tri par temps
						min = dataToPrint[j].heartRate;
						oneToExchange = j;
					}
				}
			}
		}else{///ordre décroissant
			long double max = LONG_MIN;
			for (int j = i; j < size; ++j){
				if (whatToOrder == 1) {
					if (dataToPrint[j].heartRate >= max ){ ///tri par BPM
						max = dataToPrint[j].heartRate;
						oneToExchange = j;
					}
				}else {
					if (dataToPrint[j].timestamp >= max ){ ///tri par temps
						max = dataToPrint[j].heartRate;
						oneToExchange = j;
					}
				}
			}
		}
		data tmp = dataToPrint[i];
		dataToPrint[i] = dataToPrint[oneToExchange];
		dataToPrint[oneToExchange] = tmp;
	}
	printData(dataToPrint, size); ///affichage après tri
}



void openFile(char* fileName){ ///ouverture du fichier et enregistrement des données au sein d'un tableau de taille définie par le nombre de données
	FILE *csv;
	if((csv = fopen(fileName, "r")) == NULL) {
        fprintf(stderr, "Unable to open file."); ///open the file and test if their is no problem
        exit(-1);
    }

    int count = 0;

    for (char c = getc(csv); c != EOF; c = getc(csv)) {
        if (c == '\n'){
        	count = count + 1;
        } /// Increment count if this character is newline                  Count line to create array of struct as predicted
    }


    data arrayOfData[count];
    count = 0;
    int arg = 0;
    char tmp[50];
    rewind(csv); //faire revenir au début le fichier pour le relire et affecter les valeurs au sein du tableau

    for (char c = getc(csv); c != EOF; c = getc(csv)) { ///li charactère par charactère le fichier .csv afin d'extraire les données
    	if (c == ';' && arg == 0){
    		arg = 1;
    		arrayOfData[count].timestamp = atol(tmp);
    		strcpy(tmp, "");
    	}else if (c == ';' && arg == 1){
    		arrayOfData[count].heartRate = atof(tmp);
    		strcpy(tmp, "");
    	}
        else if (c == '\n'){
        	count = count + 1;
        	arg = 0; //arg is used here to mark first or second column of the CSV file
        } // Increment count if this character is newline
        else {
        	append(tmp,c);
        }
    }
    fclose(csv); //refermer fichier CSV
    //printData(arrayOfData, count);
    printf("\n\n\nQue voulez vous realiser ?\n"); ///choix parmis les possibilités
    printf("[ 0 ] Tri et affichage\n");
    printf("[ 1 ] Calcul d'une moyenne sur un intervalle de temps\n");
    printf("[ 2 ] Rechercher une valeur\n");
    printf("[ 3 ] Afficher le nombre de donnees\n");
    printf("[ 4 ] Afficher pouls min et max\n");
    int answer;
    scanf("%d", &answer);
    if (answer == 0){
    	printf("\n\n\nQue voulez vous realiser ?\n");
    	printf("[ 0 ] Tri puis affichage\n");
    	printf("[ 1 ] Affichage dans l'ordre du fichier CSV\n");
    	int answer;
    	scanf("%d", &answer);
    	if (answer == 0){
    		orderData(arrayOfData, count);
	    }else{
	    	printData(arrayOfData,count);
	    }
    }else if (answer == 1){
    	printf("\n\n\n");
    	printData(arrayOfData, count);
    	printf("\n\nMerci d'indiquer le minimum de l'intervalle que vous souhaitez:\n");
    	long minimum;
    	scanf("%ld", &minimum);
    	printf("Merci d'indiquer le maximum de l'intervalle que vous souhaitez:\n");
    	long maximum;
    	scanf("%ld", &maximum);
    	calcAverageInbetweenInterval(arrayOfData,count,minimum, maximum);
    }else if (answer == 2){
    	printData(arrayOfData,count);
    	printf("\n\n\nQue souhaitez-vous rechercher ?\n");
    	printf("[ 0 ] Temps\n");
    	printf("[ 1 ] Pouls\n");
    	int choice;
    	scanf("%d", &choice);
    	printf("\n\n\nQuel valeur cherchez-vous ?\n");
    	double value;
    	scanf("%lf", &value);
    	searchForHeartRateOrHeartRate(arrayOfData,count,value, choice);
    }else if (answer == 3){
    	printf("\n\nIl y a %d ligne dans le fichier CSV soit %d donnees\n", count, (count*2));
    }else{
		float min = FLT_MAX; ///!\/!\ très important afin de prendre en compte tout type de valeur dans une boucle cherchant le max et min
		float max = FLT_MIN;
		for (int i = 0; i < count; ++i){ //recherche séquentiel
			if (arrayOfData[i].heartRate >= max ){
				max = arrayOfData[i].heartRate;
			}
			if (arrayOfData[i].heartRate <= min){
				min = arrayOfData[i].heartRate;
			}
		}
		printf("\nLe minimum est %g et le maximum est %g\n", min, max);
    }
}






