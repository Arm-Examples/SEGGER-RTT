# SEGGER-RTT

[![Build SEGGER RTT Multicore](https://github.com/Arm-Examples/SEGGER-RTT/actions/workflows/Build_SEGGER-RTT_Multicore.yml/badge.svg)](https://github.com/Arm-Examples/SEGGER-RTT/actions/workflows/Build_SEGGER-RTT_Multicore.yml)
[![Build SEGGER RTT STM32F407](https://github.com/Arm-Examples/SEGGER-RTT/actions/workflows/Build_SEGGER-RTT_STM32F407.yml/badge.svg)](https://github.com/Arm-Examples/SEGGER-RTT/actions/workflows/Build_SEGGER-RTT_STM32F407.yml)
[![Run SEGGER RTT Multicore](https://github.com/Arm-Examples/SEGGER-RTT/actions/workflows/Run_SEGGER-RTT_Multicore.yml/badge.svg)](https://github.com/Arm-Examples/SEGGER-RTT/actions/workflows/Run_SEGGER-RTT_Multicore.yml)

This repository contains example projects that show how to use SEGGER RTT with
pyOCD. The examples carry standard I/O over the existing debug connection, so
neither the target nor the test system needs a dedicated UART, extra pins, a
connector, or a serial adapter. RTT can route this I/O to an interactive console
during development or to files for repeatable, headless test automation, with
minimal impact on real-time behavior.

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

## Target Sets

Each solution contains two target sets that configure how RTT standard I/O is
handled by pyOCD:

- `console` connects RTT channel 0 to an interactive serial console I/O.
- `file-io` redirects RTT standard I/O to files. This target set is especially
  useful for automated, headless tests with pyOCD because test output can be
  collected and checked without an interactive terminal. The STM example reads
  `name.txt` and writes `output.txt`; the Infineon multicore example writes
  `output_Cortex-M0p.txt`, `output_Cortex-M7-0.txt`, and
  `output_Cortex-M7-1.txt`.

After building the Infineon solution with the `file-io` target set and
programming the board, run the test from `Infineon/T2G-B-H/out` with:

```sh
pyocd run --cbuild-run RTT_Multicore+CYT4BF8CDS.cbuild-run.yml --eot -O reset_type=sysresetreq --timelimit 10
```

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

## Continuous Integration and Hardware-in-the-Loop Test

The CMSIS solution files are used for local development, CI builds, and target
execution. The workflows use:

- [`vcpkg-configuration.json`](./vcpkg-configuration.json) to install consistent
  tools on developer systems and GitHub-hosted runners.
- The `*.csolution.yml` files to describe the projects, software packs, build
  contexts, and target sets.
- The generated `*.cbuild-run.yml` file to provide pyOCD with the images and
  target configuration for hardware execution.

[![CI and HIL test setup](https://raw.githubusercontent.com/Arm-Examples/Safety-Example-Infineon-T2G/main/Doc/CI_HIL.png)](https://github.com/Arm-Examples/.github/blob/main/profile/CICD.md#hil-testing-with-pyocd)

| Workflow | Description |
| --- | --- |
| [Build SEGGER RTT Multicore](./.github/workflows/Build_SEGGER-RTT_Multicore.yml) | Builds the Infineon application with the `file-io` target set on a GitHub-hosted runner and uploads the generated files as an artifact. |
| [Run SEGGER RTT Multicore](./.github/workflows/Run_SEGGER-RTT_Multicore.yml) | Runs on a self-hosted Linux runner connected to the Infineon KIT_T2G-B-H_LITE. It downloads the build artifact, programs and executes the target with pyOCD, captures RTT output, and verifies the output from all three cores. |
| [Build SEGGER RTT STM32F407](./.github/workflows/Build_SEGGER-RTT_STM32F407.yml) | Builds the STM32F407 application on a GitHub-hosted runner. This example has no HIL run action. |

The HIL equipment and self-hosted runner are configured outside this
repository. See the shared Arm-Examples instructions:

- [HIL testing with pyOCD](https://github.com/Arm-Examples/.github/blob/main/profile/CICD.md#hil-testing-with-pyocd)
- [Set up a Raspberry Pi as a self-hosted GitHub runner](https://github.com/Arm-Examples/.github/blob/main/profile/RPI_GH_Runner.md)
