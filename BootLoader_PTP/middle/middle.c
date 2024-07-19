/*
 * middle.c
 *
 *  Created on: May 11, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "middle.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
static CircularQueue_t g_srecQueue;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static uint32_t calculateAddress(const uint8_t *const p_LineSrec);
static void tempBuff(uint8_t *p_inBuff, uint8_t *p_outBuff);


/*
 * @name:  MID_Init
 * ------------------------------------
 * @brief: Initialize the middle layer of the SREC parser application from a SREC file
 */
void MID_Init(void)
{
    Queue_Init(&g_srecQueue);          /* Initialize the circular queue */
    HAL_Init();                        /* Initialize the LPUART layer */
    HAL_getFuncAddress(MID_PushData);  /* Pass the address of the function "MID_PushData" down to the HAL layer */
}


/*
 * @name:  MID_DeInit
 * ------------------------------------
 * @brief: De-initialize the middle layer of the SREC parser application from a SREC file
 */
void MID_DeInit(void)
{
    HAL_DeInit();
    Queue_DeInit(&g_srecQueue);
}


/*
 * @name:  MID_PushData
 * ------------------------------------
 * @brief: Push data into the circular queue
 */
int8_t MID_PushData(const uint8_t data)
{
    return Queue_enQueue(&g_srecQueue, data);
}


/*
 * @name:  MID_QueueIsEmpty
 * ------------------------------------
 * @brief: Check if the SREC circular queue is empty
 */
uint8_t MID_QueueIsEmpty(void)
{
    return Queue_isEmpty(&g_srecQueue);
}


/*
 * @name:  MID_deQueue
 * ------------------------------------
 * @brief: Remove a line from the circular queue
 */
void MID_deQueue(void)
{
    (void)Queue_deQueue(&g_srecQueue);
}


/*
 * @name:  MID_peekQueue
 * ------------------------------------
 * @brief: Retrieve the front element in the queue, without deleting it
 */
void* MID_peekQueue(void)
{
    return Queue_peekQueue(&g_srecQueue);
}


/*
 * @name:  MID_Parse_Record
 * ------------------------------------
 * @brief: Parse and validate an SREC record
 */
Srec_Status_t MID_Parse_Record(const uint8_t *const p_LineSrec)
{
    Srec_Status_t statusRecord = SREC_ERROR;

    if (p_LineSrec != NULL)
    {
        /* Start checking fields in the record */
        statusRecord = SREC_checkSyntax(p_LineSrec);
        if (statusRecord == SREC_OK)
        {
            statusRecord = SREC_CheckRecordStart(p_LineSrec);
            if (statusRecord == SREC_OK)
            {
                statusRecord = SREC_Checksum(p_LineSrec);
                if (statusRecord == SREC_OK)
                {
                    statusRecord = SREC_CheckByteCount(p_LineSrec);
                    if (statusRecord == SREC_OK)
                    {
                    	statusRecord = SREC_CheckRecordType(p_LineSrec);
                    }
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

    return statusRecord;
}


/*
 * @name:  MID_Write_Record
 * ------------------------------------
 * @brief: Write content of record into specific address in flash memory
 */
void MID_Write_dataRecord(uint8_t *const p_LineSrec)
{
    uint8_t  length      = 0U;
    uint32_t address     = 0U;
    uint8_t  index       = 0U;
    uint8_t  numberWords = 0U;
    uint8_t  tmpBuff[4U];

    length  = SREC_lengthLineSrec(p_LineSrec);
    address = calculateAddress(p_LineSrec);

    switch(p_LineSrec[1U])
    {
        case '1':
            numberWords = (length - 12U) / 8U;
            for (index = 0U; index < numberWords; ++index)
            {
                tempBuff(&p_LineSrec[8U + index * 8U], tmpBuff);
                Program_LongWord(address + index * 4U, tmpBuff);
            }
            break;

        case '2':
            numberWords = (length - 14U) / 8U;
            for (index = 0U; index < numberWords; ++index)
            {
                tempBuff(&p_LineSrec[10U + index * 8U], tmpBuff);
                Program_LongWord(address + index * 4U, tmpBuff);
            }
            break;

        case '3':
            numberWords = (length - 16U) / 8U;
            for (index = 0U; index < numberWords; ++index)
            {
                tempBuff(&p_LineSrec[12U + index * 8U], tmpBuff);
                Program_LongWord(address + index * 4U, tmpBuff);
            }
            break;

        default:
            /* Do Nothing */
            break;
    }
}


/*
 * @name:  MID_SetDataTransferRate
 * -----------------------------------
 * @brief: Set the baud rate for communication in the SREC parser
 */
void MID_SetDataTransferRate(const uint32_t baudrate)
{
    HAL_SetBaudrate(baudrate);
}


/*
 * @name:  MID_InitUserApplicationSpace
 * ------------------------------------
 * @brief: Initializes the user application space by erasing a specified region of flash memory
 */
uint8_t MID_InitUserApplicationSpace(const uint32_t startAddress, const uint32_t size)
{
    return HAL_eraseFlash(startAddress, size);
}


/*
 * @name:  MID_TransmitData
 * ----------------------------
 * @brief: Transmit data in the SREC parser
 */
void MID_TransmitData(const uint8_t *const data, const uint32_t size)
{
    HAL_TransmitData(data, size);
}


/*
 * @name:  MID_switchIsPressed
 * ----------------------------
 * @brief: Checks if the switch is pressed
 */
uint8_t MID_switchIsPressed(void)
{
    return HAL_switchIsPressed();
}


/*
 * @name:  MID_isQueueOverLoad
 * ----------------------------
 * @brief: Checks if the data queue is overloaded
 */
uint8_t MID_isQueueOverLoad(void)
{
    return HAL_pushDataFailed();
}


/*
 * @brief: Jumps to the application code located at the specified address
 */
void MID_jumpApplication(const uint32_t appAddress)
{
    HAL_jumpApplication(appAddress);
}


void MID_backupApplication(const uint32_t appAddress,
                           const uint32_t backupAddress,
                           const uint32_t appSize)
{
    HAL_eraseFlash(backupAddress, appSize);
    HAL_backupApplication(appAddress, backupAddress, appSize);
}


void MID_restoreApplication(const uint32_t restoreAddress,
                            const uint32_t backupAddress,
                            const uint32_t appSize)
{
    HAL_restoreApplication(restoreAddress, backupAddress, appSize);
    HAL_jumpApplication(restoreAddress);
}


static uint32_t calculateAddress(const uint8_t *const p_LineSrec)
{
    uint8_t  index  = 0U;
    uint32_t retVal = 0U;
    uint8_t  tmp    = 0U;

    if (NULL != p_LineSrec)
    {
        switch (p_LineSrec[1U])
        {
            case '1':
                tmp = 4U;
                break;

            case '2':
                tmp = 6U;
                break;

            case '3':
                tmp = 8U;
                break;
            default:
                /* Do Nothing */
                break;
        }

        for (index = 0U; index < tmp; ++index)
        {
            /* Convert the character-form numbers to corresponding integer-form numbers */
            retVal += ((p_LineSrec[index + 4U] >= 'A') ?
                            (p_LineSrec[index + 4U] - 'A' + 10U) :
                            (p_LineSrec[index + 4U] - '0')) << (4U * (tmp - index - 1U));
        }
    }
    else
    {
        retVal = 1U; /* Return an error status if the string to be converted is invalid */
    }

    return retVal;
}


static void tempBuff(uint8_t *p_inBuff, uint8_t *p_outBuff)
{
    p_outBuff[0U] = SREC_convertStrToDec(&p_inBuff[0U]);
    p_outBuff[1U] = SREC_convertStrToDec(&p_inBuff[2U]);
    p_outBuff[2U] = SREC_convertStrToDec(&p_inBuff[4U]);
    p_outBuff[3U] = SREC_convertStrToDec(&p_inBuff[6U]);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
