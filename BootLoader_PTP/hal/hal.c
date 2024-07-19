/*
 * hal.c
 *
 *  Created on: May 11, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "hal.h"

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define HAL_LPUART0_IRQHandler    LPUART0_IRQHandler

/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint8_t   g_pushFailed;
static uint32_t  g_baudrate;
static funcMid   Push_Data_Func;  /* Used to save the function' address
                                          which push received data into queue */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*
 * @brief: LPUART0 interrupt handler
 */
void HAL_LPUART0_IRQHandler(void)
{
    /* Push received character into Queue */
    g_pushFailed = Push_Data_Func((uint8_t)(LPUART0->DATA));
}


/*
 * @brief: Initialize the hardware abstraction layer (HAL)
 */
void HAL_Init(void)
{
    /* Port initialization structure */
    PORT_InitTypeDef PORT_InitStruct =
    {
        .Mux  = PORT_MUX_ALT2,
        .Pull = PORT_PULL_UP,
    };

    /* GPIO initialization structure */
    GPIO_InitTypeDef GPIO_InitStruct =
    {
        .Direction = GPIO_INPUT,
    };

    /* LPUART initialization structure */
    LPUART_InitTypeDef LPUART_InitStruct =
    {
        .BaudRate         = g_baudrate,
        .Parity           = LPUART_NO_PARITY,
        .Mode             = LPUART_8_BITS_MODE,
        .StopBit          = LPUART_ONE_STOP_BIT,
        .MSBFirst         = FALSE,
        .ReceiveInverted  = FALSE,
        .TransmitInverted = FALSE
    };

    /* Fast clock initialization structure */
    SCG_FIRC_Config_t FIRC_InitStruct =
    {
        .Range    = SCG_FIRC48M,
        .FIRCDIV2 = SCG_ClkDivBy1
    };

    /* Configure clocks */
    DRI_CLOCK_EnableClock(PCC_PORTB_INDEX);          /* Enable clock for LPUART0_SDA PORT */
    DRI_CLOCK_EnableClock(PCC_PORTD_INDEX);          /* Enable clock for PORTD */
    DRI_CLOCK_InitFirc(&FIRC_InitStruct);            /* Configure the fast clock source for use with LPUART */

    /* Configure Pins for LPUART function */
    DRI_PORT_Pin_Init(LPUART0_SDA_RX_PORT, LPUART0_SDA_RX_PIN,
                                                &PORT_InitStruct);        /* PORTB-PIN0: RX Pin */
    DRI_PORT_Pin_Init(LPUART0_SDA_TX_PORT, LPUART0_SDA_TX_PIN,
                                                &PORT_InitStruct);        /* PORTB-PIN1: TX Pin */

    /* Configure GPIO function for PORTD_Pin2 (SW3) */
    PORT_InitStruct.Mux = PORT_MUX_GPIO;
    DRI_PORT_Pin_Init(BUTTON03_PORT, BUTTON03_PIN, &PORT_InitStruct);  /* Select GPIO function for PORTD Pin2 */
    DRI_GPIO_Init(BUTTON03_GPIO, BUTTON03_PIN, &GPIO_InitStruct);      /* Select input mode for Pin2 */

    /* Initialize LPUART0 module */
    DRI_LPUART0_Init(&LPUART_InitStruct);

    /* Enable interrupt for LPUART0 */
    LPUART_EnableInterrupts(LPUART0, LPUART_CTRL_RIE_MASK);
    NVIC_EnableIRQ(LPUART0_IRQn);
}


/*
 * @brief: De-initialize the hardware abstraction layer (HAL)
 */
void HAL_DeInit(void)
{
    DRI_CLOCK_DeinitFirc();                  /* De-initializes the SCG fast IRC */
    DRI_CLOCK_DisableClock(PCC_PORTB_INDEX); /* Disable clock for LPUART0_SDA PORT */
    NVIC_DisableIRQ(LPUART0_IRQn);           /* Disable interrupt */
}


/*
 * @brief: Set the baud rate used for communication in the HAL layer
 */
void HAL_SetBaudrate(const uint32_t baudrate)
{
    g_baudrate = baudrate;
}


/*
 * @brief: Transmit data via the LPUART0 peripheral
 */
void HAL_TransmitData(const uint8_t *const data, const uint32_t size)
{
    DRI_LPUART_TranmitData(LPUART0, data, size);
}


/*
 * @brief: Sets the address of a function from a higher layer in the system
 */
uint8_t HAL_getFuncAddress(const void *const funcAddress)
{
    DRI_StatusTypeDef status = 0U;

    if (funcAddress != NULL)
    {
        Push_Data_Func = funcAddress;
    }
    else
    {
        status = 1U;
    }

    return status;
}


/*
 * @brief: Initializes the user application space by erasing a specified region of flash memory
 */
uint8_t HAL_eraseFlash(const uint32_t startAddress, const uint32_t size)
{
    return Erase_Multi_Sector(startAddress, size);
}


/*
 * @brief: Checks the state of the specified button
 */
uint8_t HAL_switchIsPressed(void)
{
    return DRI_GPIO_ReadPin(BUTTON03_GPIO, BUTTON03_PIN);
}


/*
 * @brief: Returns the status of the data push operation to the queue
 */
uint8_t HAL_pushDataFailed(void)
{
    return g_pushFailed;
}


/*
 * @brief:  Jumps to the application code located at the specified address
 */
void HAL_jumpApplication(const uint32_t appAddress)
{
    __disable_irq();
    /* Clear pending interrupt request */
    SCB->ICSR |= SCB_ICSR_PENDSTCLR_Msk;
    SCB->ICSR |= SCB_ICSR_PENDSVCLR_Msk;

    /* Set vector table offset */
    SCB->VTOR = ((uint32_t)appAddress)  ;

    /* Set main stack pointer */
    __set_MSP(*(uint32_t *)appAddress);

    /* Jump to user's application */
    uint32_t app_start_address = *((volatile uint32_t *)(appAddress + 4));
    void (*app_entry_point)(void) = (void (*)(void))app_start_address;
    app_entry_point();
}


void HAL_backupApplication(const uint32_t appAddress,
                            const uint32_t backupAddress,
                            const uint32_t appSize)
{
    uint32_t index       = 0U;
    uint32_t numberWords = 0U;

    numberWords = appSize * 1024U / 4U;

    for (index = 0U; index < numberWords; ++index)
    {
        Program_LongWord(backupAddress + (index * 4U),
                            (uint8_t*) (appAddress + (index * 4U)));
    }
}


void HAL_restoreApplication(const uint32_t restoreAddress,
                            const uint32_t backupAddress,
                            const uint32_t appSize)
{
    uint32_t index       = 0U;
    uint32_t numberWords = 0U;

    numberWords = appSize * 1024U / 4U;

    for (index = 0U; index < numberWords; ++index)
    {
        Program_LongWord(restoreAddress + (index * 4U),
                            (uint8_t*) (backupAddress + (index * 4U)));
    }
}
/*******************************************************************************
 * EOF
 ******************************************************************************/
