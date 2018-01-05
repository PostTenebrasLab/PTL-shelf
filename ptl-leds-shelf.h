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


//#define DEBUG

#define NUM_LEDS_PER_STRIP  15
#define NUM_STRIPS          8

#define BUF_SIZE            128

#define DATA_PIN_STRIP0     12
#define DATA_PIN_STRIP1     13
#define DATA_PIN_STRIP2     14 
#define DATA_PIN_STRIP3     27
#define DATA_PIN_STRIP4     26
#define DATA_PIN_STRIP5     25
#define DATA_PIN_STRIP6     18
#define DATA_PIN_STRIP7     17

#define TOPIC_ALL           "shelf/all"
#define TOPIC_LINES         "shelf/lines"
#define TOPIC_COLUMNS       "shelf/columns"
#define TOPIC_MASK          "shelf/mask"
#define TOPIC_STATE         "shelf/state"
#define LEN_MSG_ALL         10
#define LEN_MSG_LINES       10
#define LEN_MSG_COLUMNS     10
#define LEN_MSG_MASK        10

enum {STRIP0 = 0, STRIP1, STRIP2, STRIP3, STRIP4, STRIP5, STRIP6, STRIP7};
enum {LED0 = 0, LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10, LED11, LED12, LED13, LED14, LED15};
typedef enum {WAIT, ALL, LINES, COLUMNS, MASK, STATE} state_t;

typedef struct ledshelf {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint16_t mask_0;
    uint16_t mask_1;
    uint16_t mask_2;
    uint16_t mask_3;
    uint16_t mask_4;
    uint16_t mask_5;
    uint16_t mask_6;
    uint16_t mask_7;

} ledshelf_st;



/*** MQTT's callback function
 *
 * It just set a flag depending on topics whom be
 * processed in main loop
 *
 * @param topic
 * @param payload
 * @param length
 */
void callback(char *topic, byte *payload, unsigned int length);

/*** update LEDs states depending on topic/payload
 *
 * @return 0 if job done
 */
int update(const state_t);

void update_leds(void);
int set_led(unsigned long color, unsigned int x, unsigned int y);
int set_line(unsigned long color, unsigned int num);
int set_column(unsigned long color, unsigned int num);
int set_all(unsigned long color);
int publish_state();


/*** test_leds
 *
 */
void test_leds(void);


#endif //PTL_LEDS_SHELF_V2_0_PTL_LEDS_SHELF_H
