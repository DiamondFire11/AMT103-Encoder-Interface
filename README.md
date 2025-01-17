# Introducing the AMT103 Encoder Interface

The AMT103 Encoder Interface as the name implies interfaces with a Same Sky AMT103 encoder (formerly CUI Devices), processing its quadrature signals to track position via interrupt-driven incremental counts. It leverages real-time signal decoding for precise motion tracking and communicates the extracted data to the robot system via CAN-FD, ensuring fast and reliable data transfer. Ideal for robotics and automation applications requiring high-speed encoder feedback with interrupt-based efficiency.

![pcb_render](/docs/renders/AMT103Interface.PNG?raw=true)

## Hardware Features

- Atmel SAMD21: The same microcontroller used on the Arduino Zero and many Adafruit dev-boards. Allows for ease of software modification.
- MCP2518FD Mixed CAN-FD and CAN2.0B Controller
  - Conforms to ISO 11898-1:2015 and ISO 26262 Functional Safety for automotive grade CAN-FD compliance.
  - On-board low PPM 40MHz CAN clock (divided to 20MHz to comply with SPI max clock on uC).
- Wide compatability: Supports wide range of 5V and 3.3V rotary encoders.
- USB 2.0 Type-C connector: Given the prevalence of USB Type-C the board comes equipped to take advantage of spare cables.
- Very low power: The device consumes around 60mW at 5V. Meaning that the robotic platform's battery life will not be significantly impacted.
- And much more...

## Getting Started

This mod requires some hands-on assembly. We'll provide the necessary build files, but you'll need to order and assemble the PCB yourself using the included GERBER, schematics, and Draftsman files.

The project utilizes an Atmel SAMD21E18 microcontroller (MCU) to interface with the encoder. To program the MCU with the bootloader, you'll need an SWD programmer. The Adafruit Trinket M0 bootloader is recommended for this purpose, allowing you to easily setup the PCB as a custom Arduino board.

**We strongly recommend utilizing solder paste stencils (available as .GTP and .GBP GERBER files) for this project.** Soldering the small SMD components can be challenging for beginners. Recommended stencil manufacturers can be found in the [Resources](#resources) section.

## Uploading Custom Firmware

For uploading custom code, we recommend using an IDE with PlatformIO installed. The standard Arduino IDE won't work due to the PCB's unique pin layout. Luckily, PlatformIO board and variant files are included in the [build](/build/) directory within the project repository for your convenience. The board core has been forked from the [Adafruit Arduino SAMD Core](https://github.com/adafruit/ArduinoCore-samd).

## A Note on Uploading

In certain cases, the SAM-BA programming software may fail to write all firmware blocks to the MCU. This issue occurs when the SERCOM and programming interface attempt to access the USB controller simultaneously, causing the MCU to crash. To prevent this, users should enter bootloader mode by double-clicking the reset button before uploading code.

## Important Reminders

- Please refrain from modifying the PlatformIO variant files, as this can prevent the code from compiling correctly.
- This project doesn't support the standard Arduino IDE. If you seek support, we'll kindly recommend switching to PlatformIO.

## Join the Community!

We welcome contributions to this project! If you have significant hardware modifications in mind, please create an issue first to discuss the proposed changes. Additionally, remember to update any relevant software tests along with your contributions.

## Resources
#### Hardware
[Board Manufacturing - PCBWay](https://www.pcbway.com)

[Components - Mouser](https://www.mouser.com)

[OSH Stencils](https://www.oshstencils.com)

#### Software and Programming
[SWD Programmer - Atmel ICE](https://www.mouser.com/ProductDetail/Microchip-Technology/ATATMEL-ICE?qs=KLFHFgXTQiDAUrt43H15kQ%3D%3D)

[PlatformIO](https://platformio.org)

## License

This project is licensed under the GPLv3 ([GPL](https://choosealicense.com/licenses/gpl-3.0/)).
