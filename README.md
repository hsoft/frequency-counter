# Frequency Counter

This project is an embedded project built around an AVR ATtiny45 that counts the frequency at which
its input pin changes its state and displays the result on a [7-Segments display module][seg7] that
is connected to our module through a USB cable.

The display has 4 digits and allow values up to 50Mhz. The display, for values from 0Hz to 9999kHz
displays its values by taking advantage of the digital dot. For example, `1.234` means 1234Hz, the
value being in kHz. `12.34` means `12.34` kHz, `9999` means 9999 kHz.

Over that, the "MHz" LED indicator lights up to indicate that values are in MHz. That that LED is
lit, `12.34` means 12.34 MHz.

One of the goals of this project, other than the main one being to have a handy device around, is
to test the precision of ATtiny's oscillator. I plan on using the internal oscillator as my main
timer for my first prototype and see how it measures fixed frequencies that more precise oscillator
generate and see if it's good enough for my purposes. If it's not, then I'll build a second
prototype using an external oscillator for greater precision.

[seg7]: https://github.com/hsoft/seg7-multiplex
