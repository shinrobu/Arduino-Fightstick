# Arduino Fightstick
* [Introduction](https://github.com/shinrobu/Arduino-Fightstick#introduction)
* [Parts List](https://github.com/shinrobu/Arduino-Fightstick#parts-list)
* [Programming Environment & Libraries](https://github.com/shinrobu/Arduino-Fightstick/#programming-environment--libraries)
* [Miscellaneous Notes From Development](https://github.com/shinrobu/Arduino-Fightstick/#miscellaneous-notes-from-development)

## Introduction
This is a class project to create a game controller with an arcade-style button layout, colloquially known as a "fightstick." Created using [Alan Chatham's UnoJoy library](https://github.com/AlanChatham/UnoJoy), and an Arduino Mega 2560 Rev3.

Our fightstick has an LCD screen display (QAPASS 1602A) as well, for an extra feature to practice with. This is used as to display the buttons currently being pressed on the controller. However, we had to implement a 7ms delay to make the LCD screen actually readable. This was the closest value we could compromise with to make the controller as responsive as possible while making the LCD readable. 

**If you would like to create a controller that would be more practical, I highly recommend to not implement this LCD feature. 7ms delay is a significant negative factor in playing competitive fighting games.**

There won't be any documentation on how we built/wired our actual fightstick itself, but it's not too hard to create the actual fightstick. If you choose to make one yourself, there's a [very nice document](https://docs.google.com/document/d/1pXX7MJQmV33LXYjgjAB6GVdm0zRoAZBUlcWOLHiQAZ8/edit#) provided by [r/fightsticks](https://www.reddit.com/r/fightsticks/) to help you with all of your fightstick questions.

## Parts List
* Arduino Mega 2560 Rev3
* QAPASS 1602A LCD Screen
* Arcade Joystick (we used a Sanwa JLF 8-way joystick, easily found on Amazon)
* 8x Arcade Buttons (we used 30mm Qanba buttons, also easily found on Amazon)
* An enclosure for the fightstick itself

## Programming Environment & Libraries
This was coded in the 1.8.19 Arduino IDE. Uses [Alan Chatham's UnoJoy library](https://github.com/AlanChatham/UnoJoy) and the LiquidCrystal.h library found in the Arduino IDE's Library Manager.

## Miscellaneous Notes From Development
* It's heavily advised to follow [the UnoJoy README.md Getting Started section](https://github.com/AlanChatham/UnoJoy#readme) when developing and testing your controller.
* It's also recommended to use an Arduino Uno R3 when working with this library. The Arduino Mega documentation is slightly outdated. If still using an Arduino Mega, though, you can still use the `TurnIntoAJoystick.bat` command found in the [UnoJoy folder of this library](https://github.com/AlanChatham/UnoJoy/tree/master/UnoJoy). Worked out for us.
* There are 3 states you work in when developing with this library:
  *  "Regular" Arduino mode, in which you can program the Arduino and upload code to it
  *  DFU mode, which is used to reprogram the communications chip, which will allow us to turn the Arduino into a game controller
  *  Controller mode, which is when the Arduino is solely being used as a controller. **You cannot program the Arduino in this state.**
  *  To go from regular mode to controller mode & vice versa, you **must put the Arduino in DFU mode first.** Follow [this link](https://support.arduino.cc/hc/en-us/articles/4410804625682-Set-a-board-to-DFU-mode) or the above linked UnoJoy README.md for more info on programming an Arduino in DFU mode.

* If you are going to configure [MegaJoy.h](MegaJoy.h), do **NOT** change the order of or delete any of the member variables inside the megaJoyControllerData_t type definition, except for the analog sticks. The library has those data members set up in that order for reasons that we don't know; but messing with those variables & the order of them creates a lot of issues in controller mode. Trust us, we know. Renaming the variables is absolutely fine, though.
