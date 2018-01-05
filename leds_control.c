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

#include "ptl-leds-shelf.h"


void update_leds(void) {

    //FastLED.show();
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
