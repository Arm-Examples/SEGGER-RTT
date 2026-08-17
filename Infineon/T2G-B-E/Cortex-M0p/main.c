// Copyright (c) 2024 Infineon Technologies AG. All rights reserved
// Licensed under the Apache License, Version 2.0, see APACHE_LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include <SEGGER_RTT.h>
#include <stdio.h>

#include "cy_pdl.h"
#include "cybsp.h"

/*******************************************************************************
* Macros
********************************************************************************/
/* 8MHz IMO clock with 8000000 reload value to generate 1s interrupt */
#define SYSTICK_RELOAD_VAL   (8000000UL)

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
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init() ;
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    __enable_irq();

    SEGGER_RTT_Init();

    printf("Hello from Cortex-M0+!\n");

	Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR);
    /* Initialize the systick, set the 8MHz IMO as clock source */
    Cy_SysTick_Init(CY_SYSTICK_CLOCK_SOURCE_CLK_IMO, SYSTICK_RELOAD_VAL);

    /* Set Systick interrupt callback */
    Cy_SysTick_SetCallback(0, led_timer_cb);

    /* Enable Systick and the Systick interrupt */
    Cy_SysTick_Enable();

    for (;;)
    {
        /* Check if timer elapsed (interrupt fired) and toggle the LED */
        if (timer_interrupt_flag)
        {
            /* Clear the flag */
            timer_interrupt_flag = false;

            /* Invert the USER LED state */        
            Cy_GPIO_Inv(LED1_PORT, LED1_PIN);
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
