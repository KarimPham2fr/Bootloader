/*
 * hal.h
 *
 *  Created on: May 11, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

#ifndef _INC_HAL_H_
#define _INC_HAL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "dri_gpio.h"
#include "dri_lpuart.h"
#include "flash.h"
#include <math.h>

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define BUTTON03_PORT         PORTD
#define BUTTON03_GPIO         GPIOD
#define BUTTON03_PIN          2U

#define LPUART0_SDA_RX_PORT   PORTB
#define LPUART0_SDA_RX_PIN    0U

#define LPUART0_SDA_TX_PORT   PORTB
#define LPUART0_SDA_TX_PIN    1U

#define SWITCH_PRESSED        0U
/*******************************************************************************
 * Typedefs
 ******************************************************************************/
typedef int8_t (*funcMid)(const uint8_t);

/*******************************************************************************
 * APIs
 ******************************************************************************/

/*
 * @brief:  Initializes the hardware abstraction layer (HAL)
 * @param:  None
 * @return: None
 */
void HAL_Init(void);


/*
 * @brief:  De-initializes the hardware abstraction layer (HAL)
 * @param:  None
 * @return: None
 */
void HAL_DeInit(void);


/*
 * @brief:    Sets the address of a function from a higher layer in the system
 * @param[in] funcAddress The address of the function to be set
 * @return:   0 if the function address is successfully set, 1 if the input address is NULL
 */
uint8_t HAL_getFuncAddress(const void *const funcAddress);


/*
 * @brief:    Transmits data via the LPUART0 peripheral
 * @param[in] data: Pointer to the data buffer to be transmitted
 * @param[in] size: Size of the data buffer to be transmitted
 * @return:   None
 */
void HAL_TransmitData(const uint8_t *const data, const uint32_t size);


/*
 * @brief:    Sets the baud rate used for communication in the HAL layer
 * @param[in] baud rate: The baud rate to be set
 * @return:   None
 */
void HAL_SetBaudrate(const uint32_t baudrate);


/*
 * @brief:
 * @param[in] startAddress: The starting address in flash memory for the erase operation
 * @param[in] size: The number of sector to be erased
 * @return:   0 for success, non-zero for error
 */
uint8_t HAL_eraseFlash(const uint32_t startAddress, const uint32_t size);


/*
 * @brief:  Checks the state of the specified button
 * @param:  None
 * @return: 0 if the button is pressed, 1 if it is not pressed
 */
uint8_t HAL_switchIsPressed(void);


/*
 * @brief:  Returns the status of the data push operation to the queue
 * @return: 1 if the data push to the queue failed, 0 if it succeeded
 */
uint8_t HAL_pushDataFailed(void);


/*
 * @brief:  Jumps to the application code located at the specified address
 * @detail: This function disables interrupts, clears pending interrupt requests, sets the vector table offset,
 *          sets the main stack pointer, and jumps to the entry point of the user's application code
 * @param[in] appAddress: The starting address of the application code
 * @return: None
 */
void HAL_jumpApplication(const uint32_t appAddress);


void HAL_backupApplication(const uint32_t appAddress,
                           const uint32_t backupAddress,
                           const uint32_t appSize);


void HAL_restoreApplication(const uint32_t restoreAddress,
                            const uint32_t backupAddress,
                            const uint32_t appSize);

#endif /* _INC_HAL_H_ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
