/*
 * lpuart.c
 *
 *  Created on: May 07, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lpuart.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*
 * @brief:      Configures the number of bits per char in LPUART controller
 * @param[out]: LPUARTx: LPUART base pointer
 * @param[in]:  bitMode: Bit mode select
 * @return:     None
 */
void LPUART_SetBitMode(LPUART_Type *const LPUARTx, const LPUART_Bit_Mode_t bitMode)
{
    switch (bitMode)
    {
        case LPUART_10_BITS_MODE:
            LPUARTx->BAUD = (LPUARTx->BAUD & ~LPUART_BAUD_M10_MASK)
                    | ((uint32_t) 1U << LPUART_BAUD_M10_SHIFT);
            break;

        case LPUART_9_BITS_MODE:
            LPUARTx->BAUD &= ~LPUART_BAUD_M10_MASK;
            LPUARTx->CTRL = (LPUARTx->CTRL & ~LPUART_CTRL_M7_MASK)
                    | ((uint32_t) 1U << LPUART_CTRL_M_MASK);
            break;

        case LPUART_8_BITS_MODE:
            LPUARTx->BAUD &= ~LPUART_BAUD_M10_MASK;
            LPUARTx->CTRL = (LPUARTx->CTRL
                    & ~(LPUART_CTRL_M7_MASK | LPUART_CTRL_M_MASK));
            break;

        case LPUART_7_BITS_MODE:
            LPUARTx->BAUD &= ~LPUART_BAUD_M10_MASK;
            LPUARTx->CTRL |= LPUART_CTRL_M7(1U);
            break;

        default:
            break;
    }
}


/*
 * @brief:      Configures parity mode in the LPUART
 * @param[out]: LPUARTx: LPUART base pointer
 * @param[in]:  Parity: Disable or Odd parity or Even parity
 * @return:     None
 */
void LPUART_SetParity(LPUART_Type *const LPUARTx, const LPUART_Parity_t Parity)
{
    switch (Parity)
    {
        case LPUART_ODD_PARITY:
        case LPUART_EVEN_PARITY:
            LPUARTx->CTRL = (LPUARTx->CTRL
                    & ~(LPUART_CTRL_PE_MASK | LPUART_CTRL_PT_MASK))
                    | (LPUART_CTRL_PT(Parity) | LPUART_CTRL_PE_MASK);
            break;

        case LPUART_NO_PARITY:
            LPUARTx->CTRL = (LPUARTx->CTRL & ~LPUART_CTRL_PE_MASK);
            break;

        default:
            break;
    }
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
