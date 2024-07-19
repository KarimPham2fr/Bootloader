/*
 * dri_lpuart.h
 *
 *  Created on: May 5, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

#ifndef _INC_DRI_LPUART_H_
#define _INC_DRI_LPUART_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lpuart.h"

/*******************************************************************************
 * Typedef structs
 ******************************************************************************/

/*
 * @brief LPUART Init Structure definition
 */
typedef struct
{
    uint32_t           BaudRate;
    LPUART_Stop_Bit_t  StopBit;
    LPUART_Parity_t    Parity;
    LPUART_Bit_Mode_t  Mode;
    uint32_t           OverSampling;
    uint8_t            MSBFirst;
    uint8_t            ReceiveInverted;
    uint8_t            TransmitInverted;
} LPUART_InitTypeDef;

/*******************************************************************************
 * APIs
 ******************************************************************************/

/*
 * @brief: Set the baud rate for the LPUART peripheral
 * @param[out] LPUARTx: LPUART base pointer
 * @param[in]  desiredBaudRate: The desired baud rate to be set
 * @return: None
 */
void DRI_LPUART_SetBaudRate(LPUART_Type *LPUARTx, const uint32_t desiredBaudRate);


/*
 * @brief: Initialize the LPUART0 peripheral with the provided configuration
 * @param[in] LPUART_Init: Pointer to a structure containing the initialization parameters
 * @return: None
 */
void DRI_LPUART0_Init(const LPUART_InitTypeDef* const LPUART_Init);


/*
 * @brief: Transmit data via the specified LPUART peripheral
 * @param[out] Data: Pointer to the data buffer to be transmitted
 * @param[in]  size: Size of the data buffer to be transmitted
 * @return: None
 */
void DRI_LPUART_TranmitData(LPUART_Type *const LPUARTx,
        const uint8_t *const Data, const uint32_t size);

#endif /* _INC_DRI_LPUART_H_ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
