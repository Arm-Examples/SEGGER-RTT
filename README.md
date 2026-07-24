# SEGGER-RTT
This example project shows how to use SEGGER RTT with pyOCD.

It redirects printf()-output to SEGGER-RTT, which can then be viewed in the debbuger console.

The ability of pyocd to read the RTT data from the target memory is used.

The board used for the example is a PIC32CM L10-CNANO. But using SEGGER-RTT like in this example also works with any other device/board.

## Quick Start
1. Install
   [Keil Studio for VS Code](https://marketplace.visualstudio.com/items?itemName=Arm.keil-studio-pack)
   from the VS Code marketplace.
2. Clone this repository, for example using
   [Git in VS Code](https://code.visualstudio.com/docs/sourcecontrol/intro-to-git),
   or download the ZIP file. Then open the repository root folder.
3. Let the related tools and software packs download and install. Review progress with **View > Output > CMSIS Solution**.
4. Connect the board to the PC.
5. Build and load the project with the CMSIS View
   [action buttons](https://github.com/Open-CMSIS-Pack/vscode-cmsis-solution#action-buttons).
6. Open a terminal in VS Code an execute the follwing:
   `pyocd run --cbuild-run .\out\SEGGER-RTT+PIC32CM6408PL10048.cbuild-run.yml --eot --timelimit 1`
7. See the "Hello World!" output from the example in the terminal.

## Requirements
For SEGGER-RTT to work as shown in this example, the following packs and in its versions need to be installed:
- Segger::RTT pack version  8.58.0 or newer
- ARM::CMSIS-Compiler pack version 2.3.1 or newer

## Adding RTT printf() Output to an Application
1. In the Manage Software Components enable the following:
   - Segger -> RTT
   - CMSIS-Compiler > CORE
   - CMSIS-Compiler > STDOUT (API) > RTT
2. Additions to the source code are the following:
   - Include required files:
     ```
     #include <SEGGER_RTT.h>
     #include <stdio.h>
     ```
   - Call SEGGER_RTT_Init():
     ```
     SEGGER_RTT_Init();
     ```
   - Use normal printf() for outputting fomatted text:
     ```
     printf("Hello World!\n");
     ```
3. Solution and Project Configiration
   - in Manage solution select your debug adapter and enable Telnet with Telnet Mode "Debug Console"
   - in the csolution file, add under the debugger: node, add the rtt: node:
     ```
     rtt:
       - channel:
         - number: 0
           mode: stdio
     ```
## Possible modifications
1. Instead of printing to the console, pyocd can output RTT via a telnet port. For this set the Telnet Mode to "Telnet Server".
