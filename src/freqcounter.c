#include <stdint.h>
#include <stdio.h>
#ifndef SIMULATION
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#else
#include "icemu.h"
#endif

#include "../common/util.h"
#include "../common/pin.h"
#include "../common/timer.h"
#include "../common/intmath.h"

#define DIGITS 4
#define SAMPLES_PER_SECOND 1
#define PRESCALER 256

#define FREQ256 PinB2
#define OUTCLK PinB0
#define OUTSER PinB1

static volatile uint32_t tick_counter;
static volatile uint32_t last_sample;
static volatile bool refresh_needed;

typedef struct {
    bool haswork;
    PinID clk;
    PinID ser;
    uint8_t digits[DIGITS];
    uint8_t dotpos;
    uint8_t digit_index;
    uint8_t bit_index;
} Seg7SerialOp;

static Seg7SerialOp serialop = {0};

static void serialop_init(PinID clk, PinID ser, uint32_t val)
{
    uint8_t i;

    serialop.haswork = false;
    serialop.clk = clk;
    serialop.ser = ser;

    serialop.dotpos = DIGITS - 1; // 123 --> 0.123
    while ((val > int_pow10(DIGITS)) && (serialop.dotpos > 0)) {
        val /= 10;
        serialop.dotpos--;
    }
    for (i=0; i<DIGITS; i++) {
        serialop.digits[i] = val % 10;
        val /= 10;
    }
    serialop.digit_index = 0;
    serialop.bit_index = 0;
    serialop.haswork = true;

    // Start the serial protocol with an empty clock.
    pinlow(clk);
    _delay_us(1);
    pinhigh(clk);
}

static bool serialop_pushbit()
{
    bool flag;

    if (!serialop.haswork) {
        return false;
    }
    pinlow(serialop.clk);
    _delay_us(1);
    if (serialop.bit_index < 4) {
        flag = serialop.digits[serialop.digit_index] & (1 << serialop.bit_index);
        serialop.bit_index ++;
    } else {
        flag = serialop.dotpos == serialop.digit_index;
        serialop.bit_index = 0;
        serialop.digit_index++;
        if (serialop.digit_index == DIGITS ) {
            serialop.haswork = false;
        }
    }
    pinset(serialop.ser, flag);
    pinhigh(serialop.clk);
    return serialop.haswork;
}

static void reset()
{
    tick_counter = 0;
    last_sample = 0;
    refresh_needed = false;
}

#ifndef SIMULATION
ISR(INT0_vect)
#else
void freqcounter_int0_interrupt()
#endif
{
    tick_counter++;
}

#ifndef SIMULATION
ISR(TIMER0_COMPA_vect)
#else
void freqcounter_timer0_interrupt()
#endif
{
    last_sample = tick_counter;
    tick_counter = 0;
    refresh_needed = true;
}

void freqcounter_setup()
{
#ifndef SIMULATION
    // generate interrupt on rising edge of INT0
    sbi(MCUCR, ISC00);
    sbi(MCUCR, ISC01);
    // enable Pin Change Interrupts
    sbi(GIMSK, INT0);
    sei();
#endif

    pinoutputmode(OUTCLK);
    pinoutputmode(OUTSER);

    reset();

    // Set timer that controls refreshes
    set_timer0_target(1000UL*1000UL/SAMPLES_PER_SECOND);
    set_timer0_mode(TIMER_MODE_INTERRUPT);
}

void freqcounter_loop()
{
    if (!serialop_pushbit()) {
        if (refresh_needed) {
            serialop_init(
                OUTCLK,
                OUTSER,
                last_sample * PRESCALER * SAMPLES_PER_SECOND);
            refresh_needed = false;
        }
    }
}

