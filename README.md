# LedBrightnessControl

## Hi everyone
This code was created for learning Arduino Uno system. I made a device that can control brightness of red and blue LEDs.

The whole system based on Arduino Uno, and compile on C++.
This device allow you to control brightness by joystick and see this on the LED scale (G G G G G G R R).
<hr></hr>

For this i used:
1. Arduino Uno
2. LCD-display I2C
3. 10 LEDs (1 blue, 3 red, 6 green)
4. Resistor (220 Om)
5. 8-bit Serial-In Parallel-Out  (SIPO) Shift Register
6. A lot of kabels

<hr></hr>

To run this code you have to include the library `LiquidCrystal_I2C.h`,
after that you can compile your code
(cuz my lcd-display has `I2C` controller).And now you should load the code into board (Arduino) and turn on the device. 

If you haven't components for device building, you can simulate this system operation on this web site. 

Simulation: https://wokwi.com/projects/364017263223760897

There is screenshot of this great device.

![image](https://user-images.githubusercontent.com/127895777/236649486-f7de2811-115e-4394-895a-7f294c6fb664.png)

If you think there are too much kabels, youre wrong, cuz there could be more without the `Shift editor`.
