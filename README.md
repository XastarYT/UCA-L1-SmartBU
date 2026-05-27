# Smart-BU : Système de comptage directionnel LoRaWAN

Ce projet a été réalisé dans le cadre du module **"Communication Sans Fil"** (Licence 1 - Université Côte d'Azur).

## 📝 Présentation

Le Smart-BU est un dispositif IoT conçu pour surveiller en temps réel l'occupation de la bibliothèque universitaire. En utilisant deux capteurs infrarouges (PIR) et le protocole de communication longue portée LoRaWAN, le système est capable de déterminer le sens de passage (Entrée/Sortie) et de maintenir un compteur précis.

Les données sont ensuite transmises via **The Things Network (TTN)** pour être visualisées sur un tableau de bord en ligne (**Tago.io**).

## 🛠️ Matériel Requis

* 1x **Carte UCA** (Microcontrôleur ATmega328PB avec puce LoRa 868 MHz intégrée).
* 2x **Capteurs PIR** (Détecteurs de mouvement infrarouge).
* 1x Câble micro-USB (pour le téléversement et l'alimentation).

## ⚙️ Prérequis Logiciels et Dépendances

Pour compiler et téléverser le code, l'IDE Arduino doit être correctement configuré avec les éléments suivants :

1.  **Gestionnaire de cartes :** Ajouter l'URL `https://rfthings.com.vn/wp-content/uploads/package_rfthings-avr_index.json` dans les préférences, puis installer **RFThings AVR Boards**. Sélectionner la carte "3.9 and newer (ATMega328PB)".
2.  **Bibliothèques requises :** Le projet nécessite la bibliothèque LoRa configurée spécifiquement pour la carte UCA.
    * Télécharger l'archive complète du dépôt du professeur : [GitHub - FabienFerrero/UCA21](https://github.com/FabienFerrero/UCA21)
    * Copier le dossier `arduino-lmic` situé dans `UCA21/Libraries/` vers votre répertoire local `Documents/Arduino/libraries/`.

## 🚀 Installation et Déploiement

### 1. Configuration matérielle
* Capteur Gauche (Extérieur) branché sur la broche numérique **D2**.
* Capteur Droit (Intérieur) branché sur la broche numérique **D3**.

### 2. Configuration The Things Network (TTN)
1.  Créer une application sur TTN.
2.  Ajouter un appareil (End Device) en utilisant la méthode **Activation By Personalization (ABP)**.
3.  *Important :* Dans les paramètres avancés (Network Layer), cocher la case **Resets frame counters** pour éviter le blocage des données après un redémarrage de la carte.

### 3. Configuration du code source
Ouvrir le fichier `src/Smart-BU_Compteur.ino` et remplacer les clés de sécurité générées par TTN :
```cpp
static const u4_t DEVADDR = 0x... ;
static const PROGMEM u1_t NWKSKEY[16] = { 0x... };
static const u1_t PROGMEM APPSKEY[16] = { 0x... };
