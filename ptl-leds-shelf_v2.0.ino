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

#include <WiFi.h>

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

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);

WiFiClient wiFiClient;

void callback(char *topic, byte *payload, unsigned int length);

PubSubClient mqttClient(mqttServer, mqttPort, callback, wiFiClient);

void callback(char *topic, byte *payload, unsigned int length) {
    // In order to republish this payload, a copy must be made
    // as the orignal payload buffer will be overwritten whilst
    // constructing the PUBLISH packet.

    // Allocate the correct amount of memory for the payload copy
    byte *p = (byte *) malloc(length);
    // Copy the payload to the new buffer
    memcpy(p, payload, length);
    mqttClient.publish("hello/world_exit", "Hello from ESP33");
    mqttClient.publish("hello/world_exit", p, length);
    Serial.println("Hello from callback Leds");
    // Free the memory
    free(p);
}


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
        } else {

            Serial.print("failed with state ");
            Serial.print(mqttClient.state());
            delay(2000);
        }
    }

    mqttClient.subscribe("hello/world");

    FastLED.addLeds<WS2812B, DATA_PIN_STRIP0, RGB>(strip0, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, DATA_PIN_STRIP1, RGB>(strip1, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, DATA_PIN_STRIP2, RGB>(strip2, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, DATA_PIN_STRIP3, RGB>(strip3, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, DATA_PIN_STRIP4, RGB>(strip4, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, DATA_PIN_STRIP5, RGB>(strip5, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, DATA_PIN_STRIP6, RGB>(strip6, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, DATA_PIN_STRIP7, RGB>(strip7, NUM_LEDS_PER_STRIP);
}

void loop() {


    // put your main code here, to run repeatedly:
    u8g2.clearBuffer();                    // clear the internal memory
    u8g2.drawStr(0, 10, "PTL's leds shelf V2.0");    // write something to the internal memory
    u8g2.sendBuffer();                    // transfer internal memory to the display
//    delay(20);

    renderLeds();
    mqttClient.loop();

}

void renderLeds() {
    long ms = millis() % 2000;

    if (ms < 1000) {
        fill_solid(strip0, NUM_LEDS_PER_STRIP, CRGB::Red);
        fill_solid(strip1, NUM_LEDS_PER_STRIP, CRGB::Blue);
        fill_solid(strip2, NUM_LEDS_PER_STRIP, CRGB::Red);
        fill_solid(strip3, NUM_LEDS_PER_STRIP, CRGB::Blue);
        fill_solid(strip4, NUM_LEDS_PER_STRIP, CRGB::Red);
        fill_solid(strip5, NUM_LEDS_PER_STRIP, CRGB::Blue);
        fill_solid(strip6, NUM_LEDS_PER_STRIP, CRGB::Red);
        fill_solid(strip7, NUM_LEDS_PER_STRIP, CRGB::Blue);

    } else {
        fill_solid(strip0, NUM_LEDS_PER_STRIP, CRGB::Blue);
        fill_solid(strip1, NUM_LEDS_PER_STRIP, CRGB::Red);
        fill_solid(strip2, NUM_LEDS_PER_STRIP, CRGB::Blue);
        fill_solid(strip3, NUM_LEDS_PER_STRIP, CRGB::Red);
        fill_solid(strip4, NUM_LEDS_PER_STRIP, CRGB::Blue);
        fill_solid(strip5, NUM_LEDS_PER_STRIP, CRGB::Red);
        fill_solid(strip6, NUM_LEDS_PER_STRIP, CRGB::Blue);
        fill_solid(strip7, NUM_LEDS_PER_STRIP, CRGB::Red);
    }

    FastLED.show();

//    Serial.println("Fin leds");
}
