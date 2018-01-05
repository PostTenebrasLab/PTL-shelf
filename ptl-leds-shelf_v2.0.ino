/*
 * =====================================================================================
 *
 *       Filename:  ptl-leds-shelf_v2.0.ino
 *
 *    Description:  WS2801 LED's server for PTL (PostTenebrasLab) Shelf
 *
 *        Version:  1.0
 *        Created:  17/12/2017 10:37:58
 *       Revision:  none
 *       Compiler:  gcc-avr
 *
 *         Author:  Sebastien Chassot (sinux), seba.ptl@sinux.net
 *        Company:  Post Tenebras Lab (Geneva's Hackerspace)
 *
 * =====================================================================================
 */

#include <Arduino.h>
#include <U8g2lib.h>

//#include <WiFi.h>
#include <FastLED.h>
#include <PubSubClient.h>

#include "ptl-leds-shelf.h"
#include "secret.h"

// Define the array of leds
//CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];
CRGBArray<NUM_LEDS_PER_STRIP> strip0;
CRGBArray<NUM_LEDS_PER_STRIP> strip1;
CRGBArray<NUM_LEDS_PER_STRIP> strip2;
CRGBArray<NUM_LEDS_PER_STRIP> strip3;
CRGBArray<NUM_LEDS_PER_STRIP> strip4;
CRGBArray<NUM_LEDS_PER_STRIP> strip5;
CRGBArray<NUM_LEDS_PER_STRIP> strip6;
CRGBArray<NUM_LEDS_PER_STRIP> strip7;

CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];


U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);

WiFiClient wiFiClient;

PubSubClient mqttClient(mqttServer, mqttPort, callback, wiFiClient);


void setup() {

    // put your setup code here, to run once:
    u8g2.begin();
    u8g2.enableUTF8Print();        // enable UTF8 support for the Arduino print() function
    u8g2.setFont(u8g2_font_ncenB08_tr);    // choose a suitable font


    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    u8g2.clearBuffer();
    u8g2.drawStr(0, 10, "PTL's leds shelf V2.0");
    u8g2.sendBuffer();

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    mqttClient.setServer(mqttServer, mqttPort);
    mqttClient.connect("ESP32", mqttUser, mqttPassword);

    while (!mqttClient.connected()) {
        Serial.println("Connecting to MQTT...");

        if (mqttClient.connect("ESP32Client", mqttUser, mqttPassword)) {

            Serial.println("connected to MQTT");
            Serial.println("Subscribed to ");

            mqttClient.subscribe(TOPIC_ALL);
            mqttClient.subscribe(TOPIC_RECT);
            mqttClient.subscribe(TOPIC_MASK);
            mqttClient.subscribe(TOPIC_STATE);

        } else {

            Serial.print("failed with state ");
            Serial.print(mqttClient.state());
            delay(2000);
        }
    }

    FastLED.addLeds<WS2811, DATA_PIN_STRIP0>(leds, 0, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_STRIP1>(leds, NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_STRIP2>(leds, 2*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_STRIP3>(leds, 3*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_STRIP4>(leds, 4*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_STRIP5>(leds, 5*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_STRIP6>(leds, 6*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_STRIP7>(leds, 7*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);

//    FastLED.addLeds<WS2811, DATA_PIN_STRIP0, RGB>(strip0, NUM_LEDS_PER_STRIP);
//    FastLED.addLeds<WS2811, DATA_PIN_STRIP1, RGB>(strip1, NUM_LEDS_PER_STRIP);
//    FastLED.addLeds<WS2811, DATA_PIN_STRIP2, RGB>(strip2, NUM_LEDS_PER_STRIP);
//    FastLED.addLeds<WS2811, DATA_PIN_STRIP3, RGB>(strip3, NUM_LEDS_PER_STRIP);
//    FastLED.addLeds<WS2811, DATA_PIN_STRIP4, RGB>(strip4, NUM_LEDS_PER_STRIP);
//    FastLED.addLeds<WS2811, DATA_PIN_STRIP5, RGB>(strip5, NUM_LEDS_PER_STRIP);
//    FastLED.addLeds<WS2811, DATA_PIN_STRIP6, RGB>(strip6, NUM_LEDS_PER_STRIP);
//    FastLED.addLeds<WS2811, DATA_PIN_STRIP7, RGB>(strip7, NUM_LEDS_PER_STRIP);
}

void loop() {

    int e;

    mqttClient.loop();

    e = update_state(state, buffer);
    if (e == 0)
        update_leds();

//    test_leds();

}


