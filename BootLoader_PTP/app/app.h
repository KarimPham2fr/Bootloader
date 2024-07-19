/*
 * app.h
 *
 *  Created on: May 11, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

#ifndef _INC_APP_H_
#define _INC_APP_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "user_inform.h"
#include "middle.h"
#include "flash.h"

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define USER_APPLICATION01_ADDRESS       0x8000U
#define BACKUP_APPLICATION_ADDRESS       0xC000U
#define USER_APPLICATION01_SIZE_SPACE    4U       /* 4kB */

/*******************************************************************************
 * Typedef enums
 ******************************************************************************/
typedef enum
{
    DEFAULT,
    CHECK_QUEUE,
    PASER_RECORD,
    ERROR,
    JUMP_USER_APP,
    WRITE_FLASH,
    BACKUP,
} App_state_t;

/*******************************************************************************
 * APIs
 ******************************************************************************/

/*
 * @brief: Initialize the application
 */
void app_init(void);


/*
 * @brief: Process actions in the application
 */
void app_process_action(void);

#endif /* _INC_APP_H_ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
