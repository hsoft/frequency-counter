#include <stdint.h>
#include <stdio.h>
#ifndef SIMULATION
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#else
#include "../common/sim.h"
#endif

#include "../common/pin.h"
#include "../common/timer.h"
#include "../common/intmath.h"

#define MAX_DIGITS 4
#define SAMPLE_DURATION_US 100

#define INPUT PinB0
#define SEG7SER PinB1
#define SEG7CLK PinB2

static volatile uint16_t tick_counter;
static volatile bool refresh_needed;

static void toggleclk(Pin pin)
{
    pinlow(pin);
    _delay_us(1);
    pinhigh(pin);
}

static void senddigit(uint8_t val, bool withdot)
{
    char i;
    bool flag;

    for (i=0; i<4; i++) {
        flag = (val >> i) & 0x1;
        pinset(SEG7SER, flag);
        toggleclk(SEG7CLK);
    }
    pinset(SEG7SER, withdot);
    toggleclk(SEG7CLK);
}

static void sendval(uint32_t val)
{
    char i;

    for (i=0; i<MAX_DIGITS; i++) {
        senddigit(val % 10, false);
        val /= 10;
    }
}

static void reset()
{
    tick_counter = 0;
    refresh_needed = false;
}

#ifndef SIMULATION
ISR(TIMER0_COMPA_vect)
#else
void freqcounter_timer0_interrupt()
#endif
{
    refresh_needed = true;
}

void freqcounter_setup()
{
#ifndef SIMULATION
    sei();
#endif

    pinoutputmode(SEG7CLK);
    pinoutputmode(SEG7SER);

    reset();
    refresh_needed = true;

    // Set timer that controls refreshes
    set_timer0_target(1000*100); // every 100 ms
    set_timer0_mode(TIMER_MODE_INTERRUPT);
}

void freqcounter_loop()
{
    if (refresh_needed) {
        sendval(tick_counter);
        tick_counter++;
        refresh_needed = false;
    }
}
