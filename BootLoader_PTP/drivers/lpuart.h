/*
 * lpuart.h
 *
 *  Created on: May 07, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

#ifndef _INC_LPUART_H_
#define _INC_LPUART_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "dri_port.h"
#include "dri_clock.h"

/*
 * @brief: LPUART number of bits in a character
 */
typedef enum
{
    LPUART_7_BITS_MODE  = 0U, /* 8-bit data characters */
    LPUART_8_BITS_MODE  = 1U, /* 8-bit data characters */
    LPUART_9_BITS_MODE  = 2U, /* 9-bit data characters */
    LPUART_10_BITS_MODE = 3U  /* 10-bit data characters */
} LPUART_Bit_Mode_t;

/*
 * @brief: LPUART number of bits in a character
 */
typedef enum
{
    LPUART_EVEN_PARITY  = 0U,
    LPUART_ODD_PARITY   = 1U,
    LPUART_NO_PARITY    = 2U
} LPUART_Parity_t;

typedef enum
{
    LPUART_ONE_STOP_BIT = 0U,
    LPUART_TWO_STOP_BIT = 1U
} LPUART_Stop_Bit_t;

/*******************************************************************************
 * APIs
 ******************************************************************************/

/*
 * @brief:     Writes to the transmitter register
 * @param[out] LPUARTx: LPUART base pointer
 * @param[in]  data: Data write to the TX register
 */
static inline void LPUART_TransmitByte(LPUART_Type *const LPUARTx,
        const uint8_t data)
{
    LPUARTx->DATA = data;
}


/*
 * @brief:     Enable/Disable the LPUART transmitter
 * @param[out] LPUARTx: LPUART base pointer
 * @param[in]  enable: Enable or disable transmitter
 */
static inline void LPUART_Transmit_Enable(LPUART_Type *const LPUARTx,
        const uint8_t enable)
{
    LPUARTx->CTRL = (LPUARTx->CTRL & ~LPUART_CTRL_TE_MASK)
            | ((enable ? 1U : 0U) << LPUART_CTRL_TE_SHIFT);
}


/*
 * @brief:     Enable/Disable the LPUART receiver
 * @param[out] LPUARTx: LPUART base pointer
 * @param[in]  enable: Enable or disable receiver
 */
static inline void LPUART_Receive_Enable(LPUART_Type *const LPUARTx,
        const uint8_t enable)
{
    LPUARTx->CTRL = (LPUARTx->CTRL & ~LPUART_CTRL_RE_MASK)
            | ((enable ? 1U : 0U) << LPUART_CTRL_RE_SHIFT);
}


/*
 * @brief:     Sets the LPUART baud rate modulo divisor
 * @param[out] LPUARTx: LPUART base pointer
 * @param[in]  SBR: The baud rate modulo division
 */
static inline void LPUART_SetBaudRateDivisor(LPUART_Type *const LPUARTx,
        const uint32_t SBR)
{
    LPUARTx->BAUD = (((LPUARTx->BAUD) & ~LPUART_BAUD_SBR_MASK)
            | LPUART_BAUD_SBR(SBR));
}


/*
 * @brief:     Sets the LPUART baud rate oversampling ratio
 * @param[out] LPUARTx: LPUART base pointer
 * @param[in]  OSR: The oversampling ratio
 */
static inline void LPUART_SetOversamplingRatio(LPUART_Type *const LPUARTx,
        const uint8_t OSR)
{
    LPUARTx->BAUD = (LPUARTx->BAUD & ~LPUART_BAUD_OSR_MASK)
            | LPUART_BAUD_OSR(OSR);
}


/*
 * @brief:     Sets the LSB or MSB is the first bit that is transmitted following the start bit
 * @param[out] LPUARTx: LPUART base pointer
 * @param[in]  enable:  Enable or disable transmit MSB first
 */
static inline void LPUART_SetMSBfirst(LPUART_Type *const LPUARTx,
        const uint8_t enable)
{
    LPUARTx->STAT = (LPUARTx->STAT & ~LPUART_STAT_MSBF_MASK)
            | LPUART_STAT_MSBF(enable);
}


/*
 * @brief:     Sets the polarity of the received data input
 * @param[out] LPUARTx: LPUART base pointer
 * @param[in]  enable:  Enable or disable inverted data
 */
static inline void LPUART_SetReceiveDataInvert(LPUART_Type *const LPUARTx,
        const uint8_t enable)
{
	LPUARTx->STAT = (LPUARTx->STAT & ~LPUART_STAT_RXINV_MASK)
            | ((enable ? 1U : 0U) << LPUART_STAT_RXINV_SHIFT);
}


/*
 * @brief:     Sets the polarity of f the transmitted data output
 * @param[out] LPUARTx: LPUART base pointer
 * @param[in]  enable:  Enable or disable inverted data
 */
static inline void LPUART_SetTranmitDataInvert(LPUART_Type *const LPUARTx,
        const uint8_t enable)
{
	LPUARTx->CTRL = (LPUARTx->CTRL & ~LPUART_CTRL_TXINV_MASK)
            | ((enable ? 1U : 0U) << LPUART_CTRL_TXINV_SHIFT);
}


/*
 * @brief:     Sets the Stop Bit Number
 * @param[out] LPUARTx: LPUART base pointer
 * @param[in]  stopBit:  determines whether data characters have one or two stop bits
 */
static inline void LPUART_SetStopBit(LPUART_Type *const LPUARTx,
        const LPUART_Stop_Bit_t stopBit)
{
    LPUARTx->BAUD = (LPUARTx->BAUD & ~LPUART_BAUD_SBNS_MASK)
            | LPUART_BAUD_SBNS(stopBit);
}


/*
 * @brief:     Enables LPUART interrupts according to a provided mask.
 * @param[out] LPUARTx: LPUART base pointer
 * @param[in]  mask: The interrupts to enable
 */
static inline void LPUART_EnableInterrupts(LPUART_Type *LPUARTx, const uint32_t mask)
{
    LPUARTx->CTRL |= mask;
}


/*
 * @brief:     Enables sampling of the received data on both edges of the baud rate clock
 * @param[out] LPUARTx: LPUART base pointer
 */
static inline void LPUART_EnableBothEdgeSampling(LPUART_Type *const LPUARTx)
{
    LPUARTx->BAUD |= LPUART_BAUD_BOTHEDGE_MASK;
}


/*
 * @brief: Configures the number of bits per char in LPUART controller
 */
void LPUART_SetBitMode(LPUART_Type *const LPUARTx, const LPUART_Bit_Mode_t bitMode);


/*
 * @brief: Configures parity mode in the LPUART
 */
void LPUART_SetParity(LPUART_Type *const LPUARTx, const LPUART_Parity_t Parity);

#endif /* _INC_LPUART_H_ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
