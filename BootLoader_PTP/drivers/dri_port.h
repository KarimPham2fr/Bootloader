/*
 * dri_port.h
 *
 *  Created on: Apr 12, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

#ifndef _INC_DRI_PORT_H_
#define _INC_DRI_PORT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "dri_def.h"

/*******************************************************************************
 * Typedef enums
 ******************************************************************************/

/* @brief: Pin MUX selection */
typedef enum
{
    PORT_PIN_DISABLED = 0U,  /* Pin disabled (Alternative 0) (analog) */
    PORT_MUX_ALT1     = 1U,  /* Alternative 1 (GPIO) */
    PORT_MUX_GPIO     = 1U,  /* Alternative 1 (GPIO) */
    PORT_MUX_ALT2     = 2U,  /* Chip-specific */
    PORT_MUX_ALT3     = 3U,  /* Chip-specific */
    PORT_MUX_ALT4     = 4U,  /* Chip-specific */
    PORT_MUX_ALT5     = 5U,  /* Chip-specific */
    PORT_MUX_ALT6     = 6U,  /* Chip-specific */
    PORT_MUX_ALT7     = 7U   /* Chip-specific */
} Port_Mux_t;

/*
 * @brief: Specifies values for setting the pull resistor
 */
typedef enum
{
    PORT_PULL_NONE = 0U,
    PORT_PULL_DOWN = 2U,
    PORT_PULL_UP   = 3U
} Port_Pull_Resistor_t;

/*
 * @brief: Specifies values for setting the event trigger
 */
typedef enum
{
    PORT_TRIGGER_NONE             = 0U,
    PORT_TRIGGER_DMA_RISING_EDGE  = 1U,
    PORT_TRIGGER_DMA_FALLING_EDGE = 2U,
    PORT_TRIGGER_DMA_EITHER_EDGE  = 3U,
    PORT_TRIGGER_LOGIC0           = 8U,
    PORT_TRIGGER_RISING_EDGE      = 9U,
    PORT_TRIGGER_FALLING_EDGE     = 10U,
    PORT_TRIGGER_EITHER_EDGE      = 11U,
    PORT_TRIGGER_LOGIC1           = 12U
} Port_Event_Trigger_t;

typedef enum
{
    PORT_LOW_DRIVER_STRENGTH  = 0U, /* Low-drive strength is configured. */
    PORT_HIGH_DRIVER_STRENGTH = 1U, /* High-drive strength is configured. */
} Port_Driver_Strength_t;

/*
 * @brief: PORT Init structure definition
 */
typedef struct
{
    Port_Mux_t              Mux;
    Port_Event_Trigger_t    Trigger;
    Port_Pull_Resistor_t    Pull;         /* Specifies the Pull-up or Pull-Down activation for the selected pins */
    Port_Driver_Strength_t  Strength;
} PORT_InitTypeDef;

/*
 * @name: DRI_PORT_SetPinMux
 * ----------------------------
 * @brief:     Configures the pin muxing
 * @param[out] PORTx: PORT peripheral base pointer
 * @param[in]  Pin: PORT pin number
 * @param[in]  MUX: Pin muxing slot selection
 * @return:    None
 */
static inline void DRI_PORT_SetPinMux(PORT_Type *const PORTx, const uint8_t Pin,
        const Port_Mux_t MUX)
{
    PORTx->PCR[Pin] = (PORTx->PCR[Pin] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(MUX);
}


/*
 * @name: DRI_PORT_SetPinPull
 * ----------------------------
 * @brief:     Configures the pin pulling
 * @param[out] PORTx: PORT peripheral base pointer
 * @param[in]  Pin: PORT pin number
 * @param[in]  PullType: Pin pulling slot selection
 * @return:    None
 */
static inline void DRI_PORT_SetPinPull(PORT_Type *const PORTx,
        const uint8_t Pin, const Port_Pull_Resistor_t PullType)
{
    PORTx->PCR[Pin] = (PORTx->PCR[Pin] & ~(PORT_PCR_PE_MASK | PORT_PCR_PS_MASK))
            | (PullType << PORT_PCR_PS_SHIFT);
}


/*
 * @name: DRI_PORT_SetEventTrigger
 * ----------------------------
 * @brief:     Configures the port pin interrupt/DMA request
 * @param[out] PORTx: PORT peripheral base pointer
 * @param[in]  Pin: PORT pin number
 * @param[in]  Trigger_Type: PORT pin interrupt configuration
 */
static inline void DRI_PORT_SetEventTrigger(PORT_Type *const PORTx,
        const uint8_t Pin, const Port_Event_Trigger_t Trigger_Type)
{
    PORTx->PCR[Pin] = (PORTx->PCR[Pin] & ~PORT_PCR_IRQC_MASK)
            | PORT_PCR_IRQC(Trigger_Type);
}

/*
 * @name: DRI_PORT_GetPinsInterruptFlags
 * ----------------------------
 * @brief:    Reads the Port interrupt status flag
 * @param[in] PORTx: PORT peripheral base pointer (PORTA, PORTB, PORTC, PORTD)
 * @return:   Current port interrupt status flags
 */
static inline uint32_t DRI_PORT_GetPinsInterruptFlags(
        const PORT_Type *const PORTx)
{
    return PORTx->ISFR;
}

/*
 * @name: DRI_PORT_ClearPinsInterruptFlags
 * ----------------------------
 * @brief: Clears the multiple pin interrupt status flag
 * @param[in] PORTx: PORT peripheral base pointer
 * @param[in] mask: PORT pin number macro
 */
static inline void DRI_PORT_ClearPinsInterruptFlags(PORT_Type *const PORTx,
        const uint32_t mask)
{
    PORTx->ISFR = mask;
}

/*
 * @name: DRI_PORT_SetPinDriveStrength
 * ----------------------------
 * @brief: Configures the port pin drive strength
 * @param[out] PORTx: PORT peripheral base pointer
 * @param[in]  Pin: PORT pin number
 * @param[in]  Strength: PORT pin drive strength
 */
static inline void DRI_PORT_SetPinDriveStrength(PORT_Type *const PORTx,
        const uint8_t Pin, const uint8_t Strength)
{
    PORTx->PCR[Pin] = (PORTx->PCR[Pin] & ~PORT_PCR_DSE_MASK)
            | PORT_PCR_DSE(Strength);
}

/*
 * @name: DRI_PORT_Pin_Init
 * ----------------------------
 * @brief: Initialize PORT pin
 * @param[out] PORTx: PORT peripheral base pointer
 * @param[in]  Pin: PORT pin number
 * @param[in]  PORT_Init: PORT PCR register configuration structure
 */
static inline void DRI_PORT_Pin_Init(PORT_Type *const PORTx, const uint8_t Pin,
        const PORT_InitTypeDef *const PORT_Init)
{
	PORTx->PCR[Pin] = (PORTx->PCR[Pin] & ~(PORT_PCR_MUX_MASK))
            | PORT_PCR_MUX(PORT_Init->Mux);
    PORTx->PCR[Pin] = (PORTx->PCR[Pin] & ~(PORT_PCR_IRQC_MASK))
            | PORT_PCR_IRQC(PORT_Init->Trigger);
    PORTx->PCR[Pin] = (PORTx->PCR[Pin] & ~(PORT_PCR_PE_MASK | PORT_PCR_PS_MASK))
            | ((PORT_Init->Pull) << PORT_PCR_PS_SHIFT);
    PORTx->PCR[Pin] = (PORTx->PCR[Pin] & ~(PORT_PCR_DSE_MASK))
            | PORT_PCR_DSE(PORT_Init->Strength);
}

#endif /* _INC_DRI_PORT_H_ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
