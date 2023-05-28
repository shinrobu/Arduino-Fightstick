#include "MegaJoy.h"
#include <LiquidCrystal.h>

// Pin definitions

// Direction Pins: A1 up, A2 left, A3 down, A4 right
// Remappable Face Buttons: 10 B/Circle, 9 A/Cross, 8 Y/Triangle, 7 X/Square, 6 RB/R1, 5 RT/R2, 4 LB/L1, 3 LT/L2
// Nonremappable: 22 Start, 23 Select

int BPin = 10; // Grey
int APin = 9; // Blue
int YPin = 8; // White
int XPin = 7; // Purple

int RBPin = 6; // Brown
int RTPin = 5; // Black
int LBPin = 4; // Orange
int LTPin = 3; // Red

// 8 buttons
// 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10
// LT -> LB -> RT -> RB -> X -> Y -> A -> B

// All of these arrays are properties of each button. All of the LCD arrays are for placing the buttons being pressed onto the LCD
// These arrays are ordered in the way we pinned the buttons onto the Arduino Mega
uint8_t buttonArray[8];
uint8_t buttonLCDColumn[8] = {15, 15, 14, 14, 12, 13, 12, 13};
uint8_t buttonLCDRow[8] = {1, 0, 1, 0, 0, 0, 1, 1};
uint8_t buttonLCDWrite[8] = {7, 7, 6, 6, 4, 5, 4, 5};
String buttonLabels[8] = {"LT", "LB", "RT", "RB", "X", "Y", "A", "B"};

// Start and select pins cannot be remapped
const int startPin = 23; // Blue
const int selectPin = 22; // White

// LCD implementation:
LiquidCrystal lcd(45, 43, 39, 37, 35, 33, 29, 31, 27, 25);

byte Button_1_UnFilled[] = {B00000,B00000,B01110,B10001,B10001,B10001,B01110,B00000};
byte Button_2_UnFilled[] = {B01110,B10001,B10001,B10001,B01110,B00000,B00000,B00000};
byte Button_3_UnFilled[] = {B00000,B01110,B10001,B10001,B10001,B01110,B00000,B00000};
byte Button_4_UnFilled[] = {B00000,B00000,B00000,B01110,B10001,B10001,B10001,B01110};

byte Button_1_Filled[] = {B00000,B00000,B01110,B11111,B11111,B11111,B01110,B00000};
byte Button_2_Filled[] = {B01110,B11111,B11111,B11111,B01110,B00000,B00000,B00000};
byte Button_3_Filled[] = {B00000,B01110,B11111,B11111,B11111,B01110,B00000,B00000};
byte Button_4_Filled[] = {B00000,B00000,B00000,B01110,B11111,B11111,B11111,B01110};


void setup(){
  setupPins();
  setupMegaJoy();
  // LCD Setup
  lcd.begin(16, 2); //number of pixel on lcd screen
  lcd.createChar(0, Button_1_UnFilled);
  lcd.createChar(1, Button_2_UnFilled);
  lcd.createChar(2, Button_3_UnFilled);
  lcd.createChar(3, Button_4_UnFilled);
  lcd.createChar(4, Button_1_Filled);
  lcd.createChar(5, Button_2_Filled);
  lcd.createChar(6, Button_3_Filled);
  lcd.createChar(7, Button_4_Filled);
  lcd.clear();
  lcd.print("Welcome");
  delay(2000);
}

void loop(){
  // Always be getting fresh data
  megaJoyControllerData_t controllerData = getControllerData();
  setControllerData(controllerData);

  // LCD
  Controller_Layout(controllerData);
  Button_Polling();
  delay(7);
}

void setupPins(void){
  // Set all the digital pins as inputs
  // with the pull-up enabled, except for the 
  // two serial line pins

  //button pins
  for (int i = 2; i <= 53; i++){
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);
  }

  //direction pins
  pinMode(A1, INPUT_PULLUP);
  digitalWrite(A1, HIGH);
  pinMode(A2, INPUT_PULLUP);
  digitalWrite(A2, HIGH);
  pinMode(A3, INPUT_PULLUP);
  digitalWrite(A3, HIGH);
  pinMode(A4, INPUT_PULLUP);
  digitalWrite(A4, HIGH);
}

megaJoyControllerData_t getControllerData(void){
  
  // Set up a place for our controller data
  //  Use the getBlankDataForController() function, since
  //  just declaring a fresh dataForController_t tends
  //  to get you one filled with junk from other, random
  //  values that were in those memory locations before
  
  megaJoyControllerData_t controllerData = getBlankDataForMegaController();
  
  // Since our buttons are all held high and
  //  pulled low when pressed, we use the "!"
  //  operator to invert the readings from the pins

  //remappable
  controllerData.YOn = !digitalRead(YPin);
  controllerData.BOn = !digitalRead(BPin);
  controllerData.XOn = !digitalRead(XPin);
  controllerData.AOn = !digitalRead(APin);
  
  controllerData.RBOn = !digitalRead(RBPin);
  controllerData.RTOn = !digitalRead(RTPin);
  controllerData.LBOn = !digitalRead(LBPin);
  controllerData.LTOn = !digitalRead(LTPin);

  // Read into the buttonArray as well
  for (int i = 3; i < 11; i++){
    buttonArray[i - 3] = !digitalRead(i);
  }
  
  //non-remappable
  controllerData.startOn = !digitalRead(startPin);
  controllerData.selectOn = !digitalRead(selectPin);

  controllerData.dpadUpOn = !digitalRead(A1);
  controllerData.dpadLeftOn = !digitalRead(A2);
  controllerData.dpadDownOn = !digitalRead(A3);
  controllerData.dpadRightOn = !digitalRead(A4);

  
  // And return the data!
  return controllerData;
}

void Controller_Layout(megaJoyControllerData_t controllerData){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(buttonLabels[4]);
      lcd.setCursor(3, 0);
      lcd.print(buttonLabels[5]);
      lcd.setCursor(6, 0);
      lcd.print(buttonLabels[3]);
      lcd.setCursor(9, 0);
      lcd.print(buttonLabels[1]);
      lcd.setCursor(0, 1);
      lcd.print(buttonLabels[6]);
      lcd.setCursor(3, 1);
      lcd.print(buttonLabels[7]);
      lcd.setCursor(6, 1);
      lcd.print(buttonLabels[2]);
      lcd.setCursor(9, 1);
      lcd.print(buttonLabels[0]);
      for (int i = 4; i <= 7; i++)
      {
        lcd.setCursor(8+i,0);
        lcd.write(byte(4+i));
        lcd.setCursor(8+i,1);
        lcd.write(byte(4+i));
      }
}

void Button_Polling() {
  for(int i = 0; i < 8; i++)
  {
    if(buttonArray[i] == 1)
    {
       lcd.setCursor(buttonLCDColumn[i], buttonLCDRow[i]);
       lcd.write(buttonLCDWrite[i]);
    }
  }
}


  // Function for testing
/*void pinTest(megaJoyControllerData_t controller)
{
  if(controller.dpadDownOn == 1)
  {
    Serial.write("Y Button Pressed");
    delay(100);
  }
}*/
