# Changelog Thingsat PC104
 
## 03 Juin 2024 (Léo CORDIER)
  
- [x] Import du projet kicad ***Thingsat UP4 FM*** 
- [x] Suppression des fichiers inutiles accumulés au cours de l'évolution du projet

## 06 Juin 2024 (Léo CORDIER)
- [x] Ajout d'une librairie de symbole et d'empreinte pour le projet
- [x] Mise en place de plusieurs classes d'équipots
- [x] Changement sur le Pin EN du convertisseur buck (U301), celle ci est maintenant connecté après l'étage de filtrage et de protection de la ligne 12V. Auparavant elle était connectée directement que le 12V d'entrée, une surtension aurait pu endommager le composant qui est critique pour le fonctionnement du circuit
- [x] Revue de la DRC pour corriger les problèmes apparus avec les changements d'empreintes

## 07 Juin 2024 (Léo CORDIER)
- [x] Fin de la correction des erreurs DRC (sauf les erreurs de composants chevauchants dans les lignes RF
- [x] Supression du connecteur Jack d'alimentation (L'alim du 12V se fera par le connecteur PC104)

## 10 Juin 2024 (Léo CORDIER)
- [x] Ajout de l'empreinte connecteur PC104 à la librairie relative au projet "Thingsat PC104"
- [x] Import de la couche ***Edge.cut*** de la carte exemple NanoLab Academy
- [x] Placement du connecteur PC104 et des 4 vias de fixation en prenant les mesure sur la carte exemple
- [x] Suppression du header de debug (on utilisera le connecteur nicomatic qui poura être remplacé par un header 1.27mm pour les modèles d'ingénieurie)
- [x] Suppresion du boot 1

## 9 Juillet 2024 (Léo CORDIER)
- [x] Grossisement de R401 à R408, R201, C203: 0201 ==> 0603
- [x] Grossisement de R301: 0201 ==> 0402
- [x] Switch Reset passé en CMS
- [x] Replacement des différents blocs sur la carte pour obtenir l'antenne en position centrale
- [x] Edition de la schématique pour rendre possible l'alimentation soit par la ligne VBAT OU par la ligne 3.3V régulée.
- [x] Routage des signaux de debug sur le connecteur nicommatic:
	* Flags LCL
	* Tension en sortie des LCL
	* CAN
	* i2c
	* UART
	* JTAG

## 10 Juillet 2024 (Léo CORDIER)
- [x] Ajout de deux diode TVS sur les entrées d'alim (+3.3V régulé et VBAT)
	* PTVS3V3P1UP (+3.3V régulé)
	* PTVS12VP1UP (VBAT)
- [x] Dans la feuille de schématique générale (racine), Regroupement des signaux liées en bus pour améliorer la lisibilité

## 11 Juillet 2024 (Léo CORDIER)
- [x] Ajout du driver CAN ST L9616
- [x] Routage du bus i2c1 slave sur le connecteur PC104
- [x] Assignation des pin PC104
- [x] Début du routage des blocs adjacents a la partie RF

## 12 Juillet 2024 (Léo CORDIER)
- [x] Placements des grands blocs fonctionels terminé
- [x] Définition des plans d'alimentations et début du routage

## 15 Juillet 2024 (Léo CORDIER)
- [x] Progression du routage
- [x] Tous les elements sont routés mais pas vérifié avec la DRC

## 25 Juillet 2024 (Léo CORDIER)
- [x] Retrecissement de l'empreinte D901 0603 ==> 0201
- [x] MAJ des refs R401-R408 dans kicad
- [x] Grossisement C303-C306 0402 ==> 0603
- [x] Grossisement R303 0805 ==> 1210 
- [x] via de fication mis à la bonne taille
- [x] Utilisation de plugin pour quadriller de vias GND
- [x] Correction erreurs DRC

## 30 Juillet 2024 (Léo CORDIER)
- [x] Mise en forme de la sérigraphie

## 31 Juillet 2024 (Léo CORDIER)
- [x] Ajout de légende sur la sérigraphie:
	- * : ne monter que si l'on utilise le Vbat comme alim
	- carré : ne monter que si l'on utilise le 3v3 régulé comme alim
	- *200/500* : sur la partie LCL l'indication de la limitation de courant est annoté en face des résistances 0 Ohm de sélection

## 1 Aout 2024 (Léo CORDIER)
- [x] Ajout sérigraphie back:
	- 	numéro de série
	-  logo CSUG et auteurs
-  [x] Sortie LCL STM32 sur pin 19 du connecteur PC104 H1 (avec res. 0Ohm)
-  [x] Changement empreinte grove
-  [x] Changement des trous de fixations de via en mounting hole

## 23 Aout 2024 (Léo CORDIER)
- [x] Complétion de la doc sur le README
- [x] Correction symbole

## 20 Septembre 2024 (Léo CORDIER)
- [x] décalage des pistes sous les écrous du connecteur Nicommatic

## Changements à faire
### BOM
- [Fait] changement taille composants R401-R408,R301,R201,C203 ==> changer les références

### Amélioration par rapport à Stork 8

* [Fait] Retrecir D901
* [Fait] Mettre un switch CMS pour le reset au lieu du gros bouton traversant
* Changer l'accelera/magneto ==> Complexe si on veut un composant ST
* [Fait] Connecter le PPS au connecteur PC104
* Mettre à jour la pinmap du stm32

### Réunion Nanolab [26 Juin 2024]

* [Fait] Sortir les signaux LCL sur Nicommatic pour faire des test? [Fait]
* [Fait] Alimentation modulaire soit par le bus 3.3V régulé OU VBAT converti avec l'abaisseur de tension DC-DC	
	* Si 3.3V régulé: DC-DC non peuplé et jonction 3.3V régulé ==> bus 3.3V Thingsat par résistance 0 Ohm
	* Si VBAT : DC-DC peuplé + jonction sortie DC-DC ==> bus 3.3V Thingsat par résistance 0 Ohm
* Envisager de mettre un capot sur le convertisseur DC-DC
* Séparer la grosse inductance en deux petites pour limiter la hauteur de la carte?
* [Fait] Placer le connecteur PSMP le plus au centre de la carte (Pour pouvoir envoyer le cable d'antenne vers n'importe quel côté)
* [Fait] Mettre les signaux de debug sur le connecteur Nicomatic
* [Fait]Connecter le STM32 au PC104 avec les bus i2c (stm32 en slave) et CAN
* Sortir un UART du STM32 vers le PC104 avec résistance 0 Ohm

### Autres
* [Fait] Rajouter une/des protections de surtentions, surintensités (diode TVS, Thyristor) sur la ligne d'alim (VBAT ou 3.3V régulé)
* [Fait] Ajouter un Driver CAN
* [Fait] Grossir C303,C306 --> 0805
* [Fait] Grossir R303
* Editer empreinte U405 --> elargir les pads
* [Fait]Placer exactement le connecteur nicomatic
* [Fait]Remettre les trous de fixations (via GND x 4) aux bonnes dimensions
* [Fait] Rajouter une sortie du flag LCL STM32 vers le connecteur PC104 avec res 0Ohm
*  [Fait] vérifier l'empreinte Grove
*  [Fait] Ajouter QR code vers CSUG
*  [Fait] Ajouter un tableau avec 5 cases et écris tested au dessus
*  [Fait] Ajouter du cuivre autour des vias de fixations
*  [Fait] Corriger l'empreinte du shield ou il manque un pad