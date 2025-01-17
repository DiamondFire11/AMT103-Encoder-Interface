#include <Arduino.h>
#include <cmath>

#define ENCODER_USE_INTERRUPTS
#define ENCODER_ID 0x01

// Include Paul Stoffregen's Encoder library and MCP2517FD library
#include "Encoder.h"
#include "ACAN2517FD.h"
#include <SPI.h>

#include "../include/encoderFSM.h"
#include "../include/ledFSM.h"

ACAN2517FD CAN(CAN_CS, SPI, CAN_INT);
CANFDMessage canFrame;
uint8_t frameID = ENCODER_ID;
bool isCANGood = false;

Encoder encoder(ENCODER_A, ENCODER_B);
int32_t encoderPos; // Encoder position

struct Tasks {
    uint8_t state;
    uint32_t period;
    uint32_t elapsedTime;
    uint8_t (*tickFcn) (uint8_t);
} typedef Tasks;

Tasks tasks[2]; // Array storing FSMs

void setup() {
    // Initialize MCU Alive LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    // Wait for Serial to connect - Break and continue boot after 5s
    Serial.begin(115200);
    while (!Serial && millis() < 5000) {
        delay (50);
        digitalWrite (LED_BUILTIN , !digitalRead (LED_BUILTIN));
    }

    SPI.begin();    // Start SPI bus
    initCAN();      // Initialize CAN-FD controller

    tasks[0].state = LEDStates::LED_INIT;
    tasks[0].period = 500;
    tasks[0].elapsedTime = 0;
    tasks[0].tickFcn = &ledTick;

    tasks[1].state = EncoderStates::ENCODER_INIT;
    tasks[1].period = 5;
    tasks[1].elapsedTime = 0;
    tasks[1].tickFcn = &encoderTick;
}

void loop() {
    for (auto & task : tasks) {
        if ((millis() - task.elapsedTime) >= task.period) {
            task.state = task.tickFcn(task.state);
            task.elapsedTime = millis(); // Last time this task was ran
        }
    }
}