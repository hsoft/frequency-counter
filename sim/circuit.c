#include "circuit.h"

void freqcounter_loop();

void freqcounter_circuit_init(
    FreqCounter *circuit, ICePin *outser, ICePin *outclk, ICePin *input)
{
    icemu_ATtiny_init(&circuit->mcu);
    icemu_mcu_set_runloop(&circuit->mcu, freqcounter_loop, 20);
    icemu_SN74F161AN_init(&circuit->cnt1);
    icemu_SN74F161AN_init(&circuit->cnt2);
    icemu_pin_wireto(icemu_chip_getpin(&circuit->mcu, "PB1"), outser);
    icemu_pin_wireto(icemu_chip_getpin(&circuit->mcu, "PB0"), outclk);
    icemu_pin_wireto(icemu_chip_getpin(&circuit->mcu, "PB2"), input);
}
