/*
 * user_inform.c
 *
 *  Created on: May 11, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "user_inform.h"

/*******************************************************************************
 * Constants
 ******************************************************************************/
const static uint8_t arr_Starting_Message[] =
        "The boost loader process is ready. Please send user' application file!\r\n";
const static uint8_t arr_Error_Message[] =
        "\r\nError!\r\nThe boost process is failed.\r\nPress the switch to enter your previous application!\r\n";
const static uint8_t arr_Done_Message[] =
        "\r\nDone!\r\nPress the switch to enter your application!\r\n";

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void UI_inform(const uint8_t *const message, const uint8_t size)
{
    MID_TransmitData(message, size);
}


void UI_informStarting(void)
{
    MID_TransmitData(arr_Starting_Message, sizeof(arr_Starting_Message) - 1U);
}


void UI_informError(void)
{
    MID_TransmitData(arr_Error_Message, sizeof(arr_Error_Message) - 1U);
}


void UI_informSucess(void)
{
    MID_TransmitData(arr_Done_Message, sizeof(arr_Done_Message) - 1U);
}


/*******************************************************************************
 * EOF
 ******************************************************************************/
