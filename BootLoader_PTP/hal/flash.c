/*
 * flash.c
 *
 *  Created on: May 17, 2024
 *      Author: jengp
 */


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "MKE16Z4.h"
#include "flash.h"


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/* Program Address and Data (32bit) into Flash Memory */
void Program_LongWord(uint32_t Addr, uint8_t *Data)
{
    __disable_irq();

    /* Wait previous CMD finish */
    while (FTFA->FSTAT == 0x00U);

    /* Clear previous CMD error */
    if(FTFA->FSTAT != 0x80U)
    {
        FTFA->FSTAT = 0x30U;
    }
    /* Program 4 bytes in a program flash block */
    FTFA->FCCOB0 = CMD_PROGRAM_LONGWORD;

    /* Fill Address */
    FTFA->FCCOB1 = (uint8_t)(Addr >> 16U);
    FTFA->FCCOB2 = (uint8_t)(Addr >> 8U);
    FTFA->FCCOB3 = (uint8_t)(Addr >> 0U);

    /* Fill Data */
    FTFA->FCCOB4 = (uint8_t)(Data[3U]);
    FTFA->FCCOB5 = (uint8_t)(Data[2U]);
    FTFA->FCCOB6 = (uint8_t)(Data[1U]);
    FTFA->FCCOB7 = (uint8_t)(Data[0U]);

    /* Clear CCIF */
    FTFA->FSTAT = 0x80U;
    /* Wait CMD finish */
    while (FTFA->FSTAT == 0x00U);

    __enable_irq();
}


uint8_t  Erase_Sector(const uint32_t Addr)
{
    /* Wait previous CMD finish */
    while (FTFA->FSTAT == 0x00U);

    /* Clear previous cmd error */
    if(FTFA->FSTAT != 0x80U)
    {
        FTFA->FSTAT = 0x30U;
    }
    /* Erase all bytes in a program flash sector */
    FTFA->FCCOB0 = CMD_ERASE_FLASH_SECTOR;

    /* Fill Address */
    FTFA->FCCOB1 = (uint8_t)(Addr >> 16U);
    FTFA->FCCOB2 = (uint8_t)(Addr >> 8U);
    FTFA->FCCOB3 = (uint8_t)(Addr >> 0U);

    /* Clear CCIF */
    FTFA->FSTAT = 0x80U;
    /* Wait CMD finish */
    while (FTFA->FSTAT == 0x00U);

    return 0U;
}


/* Erase all flash sector */
uint8_t  Erase_Multi_Sector(const uint32_t Addr, const uint32_t Size)
{
    uint8_t index;

    for(index = 0U; index < Size; index++)
    {
        Erase_Sector(Addr + index * 1024U);
    }

    return 0U;
}
