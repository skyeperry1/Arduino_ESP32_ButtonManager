#include "GSXButtonManager.h"


// // Initialize static variable
Button* GSXButtonManager::ButtonList[MAX_BUTTONS] = { nullptr };
int GSXButtonManager::button_index = 0;


GSXButtonManager::GSXButtonManager()
{   

}

void GSXButtonManager::intitializeButton(uint8_t button_pin, int button_id)
{
    if (button_index < MAX_BUTTONS) { 
        //Button new_button(button_pin, button_id);
        ButtonList[button_index] = new Button(button_pin, button_id); // Store the button instance pointer in the array
        ButtonList[button_index]->init(); // Call its init function
        button_index = button_index + 1;
    } 
    else    
    {
        Serial.println("[ButtonManager] [Warn] - addButton(): Unable to add button, array is full");
    }
}


void GSXButtonManager::update() {
    // update here
    for (uint8_t i = 0; i <= button_index; ++i) { // Scan through the array
        //Serial.println(ButtonList[i] != nullptr);
        if (ButtonList[i] != nullptr) { // If a button has been set            
                ButtonList[i]->update(); // Call its update function
        }
    }
}

// Setter methods for callback functions
void GSXButtonManager::setShortPressCallback(void (*function)(), int button_id) {
    int i = button_id - 1; // calculate the index from the id (0 index)
    ButtonList[i]->setShortPressCallback(function);
}

void GSXButtonManager::setLongPressCallback(void (*function)(), int button_id) {
    int i = button_id - 1; // calculate the index from the id (0 index)
    ButtonList[i]->setLongPressCallback(function);
}
  
void GSXButtonManager::setDoubleClickCallback(void (*function)(), int button_id) {
    int i = button_id - 1; // calculate the index from the id (0 index)
    ButtonList[i]->setDoubleClickCallback(function);
}


void GSXButtonManager::setExtaLongPressCallback(void (*function)(), int button_id) {
    int i = button_id - 1; // calculate the index from the id (0 index)
    ButtonList[i]->setExtaLongPressCallback(function);
}

void GSXButtonManager::setResetButtonHoldCallback(void (*function)(), int button_id) {
    int i = button_id - 1; // calculate the index from the id (0 index)
    ButtonList[i]->setResetButtonHoldCallback(function);
}