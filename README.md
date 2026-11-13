# SEGGER-RTT

This repository contains example projects that show how to use SEGGER RTT with pyOCD.

## Quick Start

1. Install
   [Keil Studio for VS Code](https://marketplace.visualstudio.com/items?itemName=Arm.keil-studio-pack)
   from the VS Code marketplace.
2. Clone this repository, for example using
   [Git in VS Code](https://code.visualstudio.com/docs/sourcecontrol/intro-to-git),
   or download the ZIP file. Then open the repository root folder.

There are 2 example projects in this repository for the following boards:

1. [STMicroelectronics STM32F407G-DISC1](./STM/STM32F407G-DISC1) (single-core standard input and output)
2. [Infineon KIT_T2G-B-H_LITE](./Infineon/T2G-B-H) (multicore standard output)

Follow the instructions in the README file for each project.

## About SEGGER RTT

[SEGGER Real Time Transfer (RTT)](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/)
provides fast, bidirectional communication between an embedded target and a host
computer while the application is running. It can be used for terminal I/O,
diagnostic messages, and other data transfers with minimal impact on real-time
behavior.

RTT uses the target's existing debug port rather than a dedicated UART. This has
several practical benefits:

- No extra UART peripheral, pins, connector, or USB-to-serial adapter is needed.
- Production hardware can retain terminal I/O and diagnostics even when a UART
  is unavailable or not exposed on the board.
- Automated [Hardware-in-the-Loop (HIL) tests](https://github.com/Arm-Examples/.github/blob/main/profile/CICD.md#hil-testing-with-pyocd)
  can program, control, and communicate with a target through the same debug
  connection.
- Input and output are available without changing the application hardware.

[pyOCD](https://pyocd.io/) provides the host-side debug connection. It connects
to CMSIS-DAP debug units such as Arm ULINKplus, as well as ST-LINK probes, and
accesses RTT data through the target's debug port.

<p align="center">
  <img src="https://raw.githubusercontent.com/Arm-Examples/.github/main/profile/pyOCD-Tools-Ecosystem.png" width="600" alt="pyOCD tools ecosystem">
</p>
