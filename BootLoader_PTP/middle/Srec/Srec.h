/*
 * Srec.h
 *
 *  Created on: May 10, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

#ifndef _INC_SREC_H_
#define _INC_SREC_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "Queue.h"

/*******************************************************************************
 * Typedef enums
 ******************************************************************************/

/*
 * @brief: Enumeration defining status codes for SREC operations
 */
typedef enum
{
    SREC_ERROR = 0U,
    SREC_OK,
} Srec_Status_t;

/*******************************************************************************
 * APIs
 ******************************************************************************/

/*
 * @name:  SREC_checkSyntax
 * ----------------------------
 * @brief: Check the syntax of an SREC record line.
 *         This function verifies if the provided SREC record line contains valid characters.
 *         It checks whether each character in the line is either a digit ('0' to '9') or a hexadecimal digit ('A' to 'F').
 * @param[in] srecLine: Pointer to the SREC record line to be checked.
 * @return: SREC_OK if the syntax is correct, otherwise SREC_ERROR.
 */
Srec_Status_t SREC_checkSyntax(const uint8_t *const srecLine);


/*
 * @name:      SREC_Checksum
 * ----------------------------
 * @brief:     Calculate and verify the checksum of an SREC record
 * @param[in]: srecLine: Pointer to the SREC record whose checksum needs to be verified
 * @return:    SREC_OK if the checksum is valid, SREC_ERROR otherwise
 * @note:      None
 */
Srec_Status_t SREC_Checksum(const uint8_t *const srecLine);


/*
 * @name:      SREC_CheckByteCount
 * ----------------------------
 * @brief:     Check the byteCount field of an SREC record
 * @param[in]: srecLine: Pointer to the SREC record whose checksum needs to be verified
 * @return:    SREC_OK if the byteCount is valid, SREC_ERROR otherwise
 * @note:      None
 */
Srec_Status_t SREC_CheckByteCount(const uint8_t *const srecLine);


/*
 * @name:      SREC_CheckRecordStart
 * ----------------------------
 * @brief:     Check the start field of an SREC record
 * @param[in]: srecLine: Pointer to the SREC record whose checksum needs to be verified
 * @return:    SREC_OK if the start field is valid, SREC_ERROR otherwise
 * @note:      None
 */
Srec_Status_t SREC_CheckRecordStart(const uint8_t *const srecLine);


/*
 * @name:      SREC_CheckRecordType
 * ----------------------------
 * @brief:     Check the recordType field of an SREC record
 * @param[in]: srecLine: Pointer to the SREC record whose checksum needs to be verified
 * @return:    SREC_OK if the record type is valid, SREC_ERROR otherwise
 * @note:      None
 */
Srec_Status_t SREC_CheckRecordType(const uint8_t *const srecLine);


/*
 * @brief: Check if an Termination record exists.
 * @return: 1 if an Termination record exists, otherwise 0.
 */
uint8_t SREC_TerminationIsExist(void);


/*
 * @name:      SREC_lengthLineSrec
 * ----------------------------
 * @brief:     Calculate the length of a line in SREC format
 * @param[in]  str: Pointer to the line in SREC format whose length needs to be calculated
 * @return:    The length of the line (number of characters), excluding the newline character
 * @note:      None
 */
size_t SREC_lengthLineSrec(const uint8_t *str);

/*
 * @name:      SREC_convertStrToDec
 * ----------------------------
 * @brief:     Convert the first two characters of a string to an integer in decimal format
 * @param[in]  Str: Pointer to the string containing the characters to be converted
 * @return:    The converted integer value if successful, -1 if the input string is invalid
 * @note:      None
 */
int32_t SREC_convertStrToDec(const uint8_t* Str);

#endif /* _INC_SREC_H_ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
