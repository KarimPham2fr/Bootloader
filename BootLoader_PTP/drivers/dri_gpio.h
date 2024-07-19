/*
 * dri_gpio.h
 *
 *  Created on: Apr 12, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

#ifndef _INC_DRI_GPIO_H_
#define _INC_DRI_GPIO_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "dri_def.h"
#include "dri_port.h"

/*******************************************************************************
 * Typedef datatype
 ******************************************************************************/
typedef uint8_t GPIO_Pin_t;

/*******************************************************************************
 * Typedef enums
 ******************************************************************************/

/*
 * @brief: GPIO Bit SET and Bit RESET enumeration
 */
typedef enum
{
    GPIO_PIN_RESET,
    GPIO_PIN_SET
} GPIO_Pin_State_t;


/*
 * @brief: Enumerates the modes of operation for GPIO pins
 */
typedef enum
{
    GPIO_INPUT,
    GPIO_OUTPUT
} GPIO_Direction_t;


/*******************************************************************************
 * Typedef structs
 ******************************************************************************/

/*
 * @brief: GPIO Init structure definition
 */
typedef struct
{
    GPIO_Direction_t     Direction;     /* Specifies the operating mode for the selected pins */
    GPIO_Pin_State_t     OutputLogic;   /* Default output logic */
} GPIO_InitTypeDef;

/*******************************************************************************
 * APIs
 ******************************************************************************/

/*
 * @name:      DRI_GPIO_TogglePin
 * ----------------------------
 * @brief:     Toggles the state of the specified pin
 * @param[out] GPIOx: Pointer to the GPIO port structure
 * @param[in]  Pin: Number of the pin to be toggled
 * @return:    DRIVER_OK if successful;
 *             DRIVER_ERROR if an error occurred
 * @note:      If GPIOx is NULL, the function does nothing
 */
DRI_StatusTypeDef DRI_GPIO_TogglePin(GPIO_Type *const GPIOx,
        const GPIO_Pin_t Pin);


/*
 * @name:      DRI_GPIO_WritePin
 * ----------------------------
 * @brief:     Sets the level of the specified pin
 * @param[out] GPIOx: Pointer to the GPIO port structure
 * @param[in]  Pin: Number of the pin to write to
 * @param[in]  State: State to write to the pin (GPIO_PIN_SET or GPIO_PIN_RESET)
 * @return:    DRIVER_OK if successful;
 *             DRIVER_ERROR if an error occurred
 * @note:      If GPIOx is NULL, the function does nothing
 */
DRI_StatusTypeDef DRI_GPIO_WritePin(GPIO_Type *const GPIOx,
        const GPIO_Pin_t Pin, const GPIO_Pin_State_t State);


/*
 * @name:      DRI_GPIO_ReadPin
 * ----------------------------
 * @brief:     Reads the level of the specified pin
 * @param[in]  GPIOx: Pointer to the GPIO port structure
 * @param[in]  Pin: Pin number to read the state from
 * @return:    The current state of the pin (GPIO_PIN_SET or GPIO_PIN_RESET)
 * @note:      None
 */
GPIO_Pin_State_t DRI_GPIO_ReadPin(const GPIO_Type *const GPIOx,
        const GPIO_Pin_t Pin);


/*
 * @name:      DRI_GPIO_Init
 * ----------------------------
 * @brief:     Initialize GPIO pin
 * @param[out] GPIOx: Pointer to the GPIO port to initialize
 * @param[in]  GPIO_Init: Pointer to the GPIO initialization structure
 * @return:    DRIVER_OK if successful;
 *             DRIVER_ERROR if an error occurred
 * @note:      This function initializes GPIO pins based on the provided configuration
 */
DRI_StatusTypeDef DRI_GPIO_Init(GPIO_Type *const GPIOx, const GPIO_Pin_t Pin,
        const GPIO_InitTypeDef *const GPIO_Init);


/*
 * @name:     DRI_GPIO_PortGetInterruptFlags
 * ----------------------------
 * @brief:    Reads the GPIO port interrupt status flag
 * @param[in] GPIOx: base GPIO peripheral base pointer (GPIOA, GPIOB, GPIOC, GPIOD)
 * @return    The current GPIO port interrupt status flag, for example, 0x00010001 means the
 *            pin 0 and 17 have the interrupt
 * @note:     None
 */
uint32_t DRI_GPIO_PortGetInterruptFlags(const GPIO_Type *const GPIOx);


/*
 * @name:     DRI_GPIO_PortClearInterruptFlags
 * ----------------------------
 * @brief:    Clears multiple GPIO pin interrupt status flags
 *
 * @param[in] GPIOx: GPIO peripheral base pointer (GPIOA, GPIOB, GPIOC, GPIOD)
 * @param[in] mask: GPIO pin number macro
 * @return    None
 * @note:     None
 */
void DRI_GPIO_PortClearInterruptFlags(const GPIO_Type *const GPIOx,
        const uint32_t mask);

#endif /* _INC_DRI_GPIO_H_ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
