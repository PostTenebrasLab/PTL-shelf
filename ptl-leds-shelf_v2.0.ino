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

#define FASTLED_ALLOW_INTERRUPTS 0

#include <PubSubClient.h>

#include "ptl-leds-shelf.h"
#include "secret.h"

// Define the array of leds
CRGBArray<NUM_LEDS_PER_STRIP> strip0;
CRGBArray<NUM_LEDS_PER_STRIP> strip1;
CRGBArray<NUM_LEDS_PER_STRIP> strip2;
CRGBArray<NUM_LEDS_PER_STRIP> strip3;
CRGBArray<NUM_LEDS_PER_STRIP> strip4;
CRGBArray<NUM_LEDS_PER_STRIP> strip5;
CRGBArray<NUM_LEDS_PER_STRIP> strip6;
CRGBArray<NUM_LEDS_PER_STRIP> strip7;

//CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];
CRGBArray<NUM_STRIPS * NUM_LEDS_PER_STRIP> leds;


U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);

WiFiClient wiFiClient;

PubSubClient mqttClient(mqttServer, mqttPort, callback, wiFiClient);

char buffer[BUF_SIZE];
state_t state = WAIT;
long count = 0;


void callback(char *topic, byte *payload, unsigned int length) {

    memcpy(&buffer, payload, length);

    if (strcmp(topic, TOPIC_ALL) == 0 && length == LEN_MSG_ALL) {
        state = ALL;
    }

    if (strcmp(topic, TOPIC_RECTANGLE) == 0 && length == LEN_MSG_RECTANGLE) {
        state = RECTANGLE;
    }

    if (strcmp(topic, TOPIC_MASK) == 0 && length == LEN_MSG_MASK) {
        state = MASK;
    }

    if (strcmp(topic, TOPIC_STATE) == 0) {
        state = STATE;
    }
}


void update_state(const state_t topic, const char *msg) {

    int err;

    switch (topic) {
        case ALL:
            set_all(3);
            break;
        case RECTANGLE:
            set_rectangle(3, 3);
            break;
        case MASK:
            //set_leds();
            break;
        case STATE:
            //publish_state();
            break;
        default:
            state = WAIT;
    }
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

    while (!mqttClient.connected()) {
        Serial.println("Connecting to MQTT...");
        mqttClient.connect("ESP32", mqttUser, mqttPassword);


        if (mqttClient.connect("ESP32Client", mqttUser, mqttPassword)) {

            Serial.println("connected to MQTT");
            Serial.println("Subscribed to ");

            mqttClient.subscribe(TOPIC_ALL);
            Serial.println(TOPIC_ALL);
            mqttClient.subscribe(TOPIC_RECTANGLE);
            Serial.println(TOPIC_RECTANGLE);
            mqttClient.subscribe(TOPIC_MASK);
            Serial.println(TOPIC_MASK);
            mqttClient.subscribe(TOPIC_STATE);
            Serial.println(TOPIC_STATE);

        } else {

            Serial.print("failed with state ");
            Serial.print(mqttClient.state());
            delay(2000);
        }
    }

    FastLED.addLeds<WS2811, DATA_PIN_STRIP0>(leds, 0, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_STRIP1>(leds, NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_STRIP2>(leds, 2 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_STRIP3>(leds, 3 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_STRIP4>(leds, 4 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_STRIP5>(leds, 5 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_STRIP6>(leds, 6 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_STRIP7>(leds, 7 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);

}

void loop() {

    Serial.print("Begin loop : ");
    Serial.println(count);

        mqttClient.loop();

    if (state != WAIT) {
        Serial.print("Callback has been run : ");
        Serial.println(state);
        update_state(state, buffer);
        count = 0;
        state = WAIT;
//        update_leds();
    }

  Serial.print("End loop : ");
  Serial.println(count++);
}

void set_all(unsigned long color) {
    for (int i = 0; i < NUM_LEDS_PER_STRIP * NUM_STRIPS; i++)
        leds[i] = CRGB::Green;

    FastLED.show();
}

void set_rectangle(unsigned long color, unsigned int num) {
//  for(int i = 0; i < NUM_LEDS_PER_STRIP*NUM_STRIPS; i++)
//    leds[i] = CRGB::Black;
    leds.fill_rainbow(255);
    FastLED.show();

}


