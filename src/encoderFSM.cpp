#include "../include/encoderFSM.h"

uint8_t encoderTick(uint8_t state) {
    state = encoderTransition(state);
    encoderAction(state);
    return state;
}

uint8_t encoderTransition(uint8_t state) {
    switch(state){
        case EncoderStates::ENCODER_INIT:
        case EncoderStates::TRANSMIT:
            state = EncoderStates::READ;
            break;

        case EncoderStates::READ:
            state = EncoderStates::TRANSMIT;
            break;

        default:
            state = EncoderStates::ENCODER_INIT;
    }

    return state;
}

void encoderAction(uint8_t state) {
    switch(state){
        case EncoderStates::ENCODER_INIT:
            Serial.println("AMT103 encoder initialized");
            break;

        case EncoderStates::READ:
            readEncoder();
            break;

        case EncoderStates::TRANSMIT:
            if(isCANGood){
                transmitToCAN();
            }
            break;

        default:
            Serial.println("Error: Encountered unknown state, resetting SM.");
    }
}

void initCAN() {
    /* MCP2518FD Settings -
     * Oscillator: 40MHz
     * Arbitration Rate: 500 kbit/s
     * Data Rate: 2 Mbit/s (500kbit/s * 4)
     */
    ACAN2517FDSettings settings(ACAN2517FDSettings::OSC_40MHz_DIVIDED_BY_2,
                                500UL * 1000UL,
                                DataBitRateFactor::x4);

    settings.mRequestedMode = ACAN2517FDSettings::NormalFD; // Request start in NORMAL FD mode

    const uint32_t canInitErrCode = CAN.begin(settings, [] {CAN.isr(); });
    if (canInitErrCode != 0) {
        Serial.print ("CAN Configuration Error: 0x");
        Serial.println (canInitErrCode , HEX);
    } else {
        isCANGood = true; // CAN is good, print CAN Tx/Rx settings
        outputCANSettings(settings);

        // Setup CAN Frame obj
        canFrame.id = frameID;
        canFrame.len = 4;
    }
}

void readEncoder() {
    encoderPos = encoder.read();
}

bool transmitToCAN() {
    canFrame.data_s32[0] = encoderPos;
    return CAN.tryToSend(canFrame);
}

void outputCANSettings(ACAN2517FDSettings & settings) {
    Serial.println("<--- MCP2518FD Settings --->");

    Serial.print("Operating Mode: ");
    switch(settings.mRequestedMode){
        case ACAN2517FDSettings::NormalFD:
            Serial.println("NormalFD");
            break;
        case ACAN2517FDSettings::Sleep:
            Serial.println("Sleep");
            break;
        case ACAN2517FDSettings::InternalLoopBack:
            Serial.println("InternalLoopBack");
            break;
        case ACAN2517FDSettings::ListenOnly:
            Serial.println("ListenOnly");
            break;
        case ACAN2517FDSettings::Configuration:
            Serial.println("Configuration");
            break;
        case ACAN2517FDSettings::ExternalLoopBack:
            Serial.println("ExternalLoopBack");
            break;
        case ACAN2517FDSettings::Normal20B:
            Serial.println("Normal20B");
            break;
        case ACAN2517FDSettings::RestrictedOperation:
            Serial.println("RestrictedOperation");
            break;
        default:
            Serial.println("Operation mode unknown");
    }

    Serial.print("Oscillator (MHz): ");
    switch(settings.oscillator()) {
        case ACAN2517FDSettings::OSC_4MHz:
            Serial.println("4");
            break;
        case ACAN2517FDSettings::OSC_4MHz_DIVIDED_BY_2:
            Serial.println("2");
            break;
        case ACAN2517FDSettings::OSC_4MHz10xPLL:
            Serial.println("4 * 10");
            break;
        case ACAN2517FDSettings::OSC_4MHz10xPLL_DIVIDED_BY_2:
            Serial.println("2 * 10");
            break;
        case ACAN2517FDSettings::OSC_20MHz:
            Serial.println("20");
            break;
        case ACAN2517FDSettings::OSC_20MHz_DIVIDED_BY_2:
            Serial.println("10");
            break;
        case ACAN2517FDSettings::OSC_40MHz:
            Serial.println("40");
            break;
        case ACAN2517FDSettings::OSC_40MHz_DIVIDED_BY_2:
            Serial.println("20");
            break;
    }

    Serial.print("SYSCLK Frequency (MHz): ");
    Serial.println(settings.sysClock()/1000000.0);

    Serial.print("Bitrate Prescaler: ");
    Serial.println(settings.mBitRatePrescaler);

    Serial.print("Arbitration Rate Is Closed To Desired Rate: ");
    Serial.println(settings.mArbitrationBitRateClosedToDesiredRate ? "Yes" : "No!");

    Serial.print("Distance (PPM): ");
    Serial.println(settings.ppmFromDesiredArbitrationBitRate());

    Serial.print("Consistency: ") ;
    Serial.println(settings.CANBitSettingConsistency() ? "FAIL" : "Ok");

    Serial.println("\n<--  Arbitration Settings  -->");

    Serial.print("Actual Arbitration Rate (kbit/s): ");
    Serial.println(settings.actualArbitrationBitRate()/1000.0);

    Serial.print("Arbitration Phase Segment 1 (Tq): ");
    Serial.println(settings.mArbitrationPhaseSegment1);

    Serial.print("Arbitration Phase Segment 2 (Tq): ");
    Serial.println(settings.mArbitrationPhaseSegment2);

    Serial.print("Arbitration Resynchronization Jump Width: ");
    Serial.println(settings.mArbitrationSJW);

    Serial.print("Arbitration Sample Point: ");
    Serial.print(settings.arbitrationSamplePointFromBitStart()) ; // 81, meaning 81%") ;
    Serial.println("%");

    Serial.println("\n<--  Frame Data Settings  -->");

    Serial.print("Actual Data Bitrate (kbit/s): ");
    Serial.println(settings.actualDataBitRate ()/1000.0);

    Serial.print("Data Phase Segment 1 (Tq): ");
    Serial.println(settings.mDataPhaseSegment1);

    Serial.print("Data Phase Segment 2 (Tq): ");
    Serial.println(settings.mDataPhaseSegment2);

    Serial.print ("Data Resynchronization Jump Width: ");
    Serial.println(settings.mDataSJW);

    Serial.print("Data Sample Point: ");
    Serial.print(settings.dataSamplePointFromBitStart());
    Serial.println("%");

    Serial.println("<--- MCP2518FD Settings --->");
}