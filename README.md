# Arduino_ESP32_ButtonManager
A simple Arduino/ESP32 library that detects multiple button interaction-types, supports debouncing, multiple buttons and easy-to-implement callbacks. 

# Interactions Supported
* Cick - detected on release, after single press 
* Double Click - detected on release, after button is double clicked
* Long Press - detected on release, after button is pressed and held down for 3s+
* Extra Long Press - detected on release, after button is pressed and held down for 20s+
* Extra Long Hold  - detected after button is pressed and held down for 20s+

# Setup
See example.ino file for implementation and callback registering. 


```
#include "GSXButtonManager.h"
#define BUTTON_1_PIN 39

GSXButtonManager buttons;

void onButton1ShortPressed(){
  Serial.println("Button1 Short Pressed CallBack");
}

void onButton1LongPressed(){
  Serial.println("Button1 Long Pressed CallBack");
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  buttons.intitializeButton(BUTTON_1_PIN,1);


  buttons.setShortPressCallback(onButton1ShortPressed,1);
  buttons.setLongPressCallback(onButton1LongPressed,1);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttons.update();
}

```

# TODO:
* add support for HIGH or LOW button press state. (Currently HIGH = Button press. See update() in button.cpp for implementation or to overide button press read state)
* Cleanup unused variables in button class, cleanup button manager naming convention
* format code, remove Serial references
* Cleanup example files
* Add Get/Set methods for hardcoded button interaction detection time values
* refactor callbacks to be less verbose? (call onInteraction callback with interaction-type passed as arg.)
