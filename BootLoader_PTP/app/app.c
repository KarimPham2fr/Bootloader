/*
 * app.c
 *
 *  Created on: May 10, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
static App_state_t g_state = DEFAULT;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*
 * @brief: Initialize the application
 */
void app_init(void)
{
    /*
        * Configure the baud rate here!
        */
    MID_SetDataTransferRate(115200U);
    /* Initialize the S-record parser layer */
    MID_Init();

    if (SWITCH_PRESSED == MID_switchIsPressed()) /* Start executing the bootloader process if the switch is pressed */
    {
        MID_backupApplication(USER_APPLICATION01_ADDRESS,
                                BACKUP_APPLICATION_ADDRESS,
                                USER_APPLICATION01_SIZE_SPACE);

        MID_InitUserApplicationSpace(USER_APPLICATION01_ADDRESS,
                                        USER_APPLICATION01_SIZE_SPACE);
        g_state = CHECK_QUEUE;
        /* Notify the users that the boost loader process is ready.
            * Users can start uploading their files */
        UI_informStarting();
    }

    else
    {
        MID_DeInit();
        /* If the switch isn't pressed, immediately jump to user's application */
        MID_jumpApplication(USER_APPLICATION01_ADDRESS);
    }
}


void app_process_action(void)
{
    static Srec_Status_t statusRecord       = SREC_ERROR;
    static uint8_t       checkEmpty         = FALSE;
    static uint8_t       checkOverLoad      = FALSE;
    static uint8_t       isTerminationExist = FALSE;
    static uint8_t       *p_LineSrec        = NULL;

    switch (g_state)
    {
        case CHECK_QUEUE:
            /* Check if there is data in the Queue */
            checkEmpty = MID_QueueIsEmpty();
            if (FALSE == checkEmpty)
            {
                /* Check if the queue is overloaded */
                checkOverLoad = MID_isQueueOverLoad();
                /* If the queue has data and is not overloaded, proceed to parse the record */
                if (FALSE == checkOverLoad)
                {
                    g_state = PASER_RECORD;
                }
                /* If the queue is overloaded, proceed to error notification and terminate the boost process */
                else
                {
                    g_state = ERROR;
                }
            }
            else
            {
                /* Continue waiting for data if the queue is empty */
            }
            break;

        case PASER_RECORD:
            /* Retrieve the next record from the queue (not remove it from queue) */
            p_LineSrec = (uint8_t*)MID_peekQueue();
            /* Parse the retrieved record */
            statusRecord = MID_Parse_Record(p_LineSrec);
            /* Check if the termination record exists */
            isTerminationExist = SREC_TerminationIsExist();
            /* If the record has no errors and is a data record, proceed to write
                * the content to the corresponding address in flash memory */
            if ((SREC_OK == statusRecord) && (FALSE == isTerminationExist))
            {
                g_state = WRITE_FLASH;
            }
            /* If a terminal record indicating the end of the file is encountered,
                * proceed to jump to the user's application */
            else if (TRUE == isTerminationExist)
            {
                g_state = JUMP_USER_APP;
            }
            /* If the record has an error, proceed to error notification and terminate the boost process*/
            else
            {
                g_state = ERROR;
            }
            break;

        case WRITE_FLASH:
            /* Write the content to the corresponding address in flash memory */
            MID_Write_dataRecord(p_LineSrec);
            /* Remove the record that was just written to flash from the circular queue */
            MID_deQueue();
            /* Continue checking the queue */
            g_state = CHECK_QUEUE;
            break;

        case JUMP_USER_APP:
            /* De-initialize the S-record parse layer */
            MID_DeInit();
            /* Inform the boost process is successful */
            UI_informSucess();
            while(MID_switchIsPressed())
            {
                /* Wait for the user to press the switch to enter the user's application */
            }
            /* Jump to the user's application */
            MID_jumpApplication(USER_APPLICATION01_ADDRESS);
            break;

        case ERROR:
            /* De-initialize the S-record parse layer */
            MID_DeInit();
            /* Send "Error" message */
            UI_informError();
            while(MID_switchIsPressed())
            {
                /* Wait for the user to press the switch to enter the previous user's application */
            }
            MID_restoreApplication(USER_APPLICATION01_ADDRESS,
                                    BACKUP_APPLICATION_ADDRESS,
                                    USER_APPLICATION01_SIZE_SPACE);
            break;

        default:
            /*Do Nothing */
            break;
    }
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
