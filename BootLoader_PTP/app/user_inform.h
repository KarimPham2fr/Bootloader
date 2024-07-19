/*
 * user_inform.h
 *
 *  Created on: May 11, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

#ifndef _INC_USER_INFORM_H_
#define _INC_USER_INFORM_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "middle.h"

/*******************************************************************************
 * APIs
 ******************************************************************************/
void UI_inform(const uint8_t *const message, const uint8_t size);

void UI_informStarting(void);

void UI_informError(void);

void UI_informSucess(void);

#endif /* _INC_USER_INFORM_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
