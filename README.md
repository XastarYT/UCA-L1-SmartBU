# Smart-BU : Compteur de présence intelligent

Ce projet est réalisé dans le cadre du module "Communication Sans Fil" (Licence 1 - Université Côte d'Azur).

## Présentation
Le Smart-BU est un dispositif IoT permettant de suivre en temps réel l'occupation de la bibliothèque universitaire. Grâce à deux capteurs infrarouges (PIR) et à la technologie LoRaWAN, il compte les flux d'entrées et de sorties pour informer les étudiants des places disponibles.

## Matériel
* Carte UCA (LoRa 868 MHz)
* 2x Capteurs PIR (Infrarouge)

## Architecture
Le système envoie les données via le réseau **The Things Network (TTN)** vers un tableau de bord **Node-RED**.
