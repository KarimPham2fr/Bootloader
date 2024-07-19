/*
 * Srec.c
 *
 *  Created on: May 10, 2024
 *      Author: Phong Pham-Thanh
 *      Email:  Phong.PT.HUST@gmail.com
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Srec.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint8_t S_record_Termination = FALSE; /* Indicates the encounter of an EOF (End of File)
                                             record (Start Address (Termination))*/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*
 * @name:  SREC_checkSyntax
 * ----------------------------
 * @brief: Check the syntax of an SREC record line.
 *         This function verifies if the provided SREC record line contains valid characters.
 *         It checks whether each character in the line is either a digit ('0' to '9') or a hexadecimal digit ('A' to 'F').
 */
Srec_Status_t SREC_checkSyntax(const uint8_t *const srecLine)
{
    Srec_Status_t status = SREC_OK;
    uint8_t       index  = 1U;
    uint8_t       length = 0U;

    if (srecLine != NULL)
    {
        length = SREC_lengthLineSrec(srecLine) - 2U;

        for(index = 1U; index < length; ++index)
        {
            if (!(((srecLine[index] >= '0') && (srecLine[index] <= '9'))
                    || ((srecLine[index] >= 'A') && (srecLine[index] <= 'F'))))
                    {
                        index  = length; /*Break out the loop*/
                        status = SREC_ERROR;
                    }
                    else
                    {
                        /* Do Nothing */
                    }
        }
    }
    else
    {
        status = SREC_ERROR;
    }

    return status;
}


/*
 * @name:  SREC_Checksum
 * ----------------------------
 * @brief: Calculate and verify the checksum of an SREC record
 */
Srec_Status_t SREC_Checksum(const uint8_t *const srecLine)
{
    Srec_Status_t status   = SREC_OK;
    uint8_t       sum      = 0U;
    uint8_t       index    = 0U;
    uint8_t       checkSum = 0U;
    uint8_t       length   = 0U;
    uint8_t       tmp      = 0U;

    if (NULL != srecLine)
    {
        length = SREC_lengthLineSrec(srecLine);
        tmp    = (length - 6U) / 2U;

        for (index = 1U; index <= tmp; ++index)
        {
            sum += SREC_convertStrToDec(&srecLine[(2U * index)]);
        }

        checkSum = SREC_convertStrToDec(&srecLine[(length - 4U)]);

        ((uint8_t)(~sum) == checkSum) ? (status = SREC_OK) : (status = SREC_ERROR);
    }
    else
    {
        status = SREC_ERROR;
    }

    return status;
}


/*
 * @name:  SREC_CheckByteCount
 * ----------------------------
 * @brief: Check the byteCount field of an SREC record
 */
Srec_Status_t SREC_CheckByteCount(const uint8_t *const srecLine)
{
    Srec_Status_t status       = SREC_ERROR;
    uint8_t       byteCount    = 0U;
    uint8_t       byteCountCal = 0U;

    if (NULL != srecLine)
    {
        byteCount    = SREC_convertStrToDec(&srecLine[2U]) * 2U;
        byteCountCal = SREC_lengthLineSrec(srecLine) - 6U;
        (byteCount == byteCountCal) ? (status = SREC_OK) : (status = SREC_ERROR);
    }
    else
    {
        status = SREC_ERROR;
    }

    return status;
}


/*
 * @name: SREC_CheckRecordStart
 * ----------------------------
 * @brief: Check the start field of an SREC record
 */
Srec_Status_t SREC_CheckRecordStart(const uint8_t *const srecLine)
{
    Srec_Status_t status = SREC_ERROR;

    if (NULL != srecLine)
    {
        (srecLine[0U] == 'S') ? (status = SREC_OK) : (status = SREC_ERROR);
    }
    else
    {
        status = SREC_ERROR;
    }

    return status;
}


/*
 * @name:  SREC_CheckRecordStart
 * ----------------------------
 * @brief: Check the recordType field of an SREC record
 */
Srec_Status_t SREC_CheckRecordType(const uint8_t *const srecLine)
{
    Srec_Status_t status = SREC_ERROR;

    if (NULL != srecLine)
    {
        switch (srecLine[1U])
        {
            case '0':  /* Header */
            case '1':  /* Data */
            case '2':  /* Data */
            case '3':  /* Data */
            case '5':  /* Count */
            case '6':  /* Count */
                status = SREC_OK;
                break;
            case '7':  /* Start Address (Termination) */
            case '8':  /* Start Address (Termination) */
            case '9':  /* Start Address (Termination) */
                S_record_Termination = TRUE; /* Inform met record EOF (Start Address (Termination)) */
                status = SREC_OK;
                break;

            default:
                status = SREC_ERROR;
                break;
        }
    }
    else
    {
        status = SREC_ERROR;
    }

    return status;
}


/*
 * @brief: Check if an Termination record exists.
 * @return: 1 if an Termination record exists, otherwise 0.
 */
uint8_t SREC_TerminationIsExist(void)
{
    return S_record_Termination;
}

/*
 * @name:  SREC_convertStrToDec
 * ----------------------------
 * @brief: Convert the first two characters of a string to an integer in decimal format
 */
int32_t SREC_convertStrToDec(const uint8_t* Str)
{
    uint8_t index  = 0U;
    int32_t retVal = 0U;

    if (Str != NULL)
    {
        for (index = 0U; index < 2U; ++index)
        {
            /* Convert the character-form numbers to corresponding integer-form numbers */
            retVal += ((Str[index] >= 'A') ? (Str[index] - 'A' + 10U) : (Str[index] - '0')) << (4U * (1U - index));
        }
    }
    else
    {
        retVal = -1; /* Return an error status if the string to be converted is invalid */
    }

    return retVal;
}


/*
 * @name:  SREC_lengthLineSrec
 * ----------------------------
 * @brief: Calculate the length of a line in SREC format
 */
size_t SREC_lengthLineSrec(const uint8_t *str)
{
    size_t length = 0U;

    while (*str != '\n')
    {
        length++;
        str++;
    }

    return (++length);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
