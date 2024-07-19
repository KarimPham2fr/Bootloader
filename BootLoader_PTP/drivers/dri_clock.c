/*
 * dri_clock.c
 *
 *  Created on: Apr 12, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

#include "dri_clock.h"

static const uint32_t fircFreq[] =
{
	SCG_FIRC_FREQ,
};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*
 * @brief: Initializes the SCG fast IRC clock
 */
DRI_StatusTypeDef DRI_CLOCK_InitFirc(const SCG_FIRC_Config_t* const config)
{
    DRI_StatusTypeDef status = DRIVER_OK;
    if (config != NULL)
    {
        /* Setup Clock divider */
        SCG->FIRCDIV = SCG_FIRCDIV_FIRCDIV2(config->FIRCDIV2);
        /* Set Frequency Range */
        SCG->FIRCCFG = SCG_FIRCCFG_RANGE(config->Range);
        /* Enable Fast IRC clock */
        SCG->FIRCCSR |= SCG_FIRCCSR_FIRCEN(1U);
        /* Wait for FIRC clock to be valid */
        while (0U == (SCG->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK));
    }
    else
    {
        status = DRIVER_ERROR;
    }

    return status;
}

/*
 * brief: De-initializes the SCG fast IRC.
 */
DRI_StatusTypeDef DRI_CLOCK_DeinitFirc(void)
{
    DRI_StatusTypeDef Status = DRIVER_OK;

    /* Return error if clock is used by system */
    if (((SCG->FIRCCSR) & SCG_FIRCCSR_FIRCSEL_MASK) != 0U)
    {
        Status = DRIVER_ERROR_BUSY;
    }
    else
    {
        SCG->FIRCCSR = SCG_FIRCCSR_FIRCERR_MASK;
    }

    return Status;
}

/*
 * brief: Initializes the SCG slow IRC clock
 */
DRI_StatusTypeDef DRI_CLOCK_InitSirc(const SCG_SIRC_Config_t *const config)
{
    DRI_StatusTypeDef Status = DRIVER_OK;

    /* De-init the SIRC first. */
    Status = DRI_CLOCK_DeinitSirc();

    if (Status == DRIVER_OK)
    {
        /* Setup clock divider */
        SCG->SIRCDIV = SCG_SIRCDIV_SIRCDIV2(config->SIRCDIV2);
        /* Set Frequency Range */
        SCG->SIRCCFG = SCG_SIRCCFG_RANGE(config->Range);
        /* Enable Slow IRC clock */
        SCG->SIRCCSR |= SCG_SIRCCSR_SIRCEN(1);
        /* Wait for SIRC clock to be valid */
        while (0U == ((SCG->SIRCCSR) & SCG_SIRCCSR_SIRCVLD_MASK));
    }

    return Status;
}

/*
 * brief: De-initializes the SCG slow IRC
 */
DRI_StatusTypeDef DRI_CLOCK_DeinitSirc(void)
{
    DRI_StatusTypeDef Status = DRIVER_OK;

    /* If clock is used by system, return error. */
    if (((SCG->SIRCCSR) & SCG_SIRCCSR_SIRCSEL_MASK) != 0U)
    {
        Status = DRIVER_ERROR_BUSY;
    }
    else
    {
        SCG->SIRCCSR &= ~(SCG_SIRCCSR_SIRCEN_MASK);
        Status       = DRIVER_OK;
    }

    return Status;
}


/*
 * @brief Get the frequency of the FIRCDIV2 clock source
 */
uint32_t DRI_CLOCK_SYS_Get_FIRCDIV2_CLK(void)
{
    uint32_t freq = 0U;
    uint32_t div  = 0U;

    freq = fircFreq[DRI_SCG_GetFircRange(SCG)];
    div  = DRI_SCG_GetFircSecondAsyncDivider(SCG);

    return (uint32_t)(freq / div);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
