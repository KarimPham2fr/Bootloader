/*
 * flash.h
 *
 *  Created on: May 17, 2024
 *      Author: jengp
 */

#ifndef _INC_FLASH_H_
#define _INC_FLASH_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define CMD_PROGRAM_LONGWORD     (0x06U)
#define CMD_ERASE_FLASH_SECTOR   (0x09U)

/*******************************************************************************
 * APIs
 ******************************************************************************/

/*
 * @brief
 * flash data input into flash
 * @param Addr: address to flash data to flash
 * @param *Data: input data need to flash data into flash
 * @return: None
 */
void Program_LongWord(uint32_t Addr, uint8_t *Data);


/*
 * @brief
 * erase a sector in flash
 * @param Addr: address to erase
 * @return
 * return 1: if success
 */
uint8_t Erase_Sector(const uint32_t Addr);

/*
 * @brief
 * erase multi sectors in flash
 * @param Addr: address to erase
 * @return
 * return 1: if success
 */
uint8_t Erase_Multi_Sector(const uint32_t Addr, const uint32_t Size);

#endif /* _INC_FLASH_H_ */
