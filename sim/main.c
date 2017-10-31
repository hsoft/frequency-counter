#include <stdio.h>
#include <unistd.h>
#include "../src/freqcounter.h"
#include "icemu/capi/icemu.h"
#include "icemu/capi/avr/attiny.h"

int main(void)
{
    freqcounter_setup();

    while (1) {
        while (icemu_check_interrupt() == ICEMU_INT0) {
            freqcounter_int0_interrupt();
            icemu_end_interrupt();
        }
        if (icemu_check_timer(ICEMU_TIMER0)) {
            freqcounter_timer0_interrupt();
        }
        freqcounter_loop();
        icemu_process_messages();
    }
}
