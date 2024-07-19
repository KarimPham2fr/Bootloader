/*
 * Queue.h
 *
 *  Created on: May 10, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

#ifndef _INC_QUEUE_H_
#define _INC_QUEUE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include "MKE16Z4.h"
#include "dri_def.h"

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define QUEUE_MAX_SIZE         4U
#define LINE_MAX_CHAR          100U

/*******************************************************************************
 * Typedef structs
 ******************************************************************************/

typedef struct
{
    int8_t  front;
    int8_t  rear;
    int8_t  size;
    uint8_t capacity;
    uint8_t QueueArr[QUEUE_MAX_SIZE][LINE_MAX_CHAR];
} CircularQueue_t;

/*******************************************************************************
 * APIs
 ******************************************************************************/

/*
 * @name:      Queue_Init
 * ----------------------------
 * @brief:     Initialize a circular queue
 * @param[out] Queue: Pointer to the circular queue structure to be initialized
 * @return:    None
 * @note:      None
 */
void Queue_Init(CircularQueue_t *const Queue);


/*
 * @name:      Queue_Init
 * ----------------------------
 * @brief:     De-initialize the circular queue
 * @param[out] Queue: Pointer to the circular queue structure
 * @return:    None
 */
void Queue_DeInit(CircularQueue_t *const Queue);



/*
 * @name:      Queue_isFull
 * ----------------------------
 * @brief:     Check if the circular queue is full
 * @param[out] Queue: Pointer to the circular queue structure to be checked
 * @return:    TRUE if the queue is full, FALSE otherwise
 * @note:      None
 */
uint8_t Queue_isFull(const CircularQueue_t *const Queue);


/*
 * @name:      Queue_isEmpty
 * ----------------------------
 * @brief:     Check if the circular queue is empty
 * @param[out] Queue: Pointer to the circular queue structure to be checked
 * @return:    TRUE if the queue is empty, FALSE otherwise
 * @note:      None
 */
uint8_t Queue_isEmpty(const CircularQueue_t *const Queue);


/*
 * @name:      Queue_enQueue
 * ----------------------------
 * @brief:     Enqueue a byte into the circular queue
 * @param[out] Queue: Pointer to the circular queue structure
 * @param[in]: byteData: The byte of data to be added to the queue
 * @return:    None
 * @note:      None
 */
int8_t Queue_enQueue(CircularQueue_t *const Queue, const uint8_t byteData);


/*
 * @name:      Queue_deQueue
 * ----------------------------
 * @brief:     Dequeue a line from the circular queue
 * @param[out] Queue: Pointer to the circular queue structure
 * @return:    Pointer to the address of the dequeued line. Returns NULL if the queue is empty
 * @note:      None
 */
void* Queue_deQueue(CircularQueue_t *const Queue);


/*
 * @name:  Queue_peekQueue
 * ----------------------------
 * @brief:
 */
void* Queue_peekQueue(CircularQueue_t *const Queue);

#endif /* _INC_QUEUE_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
