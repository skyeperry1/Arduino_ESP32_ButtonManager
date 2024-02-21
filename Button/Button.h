/*********************************************
* Tactile Buttons 
* An asynchronous library for managing & detecting your button clicks
* By: Skye Perry 
* Last Updated: 02-12-2024
* Version 1.0
*********************************************/

#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"

class Button {
  public:
    // Constructor
    Button(uint8_t pin, int id);
   
    void init();  // init method must be called in setup()
    void update(); // update method must be called in loop()

    //Static class methods    
    static void setDebounceTimeout(int timeout);
    static void seLongPressDuration(int timeout);
    static void setButtonClickTimeout(int timeout);

    // Setter methods for callback functions
    void setShortPressCallback(void (*onShortPress)());
    void setLongPressCallback(void (*onLongPress)());
    void setDoubleClickCallback(void (*onDoubleClick)());
    void setExtaLongPressCallback(void (*onExtraLongPress)());
    void setResetButtonHoldCallback(void (*onResetButtonHold)());
    
  private:
    //Static class variables
    static int BUTTON_DEBOUNCE_TIMEOUT; 
    static int LONG_PRESS_DURATION; // Time in milliseconds
    static int BUTTON_CLICK_TIMEOUT;

    uint8_t PIN;
    bool pressed;
    unsigned long last_interaction_timestamp;
    unsigned long press_start_time;
    bool long_pressed;
    bool extra_long_pressed;
    bool reset_hold_registered;
    //unsigned long prev_click_time;
    //unsigned long cur_click_time;
    void (*onShortPress)();
    void (*onLongPress)();
    void (*onExtraLongPress)();
    void (*onDoubleClick)();
    void (*onResetButtonHold)();
    
    int id;
    bool lastState;  

    // Internal helper methods for detecting a short press, long press and double click
    void shortPressDetected();
    void longPressDetected();
    void doubleClickDetected();
    void extraLongPressDetected();
    void resetButtonHoldDetected();

    bool wait_for_double_click;
    unsigned long last_double_click_timestamp;
};


#endif // BUTTON_H

