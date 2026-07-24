
#include <stdbool.h>
#include "pic32c.h"
#include <SEGGER_RTT.h>
#include <stdio.h>

int main(void)
{
    SEGGER_RTT_Init();
    printf("Hello World!\n");
    while (true)
    {
    }
}
