/*
 * Queue.c
 *
 *  Created on: May 10, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Queue.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*
 * @name:  Queue_Init
 * ----------------------------
 * @brief: Initialize a circular queue
 */
void Queue_Init(CircularQueue_t *const Queue)
{
    uint8_t  row  = 0U;
    uint32_t col  = 0U;

    if (NULL != Queue)
    {
        Queue->front    = -1;
        Queue->rear     = -1;
        Queue->capacity = 0U;
        Queue->size     = QUEUE_MAX_SIZE;
        for (row = 0U; row < QUEUE_MAX_SIZE; ++row)
        {
            for (col = 0U; col < LINE_MAX_CHAR; ++col)
            {
                Queue->QueueArr[row][col] = 0U;
            }
        }
    }
    else
    {

    }
}


/*
 * @name:      Queue_DeInit
 * ----------------------------
 * @brief:     De-initialize the circular queue
 * @param[out] Queue: Pointer to the circular queue structure
 * @return:    None
 */
void Queue_DeInit(CircularQueue_t *const Queue)
{
    if (NULL != Queue)
    {
        Queue->front    = -1;
        Queue->rear     = -1;
        Queue->size     = 0U;
        Queue->capacity = 0U;
    }
    else
    {
        /* Do Nothing */
    }
}


/*
 * @name:  Queue_isFull
 * ----------------------------
 * @brief: Check if the circular queue is full
 */
uint8_t Queue_isFull(const CircularQueue_t *const Queue)
{
    uint8_t status = FALSE;

    if (NULL != Queue)
    {
        if (Queue->capacity == Queue->size)
        {
            status = TRUE;
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Do Nothing */
    }

    return status;
}


/*
 * @name: Queue_isEmpty
 * ----------------------------
 * @brief: Check if the circular queue is empty
 */
uint8_t Queue_isEmpty(const CircularQueue_t *const Queue)
{
    uint8_t status = FALSE;

    if (NULL != Queue)
    {
        if (Queue->capacity == 0U)
        {
            status = TRUE;
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Do Nothing */
    }

    return status;
}


/*
 * @name:  Queue_enQueue
 * ----------------------------
 * @brief: Enqueue a byte into the circular queue
 */
int8_t Queue_enQueue(CircularQueue_t *const Queue, const uint8_t byteData)
{
    static uint16_t s_col = 0U;
    static uint8_t  s_row = 0U;
    int8_t retVal         = 0U;

    if (NULL != Queue)
    {
        /* The row which the new byte will be stored */
        s_row = (Queue->rear + 1U) % (Queue->size);

        if (!Queue_isFull(Queue))
        {
            Queue->QueueArr[s_row][s_col++] = byteData; /* Enqueue the byte into the queue */
            if (byteData == 0x0A) /* Check if receive the new line char ('\n') */
            {
                Queue->capacity++;
                s_col = 0U; /* Reset the column index to 0 */
                Queue->rear = (Queue->rear + 1U) % Queue->size; /* Update the rear index */
            }

            /* If this condition is true, it means there is one element in the queue.
             * Therefore update the front to 0 */
            if ((-1 == Queue->front) && (Queue->rear == 0U))
            {
                Queue->front = 0U; /* Front = rear = 0 informs there is a element in the queue */
            }
        }
        else
        {
            retVal = 1U;
        }
    }
    else
    {
        retVal = 1U;
    }

    return retVal;
}

/*
 * @name:  Queue_deQueue
 * ----------------------------
 * @brief: Dequeue a line from the circular queue
 */
void* Queue_deQueue(CircularQueue_t *const Queue)
{
    void *lineAddress = NULL;

    if (NULL != Queue)
    {
        if (!Queue_isEmpty(Queue))
        {
            lineAddress = &(Queue->QueueArr[Queue->front][0U]);
            Queue->front = (Queue->front + 1U) % Queue->size;
            NVIC_DisableIRQ(LPUART0_IRQn);           /* Disable interrupt */
            Queue->capacity--;
            NVIC_EnableIRQ(LPUART0_IRQn);           /*  Enable interrupt again */
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Do Nothing */
    }

    return lineAddress;
}


/*
 * @name:  Queue_peekQueue
 * ----------------------------
 * @brief:
 */
void* Queue_peekQueue(CircularQueue_t *const Queue)
{
    void *lineAddress = NULL;

    if (NULL != Queue)
    {
        if (!Queue_isEmpty(Queue))
        {
            lineAddress = &(Queue->QueueArr[Queue->front][0U]);
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Do Nothing */
    }

    return lineAddress;
}
/*******************************************************************************
 * EOF
 ******************************************************************************/
