# AMT103 Encoder Interface | SAMD21 CAN-FD Motion Controller

![Version](https://img.shields.io/badge/Version-v1.0-purple)
![License](https://img.shields.io/badge/License-GPLv3-blue)
![MCU](https://img.shields.io/badge/MCU-Atmel__SAMD21E18-orange)
![CAN Protocol](https://img.shields.io/badge/Bus-CAN--FD%20%7C%20ISO%2011898--1-brightgreen)
![Framework](https://img.shields.io/badge/Framework-PlatformIO-orange)
![Interface](https://img.shields.io/badge/Interface-USB%202.0%20%7C%20SWD-lightgrey)

An interrupt-driven hardware interface for Same Sky (formerly CUI Devices) AMT103 quadrature rotary encoders. Designed around an Atmel SAMD21 32-bit ARM Cortex-M0+ MCU and an MCP2518FD CAN-FD controller, this unit processes high-speed incremental feedback and transmits real-time telemetry over an automotive CAN bus.

---

## 📷 PCB CAD Render

![AMT103 Interface PCB Render](/docs/renders/AMT103Interface.PNG?raw=true)

---

## 🛠 Engineering Highlights & System Architecture

* **Automotive-Grade CAN-FD Controller:** Integrates an MCP2518FD controller supporting ISO 11898-1:2015. Features a dedicated 40MHz low-PPM oscillator divided to 20MHz to match microcontroller SPI limits.
* **Interrupt-Driven Quadrature Decoding:** Low-latency C++ firmware captures encoder channels using hardware interrupts, allowing precise high-speed motion tracking without blocking the core execution pipeline.
* **High-Efficiency Power Topology:** Optimized overall board power consumption (~60mW @ 5V), making it suitable for noise-sensitive, battery-powered mobile robotics platforms.
* **Flexible Logic & Power Stage:** Native signal level compatibility across both 3.3V and 5V incremental optical/capacitive quadrature encoders.

---

## 📐 System Technical Specifications

| Parameter | Specification Details |
| :--- | :--- |
| **Microcontroller** | Microchip/Atmel SAMD21E18 (32-bit ARM Cortex-M0+, 48MHz) |
| **CAN Bus Transceiver / Controller** | MCP2518FD (CAN-FD & CAN 2.0B compliant) |
| **System Clocking** | 40MHz Low-PPM Crystal Oscillator (Divided to 20MHz via SPI) |
| **Input Encoder Compatibility** | 3.3V and 5V Incremental Quadrature Encoders (AMT103 Series) |
| **Power Consumption** | ~60mW @ 5V DC |
| **Interfaces & Connectors** | USB 2.0 Type-C, SWD Header, CAN-FD Differential Bus |
| **Manufacturing Deliverables** | Gerber, N.C. Drill, Assembly, Pick-and-Place (PnP), Altium Draftsman |

---

## 🔬 Validation, Testing & Troubleshooting

* **Hardware Bring-Up:** Verified power rails and SPI-to-CAN bridge messaging rates under synthetic bus loads using oscilloscope probing and CAN analyzer tools.
* **SERCOM Arbitration Recovery:** Resolved SAM-BA bootloader execution crashes caused by simultaneous USB and SERCOM bus access during firmware flash operations.
* **Handling Hardware Bootloader:** Force manual bootloader mode prior to binary upload by executing a physical double-tap sequence on the hardware reset pad.

---

## 💻 Firmware Architecture & Flashing

The firmware utilizes a custom PlatformIO board variant forked from the `Adafruit Arduino SAMD Core` to map the custom PCB pin configuration correctly.

```bash
# Clone the repository
git clone https://github.com/DiamondFire11/AMT103-Encoder-Interface.git
cd AMT103-Encoder-Interface

# Build firmware environment with PlatformIO
pio run -e samd21e18_amt103
```

## ⚡ Flashing via SWD & Hardware Debugging
1. Connect an Atmel-ICE or SWD-compatible programmer to the target SWD header pads.
2. Flash the board configuration using PlatformIO or Atmel Studio.
3. **Recovery Mode**: If USB SERCOM arbitration triggers a bus fault during firmware execution, double-tap the physical reset pad to force hardware bootloader mode.
--- 

## 📄 License & Hardware Manufacturing Files
* **Production Files**: Production Gerber (.gbr), N.C. Drill (.drl), Solder Paste Stencils (.gtp/.gbp), and Altium Draftsman assembly drawings are located in the /hardware directory
* **License**: Distributed under [GPLv3 License](https://github.com/DiamondFire11/Tartarus-Joystick-Mod/blob/main/LICENSE). 
