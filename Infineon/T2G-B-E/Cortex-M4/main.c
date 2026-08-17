// Copyright (c) 2024 Infineon Technologies AG. All rights reserved
// Licensed under the Apache License, Version 2.0, see APACHE_LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include <SEGGER_RTT.h>
#include <stdio.h>

#include "cy_pdl.h"
#include "cycfg_pins.h"

/*******************************************************************************
* Macros
********************************************************************************/
/* 8MHz IMO clock with 8000000 reload value to generate 1s interrupt */
#define SYSTICK_RELOAD_VAL   (4000000UL)

/*******************************************************************************
* Function Prototypes
********************************************************************************/
static void led_timer_cb(void);

/*******************************************************************************
* Global Variables
********************************************************************************/
bool timer_interrupt_flag = false;

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
* This main achieve the systick timer interrupt function. Toggle user led when generate
* the systick interrupt with 1s period.
*
* Return: int
*
*******************************************************************************/

int main(void)
{
    __enable_irq();

    SEGGER_RTT_Init();

    printf("Hello from Cortex-M4!\n");

    /* Initialize the systick, set the 8MHz IMO as clock source */
    Cy_SysTick_Init(CY_SYSTICK_CLOCK_SOURCE_CLK_IMO, SYSTICK_RELOAD_VAL);

    /* Set Systick interrupt callback */
    Cy_SysTick_SetCallback(0, led_timer_cb);

    /* Enable Systick and the Systick interrupt */
    Cy_SysTick_Enable();

    putchar( '\x04' ) ;  // Send EOT to terminate RTT session
    fflush(stdout) ;

    for (;;)
    {
        /* Check if timer elapsed (interrupt fired) and toggle the LED */
        if (timer_interrupt_flag)
        {
            /* Clear the flag */
            timer_interrupt_flag = false;

            /* Invert the USER LED state */        
            Cy_GPIO_Inv(LED2_PORT, LED2_PIN);                   
        }
    }	
}

/*******************************************************************************
* Function Name: led_timer_cb
********************************************************************************
*
*  Summary:
*  Systick interrupt handler callback
*
*  Parameters:
*  None
*
*  Return:
*  None
*
**********************************************************************************/
void led_timer_cb(void)
{
    /* Set the interrupt flag and process it from the main while(1) loop */
    timer_interrupt_flag = true;
}

/* [] END OF FILE */
