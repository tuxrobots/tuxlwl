// tuxlwl/software/DRV8262
// Copyright (C) 2024 Gymnasium der Stadt Rahden
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include "Arduino.h"
#include "lowlevel.h"

DRV8262 driver;
void setup() {
    // EN: Create motors. AddMotor takes in 2 arguments, pinA and pinB - the pins connected to the driver.
    //     The software is not limited to 2 channels and can be used to control 3, 4 or however many you want to.
    // DE: Motoren erstellen. AddMotor nimmt 2 Argumente entgegen, pinA und pinB - die mit dem Treiber verbundenen Pins.
    //     Die Software ist nicht auf 2 Kanäle beschränkt und kann zur Steuerung von 3, 4 oder beliebig vielen Kanälen verwendet werden.
    driver.AddMotor(13, 25); // FL
    driver.AddMotor(12, 33); // FR
    driver.AddMotor(2, 19); // RR
    driver.AddMotor(4, 14); // RL


    // EN: The library uses indexes to find motors. In this example that would be:
    //     FL: 0; FR: 1; RR: 2; RL: 3
    //     The first argument to all functions is always that id.

    // DE: Die Bibliothek verwendet Indexes, um Motoren zu finden. In diesem Beispiel wäre das:
    //     FL: 0; FR: 1; RR: 2; RL: 3
    //     Das erste argument in jeder Funktion ist immer diese ID.


    // EN: This shorts out the motor (both pins are set to max power), braking hard.
    // DE: Dadurch wird der Motor kurzgeschlossen (beide Pins sind auf maximale Leistung gesetzt) und stark abgebremst.
    driver.Shortbrake(0);


    // EN: This disables the power to the motor (both pins are set to 0), so that it rolls.
    // DE: Dies schaltet den Strom zum Motor ab (beide Pins werden auf 0 gesetzt), er rollt also.
    driver.Disable(0);


    // EN: This sets the power to the motor (0-255).
    // DE: Hiermit wird die Leistung für den Motor eingestellt (0-255).
    driver.SetPower(0, 150);
    // EN: Adding another argument lets you change the motor direction (0 or 1).
    // DE: Ein weiteres Argument ändert die Drehrichtung des Motors (0 or 1).
    driver.SetPower(0, 150, 1);

    // DE:  WICHTIG: Das ESP kontrolliert PWM nicht mit analogWrite, sondern mit ledcSetup/ledcAttachPin/ledcWrite.
    //      Es nutzt Kanäle, um die PWM Stärke zu setzen. Die Bibliothek interessiert es nicht, ob vorher bereits ein Kanal zugewiesen wurde.
    //      Falls du weitere PWM Kanäle nutzen möchtest, musst du sicherstellen, dass diese nicht überschrieben werden.
    //      Die AddMotor Funktion lässt hat eine Variante mit einem weiteren Argument, mit dem du einen manuelles Wert für die Kanäle einfügen kannst.
    //      Das ESP braucht aber weiterhin zwei Kanäle, also wäre bei manualChannel=9 Kanal-A dann 9 und Kanal-B 10.
    // EN:  IMPORTANT: The ESP does not control PWM with analogWrite, but with ledcSetup/ledcAttachPin/ledcWrite.
    //      It uses channels to set the PWM strength. The library does not care if a channel has already been assigned.
    //      If you want to use additional PWM channels, make sure that these are not overwritten.
    //      The AddMotor function has a third argument variant which you can use to set a manual value for the channels.
    //      The ESP still needs two channels, so when manualChannel=9, channel-A would be 9 and channel-B 10.
    driver.AddMotor(3, 15, 9);
}

void loop() {}
