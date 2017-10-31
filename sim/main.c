#include <stdio.h>
#include <unistd.h>
#include "../src/freqcounter.h"
#include "icemu/capi/icemu.h"
#include "icemu/capi/avr/attiny.h"

int main(void)
{
    freqcounter_setup();

    while (1) {
        if (icemu_check_timer(ICEMU_TIMER0)) {
            freqcounter_timer0_interrupt();
        }
        freqcounter_loop();
        icemu_process_messages();
    }
}
