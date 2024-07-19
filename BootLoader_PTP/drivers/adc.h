/*
 * ADC.h
 *
 *  Created on: May 07, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

#ifndef _INC_ADC_H_
#define _INC_ADC_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "dri_adc.h"

/*******************************************************************************
 * APIs
 ******************************************************************************/

/*
 * @name: ADC_InterruptEnable
 * ----------------------------
 * @brief: Enable/Disable conversion complete interrupts
 * @param[out] ADCx: ADC peripheral base address
 * @param[in]  channelGroup: Channel group index
 * @param[in]  enable: Set to 1 to enable interrupts, 0 to disable interrupts
 */
static inline void ADC_InterruptEnable(ADC_Type *const ADCx,
        const uint8_t channelGroup, const uint8_t enable)
{
    ADCx->SC1[channelGroup] = ((ADCx->SC1[channelGroup]) & ~(ADC_SC1_AIEN_MASK))
            | ADC_SC1_AIEN(enable);
}


/*
 * @name: ADC_SetClockDivide
 * ----------------------------
 * @brief: Sets the ADC clock divider configuration
 * @param[out] ADCx: ADC peripheral base address
 * @param[in]  clockDivide:
 *             - ADC_CLK_DIVIDE_1: Divider set to 1
 *             - ADC_CLK_DIVIDE_2: Divider set to 2
 *             - ADC_CLK_DIVIDE_4: Divider set to 4
 *             - ADC_CLK_DIVIDE_8: Divider set to 8
 */
static inline void ADC_SetClockDivide(ADC_Type *const ADCx,
        const ADC_CLK_Divider_t clockDivide)
{
    ADCx->CFG1 = ((ADCx->CFG1) & ~(ADC_CFG1_ADIV_MASK))
            | ADC_CFG1_ADIV(clockDivide);
}


/*
 * @name: ADC_SetSampleTime
 * ----------------------------
 * @brief: Sets the Sample time in ADCK clock cycles
 * @note:  Selects a sample time of 2 to 256 ADCK clock cycles
 * @param[out] ADCx: ADC peripheral base address
 * @param[in]  sampleTime: Sample time in ADCK Clocks
 */
static inline void ADC_SetSampleTime(ADC_Type *const ADCx,
        const uint8_t sampleTime)
{
    ADCx->CFG2 = ((ADCx->CFG2) & ~(ADC_CFG2_SMPLTS_MASK))
            | ADC_CFG2_SMPLTS(sampleTime);
}


/*
 * @name: ADC_SetResolution
 * ----------------------------
 * @brief: Sets the ADC resolution
 * @param[out] ADCx: ADC peripheral base address
 * @param[in]  resolution: The ADC resolution mode
 *             - ADC_CONVERSION_8BIT:  8-bit resolution mode
 *             - ADC_CONVERSION_10BIT: 10-bit resolution mode
 *             - ADC_CONVERSION_12BIT: 12-bit resolution mode
 */
static inline void ADC_SetResolution(ADC_Type *const ADCx,
        const ADC_Resolution_t resolution)
{
    ADCx->CFG1 = ((ADCx->CFG1) & ~(ADC_CFG1_MODE_MASK))
            | ADC_CFG1_MODE(resolution);
}


/*
 * @name: ADC_SetTriggerMode
 * ----------------------------
 * @brief: Sets the ADC Trigger Mode
 * @param[out] ADCx: ADC peripheral base address
 * @param[in]  Trigger: the desired trigger mode
 *             - ADC_TRIGGER_SOFTWARE: Software trigger
 *             - ADC_TRIGGER_HARDWARE: Hardware trigger
 */
static inline void ADC_SetTriggerMode(ADC_Type *const ADCx,
        const ADC_Trigger_Type_t Trigger)
{
    ADCx->SC2 = ((ADCx->SC2) & ~(ADC_SC2_ADTRG_MASK)) | ADC_SC2_ADTRG(Trigger);
}


/*
 * @name: ADC_SetInputClock
 * ----------------------------
 * @brief: Sets the ADCK Clock Input configuration
 * @param[out] ADCx: ADC peripheral base address
 * @param[in]  inputClock:
 *             - ADC_CLK_ALT_1: ADC Input clock source alternative 1
 *             - ADC_CLK_ALT_2: ADC Input clock source alternative 2
 *             - ADC_CLK_ALT_3: ADC Input clock source alternative 3
 *             - ADC_CLK_ALT_4: ADC Input clock source alternative 4
 */
static inline void ADC_SetInputClock(ADC_Type *const ADCx,
        const ADC_CLK_Input_t inputClock)
{
    ADCx->CFG1 = ((ADCx->CFG1) & ~(ADC_CFG1_ADICLK_MASK))
            | ADC_CFG1_ADICLK(inputClock);
}


/*
 * @name: ADC_SetVoltageReference
 * ----------------------------
 * @brief: Sets the ADC Reference Voltage
 * @param[out] ADCx: ADC peripheral base address
 * @param[in]  voltageRef: The voltage reference input
 *             - ADC_VOLTAGEREF_VREF: VrefL and VrefH used as voltage reference
 *             - ADC_VOLTAGEREF_VALT: ValtL and ValtH used as voltage reference
 */
static inline void ADC_SetVoltageReference(ADC_Type *const ADCx,
        const ADC_Voltage_REF_t voltageRef)
{
    ADCx->SC2 = ((ADCx->SC2) & ~(ADC_SC2_REFSEL_MASK))
            | ADC_SC2_REFSEL(voltageRef);
}


/*
 * @name: ADC_SetContinuousConversion
 * ----------------------------
 * @brief: Enables/Disables continuous conversions
 * @param[out] ADCx: ADC peripheral base address
 * @param[in]  enable: Set to 1 to enable continuous conversion, 0 to disable continuous conversion
 */
static inline void ADC_SetContinuousConversion(ADC_Type *const ADCx,
        const uint8_t enable)
{
    ADCx->SC3 = ((ADCx->SC3) & ~(ADC_SC3_ADCO_MASK)) | ADC_SC3_ADCO(enable);
}


/*
 * @name: ADC_SetHwAverageMode
 * ----------------------------
 * @brief: Determines how many ADC conversions will be averaged to create the ADC average result
 * @param[out] ADCx: ADC peripheral base address
 * @param[in]  averageResult: Number of results will be averaged
 *             - ADC_AVERAGE_4:  4 samples averaged
 *             - ADC_AVERAGE_8:  8 samples averaged
 *             - ADC_AVERAGE_16: 16 samples averaged
 *             - ADC_AVERAGE_32: 32 samples averaged
 */
static inline void ADC_SetHwAverageMode(ADC_Type *const ADCx,
        const ADC_Average_t averageResult)
{
    ADCx->SC3 = ((ADCx->SC3) & ~(ADC_SC3_AVGS_MASK))
            | ADC_SC3_AVGS(averageResult);
}


/*
 * @name: ADC_SetInputChannel
 * ----------------------------
 * @brief: Selects input channel
 * @param[out] ADCx: ADC peripheral base address
 * @param[in]  channelGroup: Channel group index
 * @param[in]  channel: Selected channel. See to "ADC_Input_Channel_t"
 */
static inline void ADC_SetInputChannel(ADC_Type *const ADCx,
        const uint8_t channelGroup, const ADC_Input_Channel_t channel)
{
    ADCx->SC1[channelGroup] = ((ADCx->SC1[channelGroup]) & ~(ADC_SC1_ADCH_MASK))
            | ADC_SC1_ADCH(channel);
}

#endif /* _INC_ADC_H_ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
