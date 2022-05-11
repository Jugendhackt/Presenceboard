//Karte 1 TAG: 6E 5D E2 2B, 23918
//Karte 2 TAG: CE 70 DF 2B, 28878
//Chip 3 TAG:  2B 50 73 5B, 20523
//Chip 4 TAG:  C3 70 96 BB, 28867

#include <SPI.h> // SPI-Bibiothek hinzufügen
#include <MFRC522.h> // RFID-Bibiothek hinzufügen
#include <Adafruit_NeoPixel.h>

#define SS_PIN      10 // SDA an Pin 10 
#define RST_PIN     9 // RST an Pin 9 
#define PIN         6 // Which pin on the Arduino is connected to the NeoPixels?
#define DELAYVAL    500 // Time (in milliseconds) to pause between pixels
#define NUMPIXELS   9 // How many NeoPixels are attached to the Arduino?

MFRC522 mfrc522(SS_PIN, RST_PIN); // RFID-Empfänger benennen
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int in_compl_ID = 0;
int compl_ID = 0;

int schalter_1 = 0;
int schalter_2 = 0;
int schalter_3 = 0;
int schalter_4 = 0;
int orte[4];
int an;



void setup() // Beginn des Setups:
{
  Serial.begin(9600); // Serielle Verbindung starten (Monitor)
  Serial.print("an");
  SPI.begin(); // SPI-Verbindung aufbauen
  mfrc522.PCD_Init(); // Initialisierung des RFID-Empfängers
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  orte[0] = 0;
  orte[1] = 0;
  orte[2] = 0;
  orte[3] = 0;
  pixels.clear();
}

void loop() // Hier beginnt der Loop-Teil
{
  schalter_1 = digitalRead(2); //Schalter 1 auf Eingang 2 gelegt
  schalter_2 = digitalRead(3);//Schalter 2 auf Eingang 3 gelegt
  schalter_3 = digitalRead(4); //Schalter 3 auf Eingang 4 gelegt
  schalter_4 = digitalRead(5);//Schalter 4 auf Eingang 5 gelegt

  for(int i = 0; i < 4; i = i + 1){
    if (an){
      switch(orte[i]){
        case 3:
          Serial.print("0");
          pixels.setPixelColor(i, pixels.Color(128, 128, 128));
          break;
        case 2:
          pixels.setPixelColor(i, pixels.Color(255, 255, 0));
          break;
        case 1:
          pixels.setPixelColor(i, pixels.Color(128, 0, 255));
          break;
        case 0:
          pixels.setPixelColor(i, pixels.Color(255, 0, 0));
          break;
      }
    } else {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
    Serial.print("an");
    Serial.println(an);
  }
  pixels.show();   // Send the updated pixel colors to the hardware.

  if(schalter_1 == HIGH){
    an = 100;
  }
  if(an > 0){
    an = an - 1;
  }
  if ( ! mfrc522.PICC_IsNewCardPresent()) // Wenn keine Karte in Reichweite ist...
  {
    return; // ...springt das Programm zurück vor die if-Schleife, womit sich die Abfrage wiederholt.
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) // Wenn kein RFID-Sender ausgewählt wurde
  {
    return; // ...springt das Programm zurück vor die if-Schleife, womit sich die Abfrage wiederholt.
  }

  an = 100;

  Serial.print("Diee ID des RFID-TAGS lautet:"); // "Die ID des RFID-TAGS lautet:" wird auf den Serial Monitor geschrieben.
  compl_ID = 0;
  for (byte i = 0; i < mfrc522.uid.size; i++){
    Serial.print(mfrc522.uid.uidByte[i], HEX); // Dann wird die UID ausgelesen, die aus vier einzelnen Blöcken besteht und der Reihe nach an den Serial Monitor gesendet.
    //Die Endung Hex bedeutet, dass die vier Blöcke der UID als HEX-Zahl (also auch mit Buchstaben) ausgegeben wird
    Serial.print(" "); // Der Befehl „Serial.print(" ");“ sorgt dafür, dass zwischen den einzelnen ausgelesenen Blöcken ein Leerzeichen steht.
    in_compl_ID = mfrc522.uid.uidByte[i];
    compl_ID = compl_ID + (in_compl_ID << (8 * i));
  }
//Steuerung Led 1 mit Karte 1 
  if (compl_ID == 23918 && schalter_1 == HIGH){ 
    orte[0] = 0;
  }
  else if (compl_ID == 23918 && schalter_2 == HIGH){ 
    orte[0] = 1;
  }
  else if (compl_ID == 23918 && schalter_3 == HIGH){ 
    orte[0] = 2;
  }
  else if (compl_ID == 23918 && schalter_4 == HIGH){ 
    orte[0] = 3;
  }
  //Steuerung Led 2 mit Karte 2
  if (compl_ID == 28878 && schalter_1 == HIGH){ 
    orte[1] = 0;
  }
  else if (compl_ID == 28878 && schalter_2 == HIGH){ 
    orte[1] = 1;
  }
  else if (compl_ID == 28878 && schalter_3 == HIGH){ 
    orte[1] = 2;
  }
  else if (compl_ID == 28878 && schalter_4 == HIGH){ 
    orte[1] = 3;
  }
  //Steuerung Led 3 mit Chip 3
  if (compl_ID == 20523 && schalter_1 == HIGH){ 
    orte[2] = 0;
  }
  else if (compl_ID == 20523 && schalter_2 == HIGH){ 
    orte[2] = 1;
  }
  else if (compl_ID == 20523 && schalter_3 == HIGH){ 
    orte[2] = 2;
  }
  else if (compl_ID == 20523 && schalter_4 == HIGH){ 
    orte[2] = 3;
  }
   //Steuerung Led 4 mit Chip 4
  if (compl_ID == 28867 && schalter_1 == HIGH){ 
    orte[3] = 0;
  }
  else if (compl_ID == 28867 && schalter_2 == HIGH){ 
    orte[3] = 1;
  }
  else if (compl_ID == 28867 && schalter_3 == HIGH){ 
    orte[3] = 2;
  }
  else if (compl_ID == 28867 && schalter_4 == HIGH){ 
    orte[3] = 3;
  }

  Serial.print(compl_ID);
  Serial.println(); // Mit dieser Zeile wird auf dem Serial Monitor nur ein Zeilenumbruch gemacht.

}
