# SEGGER-RTT
This example demonstrates how to use SEGGER RTT with pyOCD on a STM32F407G-DISC1 board, but the same approach also works with other devices and boards. It redirects `printf()` output and `scanf()` input through RTT, allowing you to interact with the application from the **Debug Console** window. pyOCD reads RTT data directly from target memory without using an interface like UART.


## Quick Start
1. Open the [CMSIS View](https://github.com/Open-CMSIS-Pack/vscode-cmsis-solution#action-buttons) and choose **Open Solution in Workspace ...**.
2. Choose **STM/STM32F407G-DISC1/SEGGER-RTT**.
3. Let the related tools and software packs download and install. Review progress with **View > Output > CMSIS Solution**.
4. Connect the board to the PC.
5. In the CMSIS View, use the [Action Buttons](https://github.com/Open-CMSIS-Pack/vscode-cmsis-solution#action-buttons) to build, load and debug the project on the board.
6. Change focus to the CMSIS Run Terminal.
7. See the **Please enter your name: ** output from the example in the terminal.
8. Type in something, like your name and press enter.
9. See the "Hello " and your text in the terminal.

## Requirements
To use SEGGER RTT as shown in this example in your own project, install the following additional packs:
- [`Segger::RTT`](https://www.keil.arm.com/packs/rtt-segger/overview/) pack, version 8.58.0 or later
- [`ARM::CMSIS-Compiler`](https://www.keil.arm.com/packs/cmsis-compiler-arm/overview/) pack, version 2.3.0 or later

## Adding RTT printf() Output to an Application
1. In the [Software Components view](https://github.com/Open-CMSIS-Pack/vscode-cmsis-solution#software-components-view), enable the following:
   - `Segger` → `RTT`
   - `CMSIS-Compiler` → `CORE`
   - `CMSIS-Compiler` → `STDOUT (API)` → `RTT`
   - `CMSIS-Compiler` → `STDIN (API)` → `RTT`
2. Add the following code to your application:

  - Include the required header files:

    ```c
    #include <SEGGER_RTT.h>
    #include <stdio.h>
    ```

  - Call `SEGGER_RTT_Init()` at the beginning of your application:

    ```c
    SEGGER_RTT_Init();
    ```

  - Use `printf()` to output formatted text:

    ```c
    printf("Please enter your name: ");
    ```

  - Use `scanf()` to read formatted input:

    ```c
    scanf("%s", Buffer);
    ```
3. Solution and Project Configuration
  - In the [Manage Solution view](https://github.com/Open-CMSIS-Pack/vscode-cmsis-solution#manage-solution-view), select your debug adapter.
  - Enable **Telnet** and set **Telnet Mode** to **Debug Console**.
  - In the `csolution.yml` file, add the following [`rtt:`](https://open-cmsis-pack.github.io/cmsis-toolbox/pyOCD-Debugger/#rtt) node under the [`debugger:`](https://open-cmsis-pack.github.io/cmsis-toolbox/pyOCD-Debugger/#debugger) node:

     ```yaml
            rtt:
              - channel:
                - number: 0
                  mode: stdio
     ```
#### Optional configurations
Instead of redirecting stdin/stdout to the debug console, pyOCD can also use:
1. A **Telnet server**: To use this mode, set **Telnet Mode** to **Telnet Server** in the [Manage Solution view](https://github.com/Open-CMSIS-Pack/vscode-cmsis-solution#manage-solution-view).
2. **File input/output**: In this mode, the text input is read from a file and the output is written to a different file. This is especially useful for automated tests. To test this mode, change **Target Set** from **console** to **file-io** in the  [Manage Solution view](https://github.com/Open-CMSIS-Pack/vscode-cmsis-solution#manage-solution-view) dialog. The `csolution.yml` file of this project already contains the configuration for this in the [`debugger:`](https://open-cmsis-pack.github.io/cmsis-toolbox/pyOCD-Debugger/#debugger) node:

      ```yaml
            stdio:
              - mode: file
                file-in: ..\name.txt
                file-out: ..\output.txt
            rtt:
              - channel:
                  - number: 0
                    mode: stdio
      ```
The file **name.txt** is already provided in this project and the file **output.txt** will be generated when you run the application in this configration. Please note that stopping pyOCD with the **Load & Run / Stop** [Action Button](https://github.com/Open-CMSIS-Pack/vscode-cmsis-solution#action-buttons) will leave an empty output.txt file. Instead, stop pyOCD in the CMSIS Run Terminal with a CTRL+C key to close the file output.txt properly. For automated tests, you can start pyOCD with the subcommand **run** and the option --eot. In this case, pyOCD will stop when an EOT character (0x04) is sent by the application.   
