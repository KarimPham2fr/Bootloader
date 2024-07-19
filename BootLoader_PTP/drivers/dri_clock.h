/*
 * dri_clock.h
 *
 *  Created on: Apr 12, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

#ifndef _INC_DRI_CLOCK_H_
#define _INC_DRI_CLOCK_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "dri_def.h"

/*******************************************************************************
 * Defines
 ******************************************************************************/

/*
 * @brief: Fast IRC trimmed clock frequency
 */
#define SCG_FIRC_FREQ     48000000U

#define DRI_PCC_PORTA_CLK_ENABLE() PCC->CLKCFG[PCC_PORTA_INDEX] |= PCC_CLKCFG_CGC(1)     /* Enable clock for PORTA */
#define DRI_PCC_PORTB_CLK_ENABLE() PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1)     /* Enable clock for PORTB */
#define DRI_PCC_PORTC_CLK_ENABLE() PCC->CLKCFG[PCC_PORTC_INDEX] |= PCC_CLKCFG_CGC(1)     /* Enable clock for PORTC */
#define DRI_PCC_PORTD_CLK_ENABLE() PCC->CLKCFG[PCC_PORTD_INDEX] |= PCC_CLKCFG_CGC(1)     /* Enable clock for PORTD */

/*******************************************************************************
 * Typedef enums
 ******************************************************************************/

/*
 * @brief: Clock source for peripherals
 */
typedef enum
{
    CLOCK_SrcOff         = 0U,    /* Clock is off */
    CLOCK_SrcSysOscAsync = 1U,    /* System Oscillator asynchronous clock */
    CLOCK_SrcSircAsync   = 2U,    /* Slow IRC asynchronous clock */
    CLOCK_SrcFircAsync   = 3U,    /* Fast IRC asynchronous clock */
    CLOCK_SrcSpFllAsync  = 5U     /* SPFLL asynchronous clock */
} Clock_Source_Sel_t;

/*
 * @brief: SCG asynchronous clock divider value
 */
typedef enum
{
    SCG_ClkDisable = 0U,          /* Clock disabled */
    SCG_ClkDivBy1  = 1U,          /* Divided by 1 */
    SCG_ClkDivBy2  = 2U,          /* Divided by 2 */
    SCG_ClkDivBy4  = 3U,          /* Divided by 4 */
    SCG_ClkDivBy8  = 4U,          /* Divided by 8 */
    SCG_ClkDivBy16 = 5U,          /* Divided by 1 */
    SCG_ClkDivBy32 = 6U,          /* Divided by 32 */
    SCG_ClkDivBy64 = 7U           /* Divided by 64 */
} SCG_CLK_Div_t;

/*
 * @brief: SCG fast IRC clock frequency range
 */
typedef enum
{
    SCG_FIRC48M,                  /* Fast IRC is trimmed to 48 MHz */
} SCG_FIRC_Range_t;

/*
 * @brief: SCG slow IRC clock frequency range
 */
typedef enum
{
    SCG_SircRangeLowClk,          /* Slow IRC low range clock (2 MHz) */
    SCG_SircRangeHighClk          /* Slow IRC high range clock (8 MHz) */
} SCG_SIRC_Range_t;

/*******************************************************************************
 * Typedef structs
 ******************************************************************************/

/*
 * @brief SCG fast IRC clock configuration
 */
typedef struct
{
    SCG_CLK_Div_t    FIRCDIV2;    /* FIRCDIV2 value */
    SCG_FIRC_Range_t Range;       /* Fast IRC frequency range */
} SCG_FIRC_Config_t;

/*
 * @brief SCG slow IRC clock configuration
 */
typedef struct
{
    SCG_CLK_Div_t    SIRCDIV2;    /* SIRCDIV2 value */
    SCG_SIRC_Range_t Range;       /* Slow IRC frequency range */
} SCG_SIRC_Config_t;

/*******************************************************************************
 * APIs
 ******************************************************************************/
/*
 * @name: DRI_CLOCK_EnableClock
 * ----------------------------
 * @brief: Enable the clock for specific module
 * @param[in] PCCmoduleIndex:
 */
static inline void DRI_CLOCK_EnableClock(const uint32_t PCC_MODULE_INDEX)
{
    PCC->CLKCFG[PCC_MODULE_INDEX] |= PCC_CLKCFG_CGC(1);
}


/*
 * @name: DRI_CLOCK_EnableClock
 * ----------------------------
 * @brief: Disable the clock for specific module
 * @param[in] PCCmoduleIndex:
 */
static inline void DRI_CLOCK_DisableClock(const uint32_t PCC_MODULE_INDEX)
{
    PCC->CLKCFG[PCC_MODULE_INDEX] &= ~(PCC_CLKCFG_CGC_MASK);
}


/*
 * @brief: Set the clock source for specific module
 * @param[in]
 * @param[in] src: Clock source to set
 */
static inline void DRI_CLOCK_SelectSource(const uint32_t PCC_MODULE_INDEX,
        const Clock_Source_Sel_t src)
{
    /* If clock is already enabled, first disable it then set the clock source */
    PCC->CLKCFG[PCC_MODULE_INDEX] &= ~PCC_CLKCFG_CGC_MASK; /* Disables clock */
    PCC->CLKCFG[PCC_MODULE_INDEX] = (PCC->CLKCFG[PCC_MODULE_INDEX]
            & ~(PCC_CLKCFG_PCS_MASK)) | PCC_CLKCFG_PCS(src);
}

/*
 * @brief: Get fast clock range
 * @param[in] base: SCG base pointer
 * @return    firc: frequency range value
 */
static inline uint32_t DRI_SCG_GetFircRange(const SCG_Type* const base)
{
    return ((base->FIRCCFG & SCG_FIRCCFG_RANGE_MASK) >> SCG_FIRCCFG_RANGE_SHIFT);
}


/*
 * @brief: Get the second asynchronous divider for FIRC
 * @param[in] base: Register base address for the SCG instance
 * @return FIRC second asynchronous divider
 */
static inline uint32_t DRI_SCG_GetFircSecondAsyncDivider(const SCG_Type * base)
{
    return (base->FIRCDIV & SCG_FIRCDIV_FIRCDIV2_MASK) >> SCG_FIRCDIV_FIRCDIV2_SHIFT;
}


/*
 * @brief Get the frequency of the FIRCDIV2 clock source
 * @param: None
 * @return The frequency of the FIRCDIV2 clock source in Hertz (Hz)
 */
uint32_t DRI_CLOCK_SYS_Get_FIRCDIV2_CLK(void);


/*
 * @brief: Initializes the SCG fast IRC clock
 * @param[in] config: Pointer to the configuration structure
 */
DRI_StatusTypeDef DRI_CLOCK_InitFirc(const SCG_FIRC_Config_t *const config);


/*
 * brief: De-initializes the SCG fast IRC (Disables the SCG fast IRC)
 */
DRI_StatusTypeDef DRI_CLOCK_DeinitFirc(void);


/*
 * brief: Initializes the SCG slow IRC clock
 */
DRI_StatusTypeDef DRI_CLOCK_InitSirc(const SCG_SIRC_Config_t *const config);


/*
 * brief: De-initializes the SCG slow IRC
 */
DRI_StatusTypeDef DRI_CLOCK_DeinitSirc(void);

#endif /* _INC_DRI_CLOCK_H_ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
