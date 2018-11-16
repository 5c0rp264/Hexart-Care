//From Arduino to Processing to CSV
//import
import processing.serial.*;
//declare
PrintWriter output;
Serial udSerial;
long zeroPoint;

void setup() {
  size(500,500);
  udSerial = new Serial(this, Serial.list()[0], 25000);
  output = createWriter ("ALEQ.csv");
  zeroPoint=-264; //définie un chiffre random pour l'affecter ensuite (parce que 264 c'est beau)
  background(0);
  textAlign(CENTER, CENTER); //aligne le texte au centre en X et en Y par rapport au commande passée a text()
}

void draw() {
  textSize(20);
  fill(255,0,0);
  text("Cliquez pour arreter la récupération de données",250,250);
  if (udSerial.available() > 0) {//s'executer seuleemnt si l'entrée série n'est pas vide
    if (zeroPoint==(-264)){
      zeroPoint=millis(); //définie le 0 pour le début 
    }
    String SenVal = udSerial.readString();
    SenVal = SenVal.replace("\n","");//empeche des bugs au sein du fichier CSV
    if (SenVal != null && float(SenVal) > 30 &&  float(SenVal) < 220) { //évite bug avec valeur abérente (problème de connection entre les deux saturation du serial etc) et n'écrit rien si il envvoie une valeur nulle
      output.print(millis()-zeroPoint);
      output.print(";");
      output.print(SenVal);
      output.println(";"); //permet de print les data dans le fichier CSV
      //println(SenVal);
    }
  }
}


void mouseClicked() { //arrete le code et enregistre lorsque l'on clique
  output.flush();
  output.close();
  exit();
}
