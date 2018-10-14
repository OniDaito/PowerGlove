* Nintendo Powerglove Project

This is a set of Arduino and Teensy based projects for the Nintendo Powerglove. The goal is to create a USB to DB9 connector which converts the NES Controller protocol into a USB device you can use with any PC. To do this I've used a [Teensy](https://www.pjrc.com/teensy/teensyLC.html) board but if you want to use something else Arduino based you can. 

A excellent Powerglove FAQ can be found at [http://mellottsvrpage.com/glove.htm](http://mellottsvrpage.com/glove.htm). The [Wikipedia page on the powerglove](https://en.wikipedia.org/wiki/Power_Glove) is also useful with some handy citations.

The circuit is quite simple. Simply take wire up the corresponding pins from the DB9 connector to the pins on the Teensy. No other components are needed.

Looking at the Powerglove DB9 connector (female end) we have the following pins:

    1 - x
    2 - GND
    3 - x
    4 - x
    5 - +5V
    6 - GND
    7 - LATCH
    8 - CLOCK
    9 - DATA


I used a DB9 cable I had lying around. The colours are mapped thusly:

    1 - black
    2 - brown
    3 - red
    4 - orange
    5 - yellow
    6 - green
    7 - blue
    8 - Purple
    9 - grey


The NES controller protocol is [documented here](https://tresi.github.io/nes/). There is some nice Arduino code I copied and modified [at all about circuits](https://www.allaboutcircuits.com/projects/nes-controller-interface-with-an-arduino-uno/).

The mappings for the controller look like this:

    gnd   |o \   
    clock |o o| power +5v
    latch |o o| DSC0 (not often used - not wired in the powerglove)
    data  |o o| DSC1 (not often used - not wired in the powerglove)


The writeup of his project can be found at [https://benjamin.computer](https://benjamin.computer).