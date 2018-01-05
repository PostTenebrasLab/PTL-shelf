/*
 * =====================================================================================
 *
 *       Filename:  leds_control.c
 *
 *    Description:  WS2801 LED's call for PTL (PostTenebrasLab) Shelf
 *
 *        Version:  1.0
 *        Created:  22/12/2017 11:12:31
 *       Revision:  none
 *       Compiler:  gcc-avr
 *
 *         Author:  Sebastien Chassot (sinux), seba.ptl@sinux.net
 *        Company:  Post Tenebras Lab (Geneva's Hackerspace)
 *
 * =====================================================================================
 */

#include "FastLED.h"
#include "ptl-leds-shelf.h"


char buffer[BUF_SIZE];
state_t state = WAIT;

void callback(char *topic, byte *payload, unsigned int length) {

    state = WAIT;  // default do nothing

    memcpy(&buffer, payload, length);

    if (strcmp(topic,TOPIC_ALL)==0 && length == LEN_MSG_ALL) {
        state = ALL;
    }

    if (strcmp(topic,TOPIC_RECTANGLE)==0 && length == LEN_MSG_LINES) {
        state = RECTANGLE;
    }

    if (strcmp(topic,TOPIC_MASK)==0) {
        state = MASK;
//        goto end_callback;
    }

    if (strcmp(topic,TOPIC_STATE)==0) {
        state = STATE;
//        goto end_callback;
    }


    // Allocate the correct amount of memory for the payload copy
//    byte *p = (byte *) malloc(length);
    // Copy the payload to the new buffer
//    memcpy(p, payload, length);
//    mqttClient.publish("hello/world_exit", "Hello from ESP33");
//    mqttClient.publish("hello/world_exit", p, length);
//    Serial.println("Hello from callback Leds");
    // Free the memory
//    free(p);

//    end_callback :
//        return;

}

int update_state(const state_t topic, const char* msg) {

    int err;

    switch (topic) {
        case ALL:
            err = set_all(3);
            goto done;
        case RECTANGLE:
            err = set_lines();
            goto done;
        case MASK:
            err = set_leds();
            goto done;
        case STATE:
            err = publish_state();
            return 0;
        default:
            state = WAIT;
    }

    done :
        if (err != 0 ) {
//            Serial.println("Unable to process command");
            return -1;
        }

    state = WAIT;
    return 0;
}

void update_leds(void) {

    FastLED.show();
}

void set_rect(int first_corner, int offset ){



    uint8_t x0 = first_corner >> 4;
    uint8_t y0 = first_corner & 0xf;

    uint8_t x1 = x0 + offset >> 4;
    uint8_t y1 = y0 + offset & 0xf;

    for(int j = y0; j < y1; j++){
        for(int i = x0; i < x1; i++){


        }

    }
}
//void test_leds() {
//
//    long ms = millis() % 2000;
//
//    if (ms < 1000) {
//        fill_solid(strip0, NUM_LEDS_PER_STRIP, CRGB::Red);
//        fill_solid(strip1, NUM_LEDS_PER_STRIP, CRGB::Blue);
//        fill_solid(strip2, NUM_LEDS_PER_STRIP, CRGB::Red);
//        fill_solid(strip3, NUM_LEDS_PER_STRIP, CRGB::Blue);
//        fill_solid(strip4, NUM_LEDS_PER_STRIP, CRGB::Red);
//        fill_solid(strip5, NUM_LEDS_PER_STRIP, CRGB::Blue);
//        fill_solid(strip6, NUM_LEDS_PER_STRIP, CRGB::Red);
//        fill_solid(strip7, NUM_LEDS_PER_STRIP, CRGB::Blue);
//
//    } else {
//        fill_solid(strip0, NUM_LEDS_PER_STRIP, CRGB::Blue);
//        fill_solid(strip1, NUM_LEDS_PER_STRIP, CRGB::Red);
//        fill_solid(strip2, NUM_LEDS_PER_STRIP, CRGB::Blue);
//        fill_solid(strip3, NUM_LEDS_PER_STRIP, CRGB::Red);
//        fill_solid(strip4, NUM_LEDS_PER_STRIP, CRGB::Blue);
//        fill_solid(strip5, NUM_LEDS_PER_STRIP, CRGB::Red);
//        fill_solid(strip6, NUM_LEDS_PER_STRIP, CRGB::Blue);
//        fill_solid(strip7, NUM_LEDS_PER_STRIP, CRGB::Red);
//    }
//
//    FastLED.show();
//}
