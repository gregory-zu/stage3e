#include <Arduino.h>
#include <VirtualWire.h>
#include "WiiChuck.h"

// Calculer et définir la résistance appropriée pour l'émetteur radio à l'aide de la documentation
// à l'aide de la loi d'ohm.
// U = R * I
// R = U / I
// Trouver l'information d'intensité dans la documentation de l'émetteur radio
// La tension est de 5V.
// Calculer La puissance que la résistance doit dissiper : P = U * I. En 2 étapes:
//    - Calculer l'intensité réelle avec la résistance choisie. U = R(choisie avant) * I
//    - On peut maintenant calculer la puissance dissipée par la résistance : P = U * I



#define VitesseSerie                    115200

#define VitesseDeTransmission 	        2000


/*Il nous faut un pointeur car la fonction vw_send de la librairie virtualwire
l'exige. En C, un tableau est un pointeur*/
uint8_t ordre[1];
uint8_t longueurOrdre = 1;

// définir le protocole de communication


// définir la broche de transmission PIN_EMETTEUR_DATA
const int PIN_EMETTEUR_DATA       = 5;
// définir une valeur de référence pour le joystick du nunchuck après observation
const int VALEUR_JOYSTICK_REF     = 9;


/*
Nunckuck:
GND va sur A2
VCC va sur A3

SDA va sur A4
SCL va sur A5
*/
WiiChuck chuck = WiiChuck();

void setup() {
  Serial.begin(VitesseSerie);
  // initialiser le nunchuck
  chuck.begin();
  // définir la broche de transmission
  // vw_set_tx_pin(?);

  // définir la vitesse de transmission
  vw_setup(VitesseDeTransmission);
  delay(5000);
}


// récupère les valeurs du nunchuck et les convertir en ordre[0] 
// comme définit dans notre protocole.
// Pour ça, j'utilise les propriétés du OU logique : ce symbole '|' en C.
void  ecouteNunchuck()
{
  // réinitialiser l'ordre à 0 pour effacer les anciennes valeurs
	ordre[0] = 0x00;
  // récupérer les valeurs du joystick
  // à l'aide de la librairie WiiChuck
  chuck.update();

  // récuprérer la valeur du joystick en X et la stocker dans une constante valeurGaucheDroite. un entier. 
  // Utiliser la fonction chuck.readJoyX()

  // récuprérer la valeur du joystick en Y et la stocker dans une constante valeurAvantArriere. un entier.
  // Utiliser la fonction chuck.readJoyY()

  // afficher les valeurs du joystick sur le moniteur série

  // Mettre en place la logique pour déterminer l'ordre[0] à envoyer en fonction des valeurs du joystick
  // Utiliser des instructions if et else if ...
  // Mettez vous tous d'ccord pour définir les valeurs à utiliser pour déterminer l'ordre[0]. 
  // Ce sera votre protocole de communication.
}

void loop() 
{
  // ETAPE 1: Récupérer les valeurs du nunchuck
  ecouteNunchuck();
  
  
  // ETAPE 2: Envoyer l'ordre[0] à la voiture
	if (true) // replacer true par une condition qui vérifie si on a un ordre à envoyer
	{
    // Afficher l'ordre[0] sur le moniteur série
		
		//*/
		// je donne l'ordre à transmettre et sa taille en octet.. moi c'est 1, et c'est toujours 1
		// l'exemple de la librairie indique strlen(message), mais c'est appeler une fonction
		// pour rien dans mon cas.
		vw_send((uint8_t *)ordre, 1);
    // attendre la fin de la transmission
		vw_wait_tx();
	}

}
