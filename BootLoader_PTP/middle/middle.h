/*
 * middle.h
 *
 *  Created on: May 11, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

#ifndef _INC_MIDDLE_H_
#define _INC_MIDDLE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Queue.h"
#include "Srec.h"
#include "hal.h"

/*******************************************************************************
 * APIs
 ******************************************************************************/

/*
 * @name: MID_Init
 * ----------------------------
 * @brief:  Initialize the middle layer of the SREC parser application from a SREC file
 * @param:  None
 * @return: None
 */
void MID_Init(void);


/*
 * @name: MID_DeInit
 * ----------------------------
 * @brief:  De-initialize the middle layer of the SREC parser application from a SREC file
 * @param:  None
 * @return: None
 */
void MID_DeInit(void);


/*
 * @name: MID_PushData
 * ----------------------------
 * @brief:     Push data into the circular queue
 * @param[in]: The byte of data to be added to the circular queue
 * @return:    0 if the data is successfully pushed into the queue, 1 if the queue is full
 */
int8_t MID_PushData(const uint8_t data);


/*
 * @name: MID_Parse_Record
 * ----------------------------
 * @brief:  Parse and validate an SREC record
 * @param:  None
 * @return: SREC_OK if the SREC record is valid, an appropriate error status code otherwise
 */
Srec_Status_t MID_Parse_Record(const uint8_t *const p_LineSrec);


/*
 * @name: MID_QueueIsEmpty
 * ----------------------------
 * @brief:  Check if the SREC circular queue is empty
 * @param:  None
 * @return: TRUE if the SREC circular queue is empty, FALSE otherwise
 */
uint8_t MID_QueueIsEmpty(void);


/*
 * @name: MID_deQueue
 * ------------------------------------
 * @brief:  Remove a line from the circular queue
 * @param:  None
 * @return: None
 */
void MID_deQueue(void);


/*
 * @name: MID_peekQueue
 * ------------------------------------
 * @brief:  Retrieve the front element in the queue, without deleting it
 * @param:  None
 * @return: A pointer to the front element of the queue, or NULL if the queue is empty
 */
void* MID_peekQueue(void);


/*
 * @name: MID_Write_Record
 * ----------------------------
 * @brief: Write content of record into specific address in flash memory
 * @param[in] p_LineSrec: Pointer to the S-record line to be processed
 * @return:   None
 */
void MID_Write_dataRecord(uint8_t *const p_LineSrec);


/*
 * @name: MID_switchIsPressed
 * ----------------------------
 * @brief:  Checks if the switch is pressed
 * @param:  None
 * @return: 0 if the switch is pressed, 1 if it is not pressed
 */
uint8_t MID_switchIsPressed(void);


/*
 * @name: MID_isQueueOverLoad
 * ----------------------------
 * @brief:  Checks if the data queue is overloaded
 * @detail: This function delegates the check for queue overload status to
 *          the HAL layer and returns the result
 * @param:  None
 * @return: 1 if the data queue is overloaded (push data failed), 0 if it is not overloaded
 */
uint8_t MID_isQueueOverLoad(void);

/*
 * @name: MID_TransmitData
 * ----------------------------
 * @brief:    Transmit data in the SREC parser
 * @param[in] data: Pointer to the data buffer to be transmitted
 * @param[in] size: Size of the data buffer to be transmitted
 * @return:   None
 */
void MID_TransmitData(const uint8_t *const data, const uint32_t size);


/*
 * @name: MID_SetDataTransferRate
 * ----------------------------
 * @brief:    Set the baud rate for communication in the SREC parser
 * @param[in] baudrate: The baud rate to be set
 * @return:   None
 */
void MID_SetDataTransferRate(const uint32_t baudrate);


/*
 * @name:  MID_InitUserApplicationSpace
 * ------------------------------------
 * @brief: Initializes the user application space by erasing a specified region of flash memory
 * @param[in] startAddress: The starting address in flash memory where the erase operation will begin
 * @param[in] size: The number of sector to be erased
 * @return: 0 for success, non-zero for error
 */
uint8_t MID_InitUserApplicationSpace(const uint32_t startAddress, const uint32_t size);


/*
 * @brief: Jumps to the application code located at the specified address
 * @param[in] appAddress: The starting address of the application code
 * @return:   None
 */
void MID_jumpApplication(const uint32_t appAddress);


void MID_backupApplication(const uint32_t appAddress,
                          const uint32_t backupAddress,
                          const uint32_t appSize);


void MID_restoreApplication(const uint32_t restoreAddress,
                           const uint32_t backupAddress,
                           const uint32_t appSize);

#endif /* _INC_MIDDLE_H_ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
