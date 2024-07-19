/*
 * dri_gpio.c
 *
 *  Created on: Apr 12, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "dri_gpio.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*
 * @name:  DRI_GPIO_TogglePin
 * ----------------------------
 * @brief: Toggles the state of the specified pin
 */
DRI_StatusTypeDef DRI_GPIO_TogglePin(GPIO_Type *const GPIOx,
        const GPIO_Pin_t Pin)
{
    DRI_StatusTypeDef reVal = DRIVER_OK;

    if (GPIOx != NULL)
    {
        SET_BIT(GPIOx->PTOR, Pin);
    }
    else
    {
        reVal = DRIVER_ERROR;
    }

    return reVal;
}


/*
 * @name:  DRI_GPIO_WritePin
 * ----------------------------
 * @brief: Sets the level of the specified pin
 */
DRI_StatusTypeDef DRI_GPIO_WritePin(GPIO_Type *const GPIOx,
        const GPIO_Pin_t Pin, const GPIO_Pin_State_t State)
{
    DRI_StatusTypeDef reVal = DRIVER_OK;

    if (GPIOx != NULL)
    {
        if (State == GPIO_PIN_SET)
        {
            SET_BIT(GPIOx->PSOR, Pin);
        }
        else
        {
            SET_BIT(GPIOx->PCOR, Pin);
        }
    }
    else
    {
        reVal = DRIVER_ERROR;
    }

    return reVal;
}


/*
 * @name:  DRI_GPIO_ReadPin
 * ----------------------------
 * @brief: Reads the level of the specified pin
 */
GPIO_Pin_State_t DRI_GPIO_ReadPin(const GPIO_Type *const GPIOx,
        const GPIO_Pin_t Pin)
{
    GPIO_Pin_State_t State = GPIO_PIN_RESET;

    if (GPIO_PIN_SET == READ_BIT(GPIOx->PDIR, Pin))
    {
        State = GPIO_PIN_SET;
    }
    else
    {
        State = GPIO_PIN_RESET;
    }

    return State;
}


/*
 * @name:  DRI_GPIO_Init
 * ----------------------------
 * @brief: Initialize GPIO pin
 */
DRI_StatusTypeDef DRI_GPIO_Init(GPIO_Type *const GPIOx, const GPIO_Pin_t Pin,
        const GPIO_InitTypeDef *const GPIO_Init)
{
    DRI_StatusTypeDef reVal = DRIVER_OK;

    if ((GPIOx != NULL) && (GPIO_Init != NULL))
    {
        /* Setup input or output mode */
        if (GPIO_Init->Direction == GPIO_OUTPUT)
        {
            SET_BIT(GPIOx->PDDR, Pin);                                   /* Setup as output mode */
            (void)DRI_GPIO_WritePin(GPIOx, Pin, GPIO_Init->OutputLogic); /* Setup default output logic */
        }
        else
        {
            CLEAR_BIT(GPIOx->PDDR, Pin);                                 /* Setup as input mode */
        }
    }
    else
    {
        reVal = DRIVER_ERROR;
    }

    return reVal;
}


/*
 * @name:  DRI_GPIO_PortGetInterruptFlags
 * ----------------------------
 * @brief: Reads the GPIO port interrupt status flag
 */
uint32_t DRI_GPIO_PortGetInterruptFlags(const GPIO_Type *const GPIOx)
{
    uint32_t retVal = 0;

    switch ((uint32_t)GPIOx)
    {
        case (uint32_t)GPIOA:
            retVal = PORTA->ISFR;
            break;

        case (uint32_t)GPIOB:
            retVal = PORTB->ISFR;
            break;

        case (uint32_t)GPIOC:
            retVal = PORTC->ISFR;
            break;

        case (uint32_t)GPIOD:
            retVal = PORTD->ISFR;
            break;

        default:
            /* Do Nothing */
            break;
    }

    return retVal;
}


/*
 * @name:  DRI_GPIO_PortClearInterruptFlags
 * ----------------------------
 * @brief: Clears multiple GPIO pin interrupt status flags
 */
void DRI_GPIO_PortClearInterruptFlags(const GPIO_Type *const GPIOx,
        const uint32_t mask)
{
    switch ((uint32_t)GPIOx)
    {
        case (uint32_t)GPIOA:
            PORTA->ISFR = mask;
            break;

        case (uint32_t)GPIOB:
            PORTB->ISFR = mask;
            break;

        case (uint32_t)GPIOC:
            PORTC->ISFR = mask;
            break;

        case (uint32_t)GPIOD:
            PORTD->ISFR = mask;
            break;

        default:
            /* Do Nothing */
            break;
    }
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
