#include <stdio.h>
#include <unistd.h>
#include "../common/pin.h"
#include "../common/timer.h"
#include "../common/intmath.h"
#include "../src/freqcounter.h"
#include "icemu.h"
#include "circuit.h"
#include "../seg7-multiplex/sim/circuit.h"

void freqcounter_int0_interrupt();
void seg7multiplex_int0_interrupt();
void seg7multiplex_timer0_interrupt();
void seg7multiplex_setup();

static FreqCounter circuit;
static Seg7Multiplex seg7;
static ICePin outser;
static ICePin outclk;
static ICePin input;
static ICeChip *active; // override for setup time

static ICeChip* active_mcu()
{
    if (active != NULL) {
        return active;
    }
    if (icemu_sim_get_elapsing_chip() == &circuit.mcu) {
        return &circuit.mcu;
    } else if (icemu_sim_get_elapsing_chip() == &seg7.mcu) {
        return &seg7.mcu;
    } else {
        return NULL;
    }
}

static ICePin* getpin(PinID pinid)
{
    ICeChip *mcu;

    mcu = active_mcu();
    if (mcu == NULL) {
        // Something is very wrong
        return NULL;
    }
    switch (pinid) {
        case PinB0: return icemu_chip_getpin(mcu, "PB0");
        case PinB1: return icemu_chip_getpin(mcu, "PB1");
        case PinB2: return icemu_chip_getpin(mcu, "PB2");
        case PinB3: return icemu_chip_getpin(mcu, "PB3");
        case PinB4: return icemu_chip_getpin(mcu, "PB4");
        default: return NULL;
    }
}

/* Layer impl */
void pinset(PinID pinid, bool high)
{
    icemu_pin_set(getpin(pinid), high);
}

void pinlow(PinID pinid)
{
    pinset(pinid, false);
}

void pinhigh(PinID pinid)
{
    pinset(pinid, true);
}

bool pinishigh(PinID pinid)
{
    return getpin(pinid)->high;
}

void pinoutputmode(PinID pinid)
{
    getpin(pinid)->output = true;
}

bool set_timer0_target(unsigned long usecs)
{
    ICeChip *mcu;

    mcu = active_mcu();
    if (mcu == &circuit.mcu) {
        icemu_mcu_add_timer(mcu, usecs, freqcounter_timer0_interrupt);
    } else {
        icemu_mcu_add_timer(mcu, usecs, seg7multiplex_timer0_interrupt);
    }
    return true;
}

void set_timer0_mode(TIMER_MODE mode)
{
}

int main(void)
{
    int i;

    icemu_pin_init(&outser, NULL, "OUTSER", true);
    icemu_pin_init(&outclk, NULL, "OUTCLK", true);
    icemu_pin_init(&input, NULL, "INPUT", true);
    freqcounter_circuit_init(&circuit, &outser, &outclk, &input);
    seg7multiplex_circuit_init(&seg7, &outser, &outclk);
    icemu_pin_set_oscillating_freq(&input, 2500);

    active = &circuit.mcu;
    freqcounter_setup();
    active = &seg7.mcu;
    seg7multiplex_setup();
    active = NULL;
    icemu_mcu_add_interrupt(
        &circuit.mcu,
        icemu_chip_getpin(&circuit.mcu, "PB2"),
        ICE_INTERRUPT_ON_RISING,
        freqcounter_int0_interrupt);
    icemu_mcu_add_interrupt(
        &seg7.mcu,
        icemu_chip_getpin(&seg7.mcu, "PB2"),
        ICE_INTERRUPT_ON_RISING,
        seg7multiplex_int0_interrupt);

    icemu_sim_init();
    icemu_ui_add_element("MCU", &circuit.mcu);
    for (i = 0; i < DIGITS; i++) {
        icemu_ui_add_element("", &seg7.segs[DIGITS - i - 1]);
    }
    icemu_sim_run();
    return 0;
}
