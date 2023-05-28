# Arduino Fightstick (with a TFT LCD!)

## Introduction
This is a class project to create a game controller with an arcade-style button layout, colloquially known as a "fightstick." Created using [Alan Chatham's UnoJoy library](https://github.com/AlanChatham/UnoJoy), and an Arduino Mega 2560 Rev3.

Our fightstick has an LCD screen display (QAPASS 1602A) as well, for an extra feature to practice with. This is used as to display the buttons currently being pressed on the controller. However, we had to implement a 7ms delay to make the LCD screen actually readable. This was the closest value we could compromise with to make the controller as responsive as possible while making the LCD readable. If you would like to create a controller that would be more practical, I highly recommend to not implement this LCD feature. 7ms delay is a significant factor in competitive fighting games.

There won't be any documentation on how we built/wired our actual fightstick itself, but it's not too hard to create the actual stick itself. If you choose to make one yourself, there's a [very nice document](https://docs.google.com/document/d/1pXX7MJQmV33LXYjgjAB6GVdm0zRoAZBUlcWOLHiQAZ8/edit#) provided by [r/fightsticks](https://www.reddit.com/r/fightsticks/) to help you with all of your fightstick questions.

## Parts List:
* Arduino Mega 2560 Rev3
* QAPASS 1602A LCD Screen
* Arcade Joystick (we used a Sanwa JLF 8-way joystick, easily found on Amazon)
* 8x Arcade Buttons (we used 30mm Qanba buttons, also easily found on Amazon)
* An enclosure for the fightstick itself

## Programming Environment & Libraries
This was coded in the 1.8.19 Arduino IDE. Uses [Alan Chatham's UnoJoy library](https://github.com/AlanChatham/UnoJoy) and the LiquidCrystal.h library found in the Arduino IDE's Library Manager.
