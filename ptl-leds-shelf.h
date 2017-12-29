/*
 * =====================================================================================
 *
 *       Filename:  ptl-leds-shelf.h
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

#ifndef PTL_LEDS_SHELF_V2_0_PTL_LEDS_SHELF_H
#define PTL_LEDS_SHELF_V2_0_PTL_LEDS_SHELF_H

#include "Arduino.h"


#define NUM_LEDS_PER_STRIP  15
#define NUM_STRIPS          8


#define DATA_PIN_STRIP0     12
#define DATA_PIN_STRIP1     13
#define DATA_PIN_STRIP2     14 
#define DATA_PIN_STRIP3     27
#define DATA_PIN_STRIP4     26
#define DATA_PIN_STRIP5     25
#define DATA_PIN_STRIP6     18
#define DATA_PIN_STRIP7     17


enum {STRIP0, STRIP1, STRIP2, STRIP3, STRIP4, STRIP5, STRIP6, STRIP7};

enum {LED0 = 0, LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10, LED11, LED12, LED13, LED14, LED15};


#define RESETTEENSY(x) (digitalWrite(x, LOW); digitalWrite(x, HIGH))
#define WAKEUPTEENSY(x) (digitalWrite(x, HIGH); digitalWrite(x, LOW))

#define SET_LED       "led"
#define SET_LINE      "line"
#define SET_COLUMN    "column"
#define SET_ALL       "set_all"
#define CLEAR_ALL     "clear_all"


typedef struct ledshelf {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint16_t st0;
    uint16_t st1;
    uint16_t st2;
    uint16_t st3;
    uint16_t st4;
    uint16_t st5;
    uint16_t st6;
    uint16_t st7;

} ledshelf_st;


/* Functions to be exposed to the API */
//int ledControl(String command);

/* Primitives */
int set_led(unsigned long color, unsigned int x, unsigned int y);
int set_line(unsigned long color, unsigned int num);
int set_column(unsigned long color, unsigned int num);
int set_all(unsigned long color);


//String getValue(String data, char separator, int index);


#endif //PTL_LEDS_SHELF_V2_0_PTL_LEDS_SHELF_H
