/*********************************************
* Tactile Buttons 
* An asynchronous library for managing & detecting your button clicks
* By: Skye Perry 
* Last Updated: 02-12-2024
* Version 1.0
*********************************************/
#include "Button.h"


// // Constructor
Button::Button(uint8_t pin, int id) : 
    PIN(pin), 
    onShortPress(NULL), 
    onLongPress(NULL),
    onDoubleClick(NULL), 
    onExtraLongPress(NULL), 
    onResetButtonHold(NULL), 
    pressed(false), 
    last_interaction_timestamp(0), 
    last_double_click_timestamp(0),
    press_start_time(0),
    //prev_click_time(0),
   // cur_click_time(0), 
    reset_hold_registered(false),
    long_pressed(false),
    wait_for_double_click(false),
    id(id)
{
    //Constructor body
}

// initialize static variables
int Button::BUTTON_DEBOUNCE_TIMEOUT = 150; // 50 milliseconds
int Button::LONG_PRESS_DURATION = 2000; // 1 second
int Button::BUTTON_CLICK_TIMEOUT = 50; // half a second

void Button::setDebounceTimeout(int timeout){
    Button::BUTTON_DEBOUNCE_TIMEOUT = timeout;
}

void Button::seLongPressDuration(int timeout){
    Button::LONG_PRESS_DURATION = timeout;
}

void Button::setButtonClickTimeout(int timeout){
    Button::BUTTON_CLICK_TIMEOUT = timeout;
}

//Simple working for short & Long Press
// void Button::update(){
//     unsigned long time_now = millis();
//     bool button_state = digitalRead(PIN);
//     if (button_state == LOW) { // Button was released
//         if (time_now - last_interaction_timestamp > BUTTON_CLICK_TIMEOUT && lastState ) {
//             if (time_now - press_start_time > LONG_PRESS_DURATION) {
//                 long_pressed = true;
//                 longPressDetected();
//             } else {
//                 pressed = true;
//                 shortPressDetected();
//             }
//             last_interaction_timestamp = time_now;
//             lastState = false;
//         }
//     } 
//     else if(button_state == HIGH){ // Button was pressed
//         if (time_now - last_interaction_timestamp > BUTTON_DEBOUNCE_TIMEOUT && !lastState) {
//             press_start_time = time_now;
//             last_interaction_timestamp = time_now;
//             lastState = true;
//         }
//     }
// }

void Button::update(){
  unsigned long time_now = millis();
  bool button_state = digitalRead(PIN);
  
  const unsigned long DOUBLE_CLICK_TIMEOUT = 250;
  const unsigned long EXTRA_LONG_PRESS_DURATION = 20000;
    const unsigned long RESET_BUTTON_HOLD_DURATION = 20000;
    
  if (button_state == LOW) { // Button was released
    if (time_now - last_interaction_timestamp > BUTTON_CLICK_TIMEOUT && lastState ) {
      if (time_now - press_start_time > LONG_PRESS_DURATION) {
          if (time_now - press_start_time < EXTRA_LONG_PRESS_DURATION) {
              long_pressed = true;
              longPressDetected();
          }
          else {
              //extra_long_pressed = true;
              extraLongPressDetected();
          }
      } 
      else if(wait_for_double_click){
          //double_clicked = true;
          doubleClickDetected();
          wait_for_double_click = false;
      }
      else {
          pressed = true;
          shortPressDetected();
          wait_for_double_click = true;
          last_double_click_timestamp = time_now;
      }
      last_interaction_timestamp = time_now;
      lastState = false;
      reset_hold_registered = false; // reset on when button is released
    }
  } 
  else if(button_state == HIGH){ // Button was/is pressed
    
    if(lastState && !reset_hold_registered){ // Button is being Held
        if (time_now - press_start_time > RESET_BUTTON_HOLD_DURATION) {
            //Serial.println("[BUTTONS] [INFO] LONG HOLD DETECTED");
            reset_hold_registered = true;
            resetButtonHoldDetected();
        }
    }

    if (time_now - last_interaction_timestamp > BUTTON_DEBOUNCE_TIMEOUT && !lastState) {
      press_start_time = time_now;
      last_interaction_timestamp = time_now;
      lastState = true;
    } 
  } 
  
  if(wait_for_double_click && (time_now - last_double_click_timestamp > DOUBLE_CLICK_TIMEOUT) ) {
    wait_for_double_click = false;
  }
}

// Initialization method 
void Button::init() {
    pinMode(PIN, INPUT);
}

// Helper method for when short press is detected
void Button::shortPressDetected() {
    if(onShortPress != NULL) {
        onShortPress();  // Call the short press handler
    }
    pressed = false;
}

// Helper method for when long press is detected
void Button::longPressDetected() {

    if(onLongPress != NULL) {
        onLongPress();  // Call the long press handler
    }
    long_pressed = false;
}

// Helper method for when long press is detected
void Button::extraLongPressDetected() {
    if(onExtraLongPress != NULL) {
        onExtraLongPress();  // Call the long press handler
    }
    extra_long_pressed = false;
}



// Helper method for when double click is detected
void Button::doubleClickDetected() {
    if(onDoubleClick != NULL) {
        onDoubleClick();  // Call the double click handler
    }
}

void Button::resetButtonHoldDetected() {
    if(onResetButtonHold != NULL) {
        onResetButtonHold();  // Call the double click handler
    }
}


// Setter methods for callback functions
void Button::setShortPressCallback(void (*function)()) {
    onShortPress = function;
}

void Button::setLongPressCallback(void (*function)()) {
    onLongPress = function;
}

void Button::setDoubleClickCallback(void (*function)()) {
    onDoubleClick = function;
}

void Button::setExtaLongPressCallback(void (*function)()) {
    onExtraLongPress = function;
}

void Button::setResetButtonHoldCallback(void (*function)()) {
    onResetButtonHold = function;
}