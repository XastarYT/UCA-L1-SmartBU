#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>

// ==============================================================================
// CLES TTN (A REMPLACER PAR VOS PROPRES CLES)
// ==============================================================================
static const u4_t DEVADDR = 0x00000000;
static const PROGMEM u1_t NWKSKEY[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const u1_t PROGMEM APPSKEY[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

const lmic_pinmap lmic_pins = {
    .nss = 10,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 8,
    .dio = {6, 6, 6},
};

const int capteurGauche = 2; 
const int capteurDroit = 3;  
int personnesDansBU = 0;
int etapeActuelle = 0;
unsigned long tempsDetection = 0;
const int delaiMax = 5000;

osjob_t sendjob;
const unsigned TX_INTERVAL = 30; 
uint8_t payload[1]; 

void os_getArtEui (u1_t* buf) { }
void os_getDevEui (u1_t* buf) { }
void os_getDevKey (u1_t* buf) { }

void do_send(osjob_t* j){
    if (LMIC.opmode & OP_TXRXPEND) {
        Serial.println("Envoi deja en cours...");
    } else {
        payload[0] = personnesDansBU; 
        LMIC_setTxData2(1, payload, sizeof(payload), 0);
        Serial.print("Envoi vers TTN... Personnes = ");
        Serial.println(personnesDansBU);
    }
}

void onEvent (ev_t ev) {
    if(ev == EV_TXCOMPLETE) {
        Serial.println("OK ! Message recu par l'antenne TTN !");
        os_setTimedCallback(&sendjob, os_getTime()+sec2osticks(TX_INTERVAL), do_send);
    }
}

void setup() {
    Serial.begin(9600);
    delay(2000); 
    pinMode(capteurGauche, INPUT);
    pinMode(capteurDroit, INPUT);

    Serial.println("========================================");
    Serial.println("Demarrage Smart-BU...");
    Serial.flush(); 
    
    os_init();
    LMIC_reset();

    uint8_t appskey[sizeof(APPSKEY)];
    uint8_t nwkskey[sizeof(NWKSKEY)];
    memcpy_P(appskey, APPSKEY, sizeof(APPSKEY));
    memcpy_P(nwkskey, NWKSKEY, sizeof(NWKSKEY));
    LMIC_setSession (0x1, DEVADDR, nwkskey, appskey);

    LMIC_setLinkCheckMode(0);
    LMIC_setDrTxpow(DR_SF7, 14);

    do_send(&sendjob);
}

void loop() {
    os_runloop_once();

    int etatG = digitalRead(capteurGauche);
    int etatD = digitalRead(capteurDroit);

    if (etatG == HIGH && etapeActuelle == 0) {
        etapeActuelle = 1;
        tempsDetection = millis();
        delay(500); 
    }
    if (etatD == HIGH && etapeActuelle == 1) {
        personnesDansBU++;
        Serial.print("+1 Entree ! Total = ");
        Serial.println(personnesDansBU);
        etapeActuelle = 0;
        delay(2000);
    }

    if (etatD == HIGH && etapeActuelle == 0) {
        etapeActuelle = 2;
        tempsDetection = millis();
        delay(500);
    }
    if (etatG == HIGH && etapeActuelle == 2) {
        if (personnesDansBU > 0) personnesDansBU--; 
        Serial.print("-1 Sortie ! Total = ");
        Serial.println(personnesDansBU);
        etapeActuelle = 0;
        delay(2000);
    }

    if (etapeActuelle != 0 && (millis() - tempsDetection > delaiMax)) {
        etapeActuelle = 0;
    }
}
