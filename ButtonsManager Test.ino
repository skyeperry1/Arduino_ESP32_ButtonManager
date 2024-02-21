
#include "GSXButtonManager.h"
#define BUTTON_1_PIN 39
#define BUTTON_2_PIN 34
#define BUTTON_3_PIN 35


GSXButtonManager buttons;


void onButton1ShortPressed(){
  Serial.println("Button1 Short Pressed CallBack");
}

void onButton1LongPressed(){
  Serial.println("Button1 Long Pressed CallBack");
}

void onButton2ShortPressed(){
  Serial.println("Button2 Short Pressed CallBack");
}

void onButton2LongPressed(){
  Serial.println("Button2 Long Pressed CallBack");
}

void onButton3ShortPressed(){
  Serial.println("Button3 Short Pressed CallBack");
}

void onButton3LongPressed(){
  Serial.println("Button3 Long Pressed CallBack");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

    buttons.intitializeButton(BUTTON_1_PIN,1);
    buttons.intitializeButton(BUTTON_2_PIN,2);
    buttons.intitializeButton(BUTTON_3_PIN,3);


  buttons.setShortPressCallback(onButton1ShortPressed,1);
  buttons.setLongPressCallback(onButton1LongPressed,1);

  buttons.setShortPressCallback(onButton2ShortPressed,2);
  buttons.setLongPressCallback(onButton2LongPressed,2);

  buttons.setShortPressCallback(onButton3ShortPressed,3);
  buttons.setLongPressCallback(onButton3LongPressed,3);

}

void loop() {
  // put your main code here, to run repeatedly:
  buttons.update();

}
