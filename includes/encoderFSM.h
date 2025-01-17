#pragma once

#include "ACAN2517FD.h"
#include "Encoder.h"

enum EncoderStates{ENCODER_INIT, READ, TRANSMIT};

extern Encoder encoder;
extern int32_t encoderPos;

extern bool isCANGood;
extern ACAN2517FD CAN;
extern CANFDMessage canFrame;
extern uint8_t frameID;

uint8_t encoderTick(uint8_t);
uint8_t encoderTransition(uint8_t);
void encoderAction(uint8_t);

void initCAN();
void outputCANSettings(ACAN2517FDSettings &);

void readEncoder();
bool transmitToCAN();