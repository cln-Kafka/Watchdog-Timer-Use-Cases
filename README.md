# Watchdog Timer Use cases

## Table of Contents
- [Description](#description)
- [Main Components](#main-components)
- [Our Results](#our-results)
- [Reproduce the same results!](#reproduce-the-same-results)
- [Dependency Installation](#dependency-installation)
- [Program Flow: Simplified Version](#program-flow-simplified-version)
- [Toolstack](#toolstack)
- [References](#references)
- [Help](#help)
- [Contribution](#contribution)
- [License](#license)

## Description

## Main Components

### Pin Controller `GPIO`

### LED State Manager `LEDMgr`

### Watchdog Manager `WDGM`

### Watchdog Driver `WDGDrv`

## Our Results

## Reproduce the same results!

## Dependency Installation

### STM32F401xE

### AVR ATmega328p

1. Install the AVR toolchain from [here](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio/gcc-compilers#:~:text=Toolchain%206.3.1%20Source-,Downloads,-Downloads). Note that you should select AVR 8-Bit Toolchain depending on the operating system you are using.
2. Extract the downloaded zip folder to any preferable location.
3. Install the AVR plugin to Eclipse by following these steps:
   - From the `Help` menu, open `Eclipse Marketplace`.
   - Search for and install `AVR Eclipse Plugin`.
4. Before creating a project, remember to add the AVR paths to the system by following these steps.
   - From the `Window` menu, open `Preferences`.
   - From the right sidebar, open `AVR` then `Paths`.
   - Add the `AVR GCC` path by clicking the "Edit" button, changing the source to "Custom," and setting the current value to the `bin` folder of the toolchain you downloaded.
   - Add the `AVR Header Files` by making the same steps, but the current value will be set to the `include` folder nested in the `avr` folder of the toolchain.
   - Regarding the `GNU make`, you should first download the `xpack build tools` and then add its `bin` folder in its "current value" field.

## Program Flow: Simplified Version

- The program starts by initializing the LED pin and setting it to ON.
- Each 10ms, the `LEDM_Manage` is called. Inside this function,
  - The LED state only changes if 500ms has passed.
  - We call the `WDGM_AlivenessIndication` to keep a count of how many times the `LEDM_Manage` was called.
- Returning to the `main` function, each 20ms, the `WDGM_MainFunction` to make sure the system works fine and the `LEDM_Manage` is called at a normal rate (8-12 times per 100ms, ideally it should be 10 times per 100ms).
- In parallel, if 50ms are passed, the `WDGDrv_IsrNotification` is called. This function checks if the `LEDM_Manage` is called at a correct rate and the program didn't get stuck at any phase (specifically in the `WDGM_MainFunction` function). Depending on that check, either the system gets reset or the watchdog gets refreshed.

## Toolstack

<p align="left"> 
  <a href="https://www.cprogramming.com/" target="_blank" rel="noreferrer"> 
    <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/c/c-original.svg" alt="c" width="40" height="40"/> 
  </a>
  <a href="https://www.eclipse.org/" target="_blank" rel="noreferrer"> 
    <img src="https://github.com/cln-Kafka/Watchdog-Timer-Use-Cases/blob/main/README-Assets/Eclipse-Luna-Logo.png" width="40" height="40"/> 
  </a>
  <a href="https://www.labcenter.com/" target="_blank" rel="noreferrer"> 
    <img src="https://upload.wikimedia.org/wikipedia/en/5/5a/Proteus_Design_Suite_Atom_Logo.png" alt="proteus" width="54" height="40"/> 
  </a>
</p>

## References

1. [Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
2. [RM0368 Reference manual - STM32F401xB/C and STM32F401xD/E - advanced Arm®-based 32-bit MCUs](https://www.st.com/resource/en/reference_manual/rm0368-stm32f401xbc-and-stm32f401xde-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

## Help

As mentioned, the shown results are generated for the ATmega328p microcontroller. Understanding pin configuration and reading chapters 10, 14, and 15 of the datasheet shall set you going with exploring the project files. However, if you encounter any issues or have questions, feel free to reach out.

## Contribution

Gratitude goes out to all team members for their valuable contributions to this project.

| <a href="https://github.com/cln-Kafka"><img src="https://avatars.githubusercontent.com/u/100665578?v=4" width="100px" alt="@Kareem Noureddine"></a> | <a href="https://github.com/Nadaaomran"><img src="https://avatars.githubusercontent.com/u/104179154?v=4" width="100px" alt="@Nadaaomran"></a> | <a href="https://github.com/nouran-19"><img src="https://avatars.githubusercontent.com/u/99448829?v=4" width="100px" alt="@nouran-19"></a> | <a href="https://github.com/MuhammadSamiAhmad"><img src="https://avatars.githubusercontent.com/u/101589634?v=4" width="100px" alt="@M.Sami"></a> |
| :-: | :-: | :-: | :-: |
| [Kareem Noureddine](https://github.com/cln-Kafka) | [Nada Omran](https://github.com/Nadaaomran") | [Nouran Khattab](https://github.com/nouran-19) | [Mohamed Sami](https://github.com/MuhammadSamiAhmad) |

## License

All rights reserved © 2024 to Team 14 of the Embedded Systems Course - Systems & Biomedical Engineering, Cairo University (Class 2025).
