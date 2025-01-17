#include "ledFSM.h"

uint8_t ledTick(uint8_t state) {
    state = ledTransition(state);
    ledAction(state);
    return state;
}

uint8_t ledTransition(uint8_t state) {
    switch (state) {
        case LEDStates::LED_INIT:
        case LEDStates::ON:
            state = LEDStates::OFF;
            break;

        case LEDStates::OFF:
            state = LEDStates::ON;
            break;

        default:
            Serial.println("Error: Encountered unknown state, resetting SM.");
            state = LEDStates::LED_INIT;
    }
    return state;
}

void ledAction(uint8_t state) {
    switch (state) {
        case LEDStates::LED_INIT:
        case LEDStates::OFF:
            digitalWrite(LED_BUILTIN, LOW);
            break;

        case LEDStates::ON:
            digitalWrite(LED_BUILTIN, HIGH);
            break;

        default:
            digitalWrite(LED_BUILTIN, LOW);
    }
}