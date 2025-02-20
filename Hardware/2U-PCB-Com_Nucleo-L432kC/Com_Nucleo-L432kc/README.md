# **Carte Thingsat @ INISAT 📡 🚀 : OBC + Communication avec Nucleo L432KC + Gateway RAK5146**

La carte [Thingsat](https://gricad-gitlab.univ-grenoble-alpes.fr/thingsat/public/-/blob/master/README.md?ref_type=heads) @ INISAT a pour but de fonctionner comme un OBC qui peut se relier à l'environnement INISAT grace au header standardisé. 

Cette carte peut accueillir un module MikroBus, trois modules Grove et une gateway LoRa RAK156 (+ GNSS).

Le firmware sur RIOT OS est disponible [ici](../../Software/riot).

Dotée du module gateway LoRa RAK156, elle peut également être utilisée comme la carte [Thingsat](https://gricad-gitlab.univ-grenoble-alpes.fr/thingsat/public/-/blob/master/README.md?ref_type=heads) @ INISAT.

La carte peut être montée en deux versions:

**Carte avec 1 connecteur mini-PCI-Express (pour accueillir un concentrateur LoRa) et 1 support Mikrobus**

![Carte Com Nucleo RAK](images/Com_Nucleo-L432kc_rak.png)

**Carte avec 3 connecteurs Grove et 1 support Mikrobus**

![Carte Com Nucleo Grove](images/Com_Nucleo-L432kc_grove.png)

## Description de la carte
La carte est equipée de:

 - Un emplacement pour carte **Nucleo-32** (ou arduino nano)
 - Un emplacement **MikroBus**
 - Un connecteur **mini-PCI-Express** OU 3 connecteurs **Grove** I2C (en fonction de la version de la carte)
 - Un connecteur **Inisat** (pour se raccorder aux autres cartes de l'ecosystème Inisat)
 - Un **transceiver CAN** ([L9616](https://www.st.com/en/automotive-analog-and-power/l9616.html) - STMicroelectronics)
 - Un **capteur de température** I2C ([MCP9808](https://www.microchip.com/en-us/product/mcp9808#document-table) - Microchip)

## Nucleo 32 (L432KC)
![pinout nucleo](images/pinout_nucleo.png)

## Emplacement MikroBus
![pinout Mikrobus](images/pinout_mikrobus.png)

## mini PCI Express

![pinout PCI](images/pinout_pci.png)

## Jumpers de selection des signaux
Les signaux marqués d'une étoile sur les diagrammes sont partagées entre plusieurs empreintes.
Pour pouvoir utiliser ces signaux il faut donc les "router" vers l'emplacement dont on veut se servir en plaçant correctement les jumpers en bas à droite de la carte.

![Selection jumpers](images/jumpers.png)

- PWM1 : 
	- position haute: `PWM Mikrobus` 		(pin 8 de l'empreinte Mikrobus)
	- position basse: `PWM Inisat` 		(pin 6 du connecteur Inisat)
	
- INT :
	- position haute: `INT Mikrobus` 		(pin 7 de l'empreinte Mikrobus)
	- position basse: `PPS Lora core` 	(pin 19 du connecteur mini PCI Express)
	
- UART (Rx et Tx) :
	- position haute: `UART Mikrobus` 	(pin 5 et 6 de l'empreinte Mikrobus)
	- position basse: `UART GPS Lora core` (pin 31 et 33 du connecteur mini PCI Express)

	
## Transceiver CAN
Le transceiver CAN peut être configuré pour opérations à hautes vitesses (> 250KBaud/s) ou à basse vitesse (< 250KBaud/s).
Pour positionner le transceiver en mode haute vitesse, il faut placer un jumper sur le connecteur `JP2`.

![](images/High_speed_CAN.png)

## Capteur de temperature
L'adresse i2c du capteur de température est définie comme suit : `0b 0 0 1 1 A2 A1 A0`
les bits de poids faibles A2,A1 et A0 sont définis en plaçant des résistances 0 Ohms (_il ne faut donc placer qu'une seule résistance pour chaque bit_): 
 

![](images/selection_adresse.png)


## Modularité de la carte
Les composants entourés d'un rectangle en pointillé ne doivent pas necessairement être montées. Cela dépend de l'usage de la carte. Voici les composants concernés:

* Alimentation Nucleo
	* `R7`: alimentation de la nucleo en 5V (_nécessaire si la carte Inisat est utilisé seule **ET** que l'on a besoin d'utiliser le 5V pour le Mikrobus_)
	* `R6`: alimentation de la nucleo en 3.3V (_nécessaire si la carte Inisat est utilisé seule_)
* Alimentation Transceiver CAN
	* `R9`: alimentation L9616 en 5V
	* `R8`: alimentation L9616 en 3.3V (_par défaut_)
* Selection adresse i2c capteur de temperature (`R10`-`R15`)
	* [voir ci-dessus](#capteur-de-temperature)


# Contributeurs

* Léo CORDIER (Design PCB + montage)
* Vincent Grennerat (Design PCB)
* Didier Donsez (firmware de test)
