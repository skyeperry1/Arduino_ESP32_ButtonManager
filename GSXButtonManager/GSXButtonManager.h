#ifndef GSXBUTTONMANAGER_H
#define GSXBUTTONMANAGER_H

#include "Arduino.h"

#include "Button.h"

#define MAX_BUTTONS 10

class GSXButtonManager {
  public:
    // Constructor
    GSXButtonManager();

    void update();
    void intitializeButton(uint8_t button1_pin, int button_id); //Called in setup

    void setShortPressCallback(void (*onShortPress)(), int button_id);
    void setLongPressCallback(void (*onLongPress)(),int button_id);
    void setDoubleClickCallback(void (*onDoubleClick)(),int button_id);

    void setExtaLongPressCallback(void (*onExtraLongPress)(),int button_id);
    void setResetButtonHoldCallback(void (*onResetButtonHold)(),int button_id);
   
  private:

    //Static array to hold button pointers
    static Button* ButtonList[MAX_BUTTONS];
    static int button_index;

};


#endif // GSXBUTTONMANAGER_H