# ATMega32 Microcontroller Drivers

## Overview

This repository contains a collection of drivers and utilities for the ATMega32 microcontroller. These drivers are designed to provide easy-to-use interfaces for various peripherals and features of the ATMega32.

## Features

- Complete GPIO (General Purpose Input/Output) drivers
- Timer modules support
- ADC (Analog-to-Digital Converter) functionality
- UART communication interface
- SPI (Serial Peripheral Interface) communication
- I2C (Inter-Integrated Circuit) communication
- External Interrupts handling
- PWM (Pulse Width Modulation) generation

## Hardware Requirements

- ATMega32 Microcontroller
- Minimum 8MHz crystal oscillator
- Programmer (e.g., USBasp, AVR ISP)
- Power supply (5V)

## Software Requirements

- Atmel Studio 7.0 or higher
- Eclipse
- AVR GCC Compiler
- AVRDUDE for firmware uploading
- Proteus (for simulation)

## Project Structure

```
ATMega32-Drivers/
├── MCAL/           # Microcontroller Abstraction Layer
│   ├── DIO/        # Digital Input/Output
│   ├── ADC/        # Analog-to-Digital Converter
│   ├── TIMER/      # Timer modules
│   ├── UART/       # UART Communication
│   ├── SPI/        # SPI Communication
│   └── I2C/        # I2C Communication
├── HAL/            # Hardware Abstraction Layer
│   ├── LCD/        # LCD Display
│   ├── Keypad/     # Keypad interface
│   └── Sensors/    # Various sensors
├── LIB/            # Libraries
│   ├── BIT_MATH/   # Bit manipulation
│   └── STD_TYPES/  # Standard types
└── APP/            # Application layer
```

## Getting Started

1. Clone this repository
2. Open the project in Atmel Studio
3. Configure your programmer settings
4. Build the project
5. Upload to your ATMega32 microcontroller

## Usage

Each driver comes with example code and documentation. To use a specific driver:

1. Include the required header files
2. Initialize the peripheral
3. Use the provided functions to interact with the hardware

Example:

```c
#include "DIO_interface.h"

int main(void)
{
    // Initialize LED pin as output
    DIO_setPinDirection(PORTA, PIN0, OUTPUT);

    while(1)
    {
        // Toggle LED
        DIO_togglePin(PORTA, PIN0);
        // Delay
        _delay_ms(1000);
    }
}
```

## Documentation

- Detailed documentation for each driver can be found in their respective folders
- Each function is documented with clear parameters and return values
- Example implementations are provided for common use cases

## Contributing

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a new Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details

## Contact

For any queries or support, please open an issue in the repository.
