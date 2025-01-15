# TSSOP4038 IR-sensors
This custom infrared sensor-board is was inspired by the BohleBots and was improved for our use by adding a USB-Port for flashing and communication. \
In this folder you will find the Schematic, Board Design and the EasyEDA Professional project. \

## How-To flash the controller
In this project I used the CH340N serial programmer because of its low price compared to their higher-end programmers, ease-of-use and the wide compatibility with universally used drivers. \
The only disadvantage of this programmer is the lack of automatically enabling and disabling the boot mode of the ESP32. Because of this, you have to press the BOOT button while powering on the board or press BOOT, press RST, release RST and after that, release BOOT. This sequence enters the boot mode of the ESP32.

## Example program
An example program will soon be located in the software folder.

## HookUp-Guide
A Hook-Up Guide is coming soon. 

## Editing/Ordering the PCB
This project was edited in EasyEDA Pro, a free, online-based EDA. Due to its tight integration with LCSC, a chinese electronics parts shop, and JLCPCB, the parts are already embedded in the project and can be exported for assembly. No manual assembly is needed for the board to function as it should.
