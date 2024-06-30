# Watchdog Timer Use cases

## Table of Contents
- [Description](#description)
- [Main Components](#main-components)
- [Observations and Discussion](#observations-and-discussion)
- [Reproducing the Results](#reproducing-the-results)
- [Dependency Installation](#dependency-installation)
- [Program Flow: Simplified Version](#program-flow-simplified-version)
- [Toolstack](#toolstack)
- [References](#references)
- [Help](#help)
- [Contribution](#contribution)
- [License](#license)

## Description

This project aims to implement the watchdog timer driver for the ATmega328p AVR and STM32f401xE microcontrollers and test its functionality using a blinking LED. The watchdog timer is a crucial safety feature available in many microcontrollers, designed to protect the system in case of a malfunction.

The watchdog timer operates like a countdown counter, starting from a specified value and decrementing towards zero. During normal operation, the system should reset the watchdog timer to its initial value at the end of each cycle. If the system fails to refresh the watchdog timer and it reaches zero, the watchdog timer will reset the system. This behavior indicates a potential malfunction that prevented the system from refreshing the watchdog timer.

The tests include a positive scenario where everything functions correctly and the system successfully refreshes the watchdog timer. Additionally, there are three negative scenarios discussed in the [Observations and Discussion](#observations-and-discussion) section, where the system fails to refresh the watchdog timer, triggering a reset to demonstrate the watchdog timer's protective mechanism.

## Main Components

### Pin Controller `GPIO`

This component includes two functions:

* **`GPIO_Init`**: This function only configures the pin that the LED is connected to as output.

* **`GPIO_Write`**: This function takes the preferred state of the LED, either ON (1) or OFF (0), and depending on it, it sets the LED pin to high or low.

### LED State Manager `LEDMgr`

This component includes two functions:

* **`LEDM_Init`**: This function initializes the LED pin and sets its initial state.
  - It calls `GPIO_Init` to configure the LED pin as an output.
  - It sets the initial state of the LED to "High" by calling `GPIO_Write`, which writes a 1 to the LED pin bit position in the port data register.

* **`LEDM_Manage`**: This function is intended to be called repeatedly inside the super loop of the `main` function in `main.c`. It has two main responsibilities:
   - Toggling the LED state every 500ms.
   - Calling `WDGM_AlivenessIndication` each time it is executed to indicate the function's aliveness.

### Watchdog Manager `WDGM`

This component includes four functions:

* **`WDGM_Init`**: This function initializes the internal variables of the Watchdog Manager, setting them to their initial values.

* **`WDGM_MainFunction`**: This function is called in the super loop of the `main` function in `main.c`. Every 100ms, it checks the call rate of the `LEDM_Manage` function to ensure it falls within a valid range. Ideally, `LEDM_Manage` should be called 10 times per 100ms. Due to possible delays in hardware components, it accepts a range of 8 to 12 calls per 100ms. If the call rate is within this range, it sets the global variable `wdgmStatus` to `OK`, indicating normal operation. Otherwise, it sets `wdgmStatus` to `NOK`, signaling a potential issue.

* **`WDGM_ProvideSupervisionStatus`**: This function returns the current status of the Watchdog Manager (`wdgmStatus`). It is used by the `WDGDrv` file to determine if the system is functioning normally or if there is a malfunction requiring a system reset.

* **`WDGM_AlivenessIndication`**: This function is called by `LEDM_Manage` each time it is executed. It increments a global counter that tracks the number of times `LEDM_Manage` has been called within the 100ms period.

### Watchdog Driver `WDGDrv`

This component includes two main functions and one helper function that are needed for the Watchdog Driver:

* **`WDGDrv_Init`**: This function initializes the watchdog timer.
  - **For ATmega328p AVR**:
    - Sets the maximum timeout value to 64ms.
    - Activates the watchdog.
    - Optionally initializes another timer, depending on your implementation. This can be included here or in a separate function or source file.

  - **For STM32F401xE**:
    - Sets the maximum timeout value to 50ms.
    - Disables the window mode.
    - Enables the early interrupt feature.
    - Activates the watchdog.

* **`ISR(TIMER1_COMPA_vect)`**: This is the Interrupt Service Routine (ISR) executed when Timer1 reaches the compare value (50ms). It calls the `WDGDrv_IsrNotification` function to handle the watchdog functionality.

* **`WDGDrv_IsrNotification`**: This function retrieves the status of the Watchdog Manager using `WDGM_PovideSuppervisionStatus()` and checks if the system is stuck in the `WDGM_MainFunction`. Based on this check:
  - If the status is `OK` and the system is not stuck (`stuck_flag != 1`), it refreshes the watchdog timer.
  - If the system is stuck, no action is taken, which allows the watchdog timer to expire and potentially reset the system.

## Observations and Discussion

### Scenario A: Positive Scenario

### Scenario B: Negative Scenario

In this scenario, we should comment the call of the `WDGM_MainFunction` function in the `main` function. We expect the watchdog timer to reset the system each 64ms.

### Scenario C: Negative Scenario

In this scenario, we should comment the call of the `WDGM_AlivenessIndication` function in the `LEDM_Manage` function. we expect the watchdog timer to reset the system after 114ms.

### Scenario D: Negative Scenario

In this scenario, we should decrease the periodicity of the call of the `LEDM_Manage` to be every 5ms. we expect the watchdog timer to reset the system after 114ms.

## Reproducing the Results

1. **Install ATmega328p**: Follow the ATmega328p installation guide in the [Dependency Installation](#dependency-installation) section.
2. **Import Project**: Import the project from [BlinkingLed_with_Watchdog](https://github.com/cln-Kafka/Watchdog-Timer-Use-Cases/tree/main/Code-for-AVR-ATmega328p/BlinkingLed_with_Watchdog) into Eclipse IDE.
3. **Rebuild Project**: Rebuild the project in Eclipse.
4. **Open Simulation**: Open the [simulation file](https://github.com/cln-Kafka/Watchdog-Timer-Use-Cases/tree/main/Proteus_Simulation) in Proteus (preferably **version 8.9**).
5. **Load Program File**: In Proteus, ensure the `.elf` or `.hex` file is loaded in the `Program File` field by double-clicking the microcontroller.
6. **Run Simulation**: Start the simulation. By default, the code is set to the positive scenario.

**To Reproduce Negative Scenarios**:

- **Option 1**: Follow the above steps but open the specific scenario project in Eclipse. These projects are available [here](https://github.com/cln-Kafka/Watchdog-Timer-Use-Cases/tree/main/Code-for-AVR-ATmega328p/Scenarios).
- **Option 2**: Edit the original project files to comment out the lines specified for each scenario. Rebuild the project in Eclipse and then run the simulation.

## Dependency Installation

### STM32F401xE Microcontroller

### ATmega328p AVR Microcontroller

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
- In parallel, if 50ms are passed, the `WDGDrv_IsrNotification` is called. This function checks if the `LEDM_Manage` is called at a correct rate and the program didn't get stuck at any phase (specifically in the `WDGM_MainFunction` function). Depending on that check, either the system gets reset or the watchdog timer gets refreshed.

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
