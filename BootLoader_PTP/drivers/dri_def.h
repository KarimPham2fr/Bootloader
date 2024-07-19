/*
 * dri_def.h
 *
 *  Created on: Apr 12, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

#ifndef _INC_DRI_DEF_H_
#define _INC_DRI_DEF_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "MKE16Z4.h"
#include <stdlib.h>

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define SET_BIT(REG, BITn)                       (REG |= (1U << BITn))  /* Set the nth bit in the register to 1 */
#define CLEAR_BIT(REG, BITn)                     (REG &= ~(1U << BITn)) /* Clear the nth bit in the register to 0 */
#define READ_BIT(REG, BITn)                      ((REG >> BITn) & 1U)   /* Read the nth bit state in the register */
#define FALSE                                    (0U)
#define TRUE                                     (1U)

/*******************************************************************************
 * Typedef enums
 ******************************************************************************/

/*
 * @brief  DRI Status structures definition
 */
typedef enum
{
    DRIVER_OK                = 0x00U,
    DRIVER_ERROR             = 0x01U,
    DRIVER_ERROR_BUSY        = 0x02U,
    DRIVER_ERROR_TIMEOUT     = 0x03U,
    DRIVER_ERROR_UNSUPPORTED = 0X04U,
    DRIVER_ERROR_PARAMETER   = 0x05U,
    DRIVER_ERROR_SPECIFIC    = 0x06U
} DRI_StatusTypeDef;

#endif /* _INC_DRI_DEF_H_ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
