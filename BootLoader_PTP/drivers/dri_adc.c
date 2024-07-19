/*
 * dri_adc.c
 *
 *  Created on: May 07, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "adc.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*
 * @name:  DRI_ADC_Init
 * ---------------------------------
 * @brief: Initialize the ADC module
 */
void DRI_ADC_Init(ADC_Type* const ADCx, const ADC_InitTypeDef* const ADC_Init)
{
    /* Enable ADC module clock */
    DRI_CLOCK_EnableClock(PCC_ADC0_INDEX);

    /* Selects the input clock source to generate the internal clock, ADCK */
    ADC_SetInputClock(ADCx, ADC_Init->inputClock);
    /* Selects the divide ratio used by the ADC to generate the internal clock ADCK */
    ADC_SetClockDivide(ADCx, ADC_Init->clockDivide);
    /* Selects a sample time */
    ADC_SetSampleTime(ADCx, ADC_Init->sampleTime);
    /* Selects the ADC resolution */
    ADC_SetResolution(ADCx, ADC_Init->resolution);
    /* Selects the type of trigger used for initiating a conversion */
    ADC_SetTriggerMode(ADCx, ADC_Init->trigger);
    /* Selects the voltage reference source used for conversions */
    ADC_SetVoltageReference(ADCx, ADC_Init->voltageRef);
    /* Continuous Conversion Enable */
    ADC_SetContinuousConversion(ADCx, ADC_Init->continuousEnable);
}


/*
 * @name:  DRI_ADC_ConfigHwAverage
 * ---------------------------------
 * @brief: Set the hardware average mode
 */
void DRI_ADC_ConfigHwAverage(ADC_Type* const ADCx, const ADC_Average_t mode)
{
    switch (mode)
    {
        case ADC_AVERAGE_4:
        case ADC_AVERAGE_8:
        case ADC_AVERAGE_16:
        case ADC_AVERAGE_32:
            ADCx->SC3 = ((ADCx->SC3) & ~(ADC_SC3_AVGS_MASK | ADC_SC3_AVGE_MASK))
                                        | (ADC_SC3_AVGS(mode) | ADC_SC3_AVGE_MASK);
            break;

        case ADC_AVERAGE_DISABLED:
            ADCx->SC3 = ((ADCx->SC3) & ~(ADC_SC3_AVGS_MASK | ADC_SC3_AVGE_MASK));
            break;

        default:
            /* Do Nothing */
            break;
    }
}


/*
 * @name: DRI_ADC_ConfigChannel
 * ---------------------------------
 * @brief: Configure the conversion channel
 */
void DRI_ADC_ConfigChannel(ADC_Type *const ADCx, const uint8_t channelGroup,
        const ADC_Channel_Config_t *const config)
{
    /* Selects one of the input channels */
    ADC_SetInputChannel(ADCx, channelGroup, config->channel);
    /* Enables conversion complete interrupts */
    ADC_InterruptEnable(ADCx, channelGroup, config->interruptEnable);
}


/*
 * @name:  DRI_ADC_GetConversionValue
 * ---------------------------------
 * @brief: Get the conversion value
 */
uint16_t DRI_ADC_GetConversionValue(const ADC_Type *const ADCx,
        const uint8_t channelGroup)
{
    return ((ADCx->R[channelGroup]) & ADC_R_D_MASK) >> ADC_R_D_SHIFT;
}


/*
 * @name:  DRI_ADC_GetConvCompleteFlag
 * ---------------------------------
 * @brief: Get the status flags of channel
 */
uint8_t DRI_ADC_GetConvCompleteFlag(const ADC_Type *const ADCx,
        const uint8_t channelGroup)
{
    return ((ADCx->SC1[channelGroup]) & ADC_SC1_COCO_MASK) >> ADC_SC1_COCO_SHIFT;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
