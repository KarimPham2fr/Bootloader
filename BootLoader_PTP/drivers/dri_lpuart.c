/*
 * dri_lpuart.c
 *
 *  Created on: Apr 12, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "dri_lpuart.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*
 * @brief: Calculate the optimal oversampling ratio (OSR) and sampling bit rate (SBR)
 *         for a given baud rate and clock frequency
 * @param[in] baudrate: The target baud rate
 * @param[in] clock: The clock frequency
 * @param[out] osr: Pointer to store the calculated oversampling ratio
 * @param[out] sbr: Pointer to store the calculated sampling bit rate
 * @return: None
 */
static void DRI_LPUART_Calculate_OSR_SBR(const uint32_t baudrate,
        const uint32_t clock, uint8_t *const osr, uint32_t *const sbr);


/*
 * @brief: Set the baud rate for the LPUART peripheral
 */
void DRI_LPUART_SetBaudRate(LPUART_Type *const LPUARTx, const uint32_t desiredBaudRate)
{
    uint8_t  BAUD_OSR  = 0U; /* Note: Bit value is one less than actual value */
    uint32_t BAUD_SBN  = 0U;
    uint32_t frequency = 0U; /* Clock frequency used for LPUART module */

    if (LPUARTx != NULL)
    {
        /* Get frequency is being used for LPUART */
        frequency = DRI_CLOCK_SYS_Get_FIRCDIV2_CLK();
        /* Calculate OSR and SBN value */
        DRI_LPUART_Calculate_OSR_SBR(desiredBaudRate, frequency, &BAUD_OSR, &BAUD_SBN);
        /* The OSR value calculated from the 'DRI_LPUART_Calculate_OSR_SBR' function
         * has been decremented by 1 compared to the actual value (the accurate value
         * is the value at the OSR field in the BAUD register)
         */
        if (BAUD_OSR < 7U)
        {
            LPUART_EnableBothEdgeSampling(LPUARTx);
        }
        else
        {
            /* Do Nothing */
        }
        LPUART_SetOversamplingRatio(LPUARTx, BAUD_OSR);
        LPUART_SetBaudRateDivisor(LPUARTx, BAUD_SBN);
    }
    else
    {
        /* Do Nothing */
    }
}


/*
 * @brief: Initialize the LPUART0 peripheral with the provided configuration
 */
void DRI_LPUART0_Init(const LPUART_InitTypeDef *const LPUART_Init)
{
    /* Select clock source for LPUART0: FIRCDIV2_CLK */
    DRI_CLOCK_SelectSource(PCC_LPUART0_INDEX, CLOCK_SrcFircAsync);
    /* Enable the interface clock for the LPUART0 peripheral */
    DRI_CLOCK_EnableClock(PCC_LPUART0_INDEX);

    /* Disable LPUART TX RX before setting */
    LPUART_Transmit_Enable(LPUART0, FALSE);
    LPUART_Receive_Enable(LPUART0, FALSE);

    /* Configure number of bits data */
    LPUART_SetBitMode(LPUART0, LPUART_Init->Mode);

    /* Configure Parity and Parity type */
    LPUART_SetParity(LPUART0, LPUART_Init->Parity);

    /* Configure transmit LSB or MSB first */
    LPUART_SetMSBfirst(LPUART0, LPUART_Init->MSBFirst);

    /* Configure Data Inversion */
    LPUART_SetReceiveDataInvert(LPUART0, LPUART_Init->ReceiveInverted);
    LPUART_SetTranmitDataInvert(LPUART0, LPUART_Init->TransmitInverted);

    /* Configure stop bit */
    LPUART_SetStopBit(LPUART0, LPUART_Init->StopBit);

    /* Configure BaudRate */
    DRI_LPUART_SetBaudRate(LPUART0, LPUART_Init->BaudRate);

    /* Enable the Receiver and Transmitter */
    LPUART_Transmit_Enable(LPUART0, TRUE);
    LPUART_Receive_Enable(LPUART0, TRUE);
}


/*
 * @brief: Transmit data via the specified LPUART peripheral
 */
void DRI_LPUART_TranmitData(LPUART_Type *const LPUARTx,
        const uint8_t *const Data, const uint32_t size)
{
    uint32_t index = 0U;

    if ((LPUARTx != NULL) && (Data != NULL))
    {
        for (index = 0; index < size; ++index)
        {
            /* Wait the Transmitter buff is empty */
            while (((LPUARTx->STAT >> LPUART_STAT_TDRE_SHIFT) & 1U) == 0U);
            /* Transmit Data */
            LPUARTx->DATA = Data[index];
        }
    }
    else
    {
    	/* Do Nothing */
    }
}


/*
 * @brief: Calculate the optimal over-sampling ratio (OSR) and sampling bit rate (SBR)
 *         for a given baud rate and clock frequency
 */
static void DRI_LPUART_Calculate_OSR_SBR(const uint32_t baudrate,
        const uint32_t clock, uint8_t *const osr, uint32_t *const sbr)
{
    uint32_t osr_candidate       = 0U;
    uint32_t sbr_candidate       = 0U;
    uint32_t calculated_baudrate = 0U;
    uint32_t error               = 0U;
    uint32_t min_error           = 0U;

    min_error = baudrate; /* Set min_error greater than baud rate to ensure finding the exact result */

    for (osr_candidate = 4U; osr_candidate <= 32U; ++osr_candidate)
    {
        for (sbr_candidate = 1U; sbr_candidate <= 8191U; ++sbr_candidate)
        {
            calculated_baudrate = clock / ((osr_candidate + 1U) * sbr_candidate);
            error = baudrate - calculated_baudrate;

            if (error == 0U)
            {
                /* If a pair (OSR, SBR) is exactly 100%, return immediately */
                *osr = osr_candidate;
                *sbr = sbr_candidate;
                return;
            }

            /* If this error is less than the previous error update the result */
            if (abs(error) < min_error)
            {
                min_error = abs(error);
                *osr = osr_candidate;
                *sbr = sbr_candidate;
            }
        }
    }
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
