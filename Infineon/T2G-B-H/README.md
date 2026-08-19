# SEGGER-RTT
This example project shows how to use SEGGER RTT with pyOCD.

It redirects printf() output to SEGGER RTT. You can view the output in the debugger console.

pyOCD reads RTT data directly from target memory.

This example uses the Infineon KIT_T2G-B-H_LITE board. The CYT4BF8CDS device on this board has 3 cores. You can use RTT to route debug output from all 3 cores to the same console. Therefore, you do not need a separate debug channel for each core.

The same approach also works with other devices and boards.

## Quick Start
1. In the [CMSIS View](https://github.com/Open-CMSIS-Pack/vscode-cmsis-solution#action-buttons) open the menu in the actions button and choose **Open Solution in Workspace ...**.
2. Choose **Infineon/T2G-B-H/SEGGER-RTT_Multicore**.
3. Let the related tools and software packs download and install. Review progress with **View > Output > CMSIS Solution**.
4. Connect the board to the PC.
5. Build and load the project with the CMSIS View
   [action buttons](https://github.com/Open-CMSIS-Pack/vscode-cmsis-solution#action-buttons).
6. Change focus to the CMSIS Run Terminal.
7. See the "Hello from ..." output from every core in the terminal.

## Requirements
To use SEGGER RTT as shown in this example in your own project, install the following additional packs:
- `Segger::RTT` pack, version 8.58.0 or later
- `ARM::CMSIS-Compiler` pack, version 2.3.0 or later

## Adding RTT printf() Output to an Application
1. In the [Software Components view](https://github.com/Open-CMSIS-Pack/vscode-cmsis-solution#software-components-view), enable the following:
   - `Segger` → `RTT`
   - `CMSIS-Compiler` → `CORE`
   - `CMSIS-Compiler` → `STDOUT (API)` → `RTT`

2. Add the following code to your application:

  - Include the required header files:

    ```c
    #include <SEGGER_RTT.h>
    #include <stdio.h>
    ```

  - Call `SEGGER_RTT_Init()`:

    ```c
    SEGGER_RTT_Init();
    ```

  - Use `printf()` to output formatted text:

    ```c
    printf("Please enter your name: ");
    ```

3. Solution and Project Configuration
  - In the [Manage Solution view](https://github.com/Open-CMSIS-Pack/vscode-cmsis-solution#manage-solution-view), select your debug adapter.
  - Enable **Telnet** and set **Telnet Mode** to **Debug Console**.
  - In the `csolution.yml` file, add the following [`rtt:`](https://open-cmsis-pack.github.io/cmsis-toolbox/pyOCD-Debugger/#rtt) node under the [`debugger:`](https://open-cmsis-pack.github.io/cmsis-toolbox/pyOCD-Debugger/#debugger) node:

     ```yaml
            rtt:
              - pname: Cortex-M0p
                channel:
                  - number: 0
                    mode: stdio
              - pname: Cortex-M7-0
                channel:
                  - number: 0
                    mode: stdio
              - pname: Cortex-M7-1
                channel:
                  - number: 0
                    mode: stdio
     ```
     **Note:** The `pname` values for individual cores can differ between devices. Check the `pname` values for your device when you add RTT support to your multicore project.
#### Optional configurations
1. Instead of sending RTT output to the debug console, pyOCD can expose it through a Telnet server. To use this mode, set **Telnet Mode** to **Telnet Server**.
2. Use **file-io** mode to read input from a file and write output to a file. To test this mode, change **Target Set** from **console** to **file-io** in the  [Manage Solution view](https://github.com/Open-CMSIS-Pack/vscode-cmsis-solution#manage-solution-view) dialog.
