from functools import partial
from collections import namedtuple

from icemu.mcu import ATtiny
from icemu.pin import Pin
from icemu.seg7 import combine_repr
from icemu.ui import SimulationWithUI

from seg7_circuit import Circuit as Seg7Circuit

class Circuit(SimulationWithUI):
    def __init__(self):
        super().__init__()
        self.mcu = self.add_chip(ATtiny())
        self.mcu.run_program('freqcounter')
        serial_input = namedtuple('SerialInput', 'ser clk')(self.mcu.pin_B1, self.mcu.pin_B2)
        self.seg7 = Seg7Circuit(max_digits=4, serial_input=serial_input, with_ui=False)
        for chip in self.seg7._chips:
            self.add_chip(chip)

        self.input_value = self.add_chip(Pin('INPUT', output=True, oscillating_freq=500))
        self.mcu.pin_B0.wire_to(self.input_value)
        self.mcu.enable_interrupt_on_pin(self.mcu.pin_B0, rising=True, falling=True)
        self._setup_ui()

    def _setup_ui(self):
        uiscreen = self.uiscreen
        uiscreen.add_element(
            "LED Matrix output:",
            partial(combine_repr, *self.seg7.segs[::-1])
        )
        uiscreen.add_element(
            "MCU:",
            self.mcu.asciiart
        )
        uiscreen.refresh()

def main():
    circuit = Circuit()
    circuit.run()

if __name__ == '__main__':
    main()
