// rf95_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing client
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example rf95_server
// Tested with Anarduino MiniWirelessLoRa

#include <SoftwareSerial.h>
#include <RH_RF95.h>

// RXTX for the UART Grove connector of TinyGS 2G4 Board
// Grove Connector should be selected with the jumper
static const int RXPin = 16, TXPin = 17;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

RH_RF95<SoftwareSerial> rf95(ss);

void setup() {
    Serial.begin(115200);
    Serial.println("RF95 client test.");

    delay(5000);

    if (!rf95.init()) {
        Serial.println("init failed");
        while (1);
    }

    // Defaults after init are 867.5MHz, 14dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

    // The default transmitter power is 13dBm, using PA_BOOST.
    // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
    // you can set transmitter powers from 5 to 23 dBm:
    
    rf95.setFrequency(867.5);
    rf95.setModemConfig(rf95.Bw125Cr45Sf128);
    // rf95.setModemConfig(rf95.Bw125Cr45Sf128);
    rf95.setPreambleLength(8U);
    rf95.setTxPower(14, false);
}

void loop() {
    Serial.println("Sending to rf95_server");
    // Send a message to rf95_server
    uint8_t data[] = "Hello World!";
    
    rf95.send(data, sizeof(data));

    rf95.waitPacketSent();

    // Now wait for a reply
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.waitAvailableTimeout(3000)) {
        // Should be a reply message for us now
        if (rf95.recv(buf, &len)) {
            Serial.print("got reply: ");
            Serial.println((char*)buf);
        } else {
            Serial.println("recv failed");
        }
    } else {
        Serial.println("No reply, is rf95_server running?");
    }

    delay(5000);
}
