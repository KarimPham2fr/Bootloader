/*
 * dri_adc.h
 *
 *  Created on: May 07, 2024
 *      Author: Phong Pham-Thanh
 *       Email: Phong.PT.HUST@gmail.com
 */

#ifndef _INC_DRI_ADC_H_
#define _INC_DRI_ADC_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "dri_def.h"
#include "dri_clock.h"

/*******************************************************************************
 * Typedef enums
 ******************************************************************************/

/*
 * @brief: Clock Divider selection
 */
typedef enum
{
    ADC_CLK_DIVIDE_1 = 0U,                    /* The divide ratio is 1 and the clock rate is input clock */
    ADC_CLK_DIVIDE_2 = 1U,                    /* The divide ratio is 2 and the clock rate is (input clock)/2 */
    ADC_CLK_DIVIDE_4 = 2U,                    /* The divide ratio is 4 and the clock rate is (input clock)/4 */
    ADC_CLK_DIVIDE_8 = 3U                     /* The divide ratio is 8 and the clock rate is (input clock)/8 */
} ADC_CLK_Divider_t;


/*
 * @brief: Conversion resolution selection
 */
typedef enum
{
    ADC_CONVERSION_8BIT  = 0U,                /* 8-bit conversion */
    ADC_CONVERSION_12BIT = 1U,                /* 12-bit conversion */
    ADC_CONVERSION_10BIT = 2U                 /* 10-bit conversion */
} ADC_Resolution_t;


/*
 * @brief: Selects the input clock source to generate the internal clock, ADCK
 */
typedef enum
{
    ADC_CLK_ALT_1 = 0U,                       /* Alternate clock 1 */
    ADC_CLK_ALT_2 = 1U,                       /* Alternate clock 2 */
    ADC_CLK_ALT_3 = 2U,                       /* Alternate clock 3 */
    ADC_CLK_ALT_4 = 3U                        /* Alternate clock 4 */
} ADC_CLK_Input_t;


/*
 * @brief: ADC pretrigger source select
 */
typedef enum
{
    ADC_PRETRIGGER_SEL_PDB    = 0U,           /* PDB pretrigger (default) */
    ADC_PRETRIGGER_SEL_TRGMUX = 1U,           /* TRGMUX pretrigger */
    ADC_PRETRIGGER_SEL_SW     = 2U            /* Software pretrigger */
} ADC_Pretrigger_SEL_t;


/*
 * @brief: ADC trigger source select
 */
typedef enum
{
    ADC_TRIGGER_SEL_PDB    = 0U,              /* PDB pretrigger (default) */
    ADC_TRIGGER_SEL_TRGMUX = 1U               /* TRGMUX pretrigger */
} ADC_Trigger_SEL_t;


/*
 * @brief: Conversion Trigger Select
 */
typedef enum
{
    ADC_TRIGGER_SOFTWARE = 0U,                /* Software trigger. */
    ADC_TRIGGER_HARDWARE = 1U                 /* Hardware trigger. */
} ADC_Trigger_Type_t;


/*
 * @brief: ADC software pretrigger sources
 */
typedef enum
{
    ADC_SW_PRETRIGGER_DISABLED = 0U,          /* Software pretrigger disabled */
    ADC_SW_PRETRIGGER_0        = 4U,          /* Software pretrigger 0 */
    ADC_SW_PRETRIGGER_1        = 5U,          /* Software pretrigger 1 */
    ADC_SW_PRETRIGGER_2        = 6U,          /* Software pretrigger 2 */
    ADC_SW_PRETRIGGER_3        = 7U           /* Software pretrigger 3 */
} ADC_SW_Pretrigger_t;


/*
 * @brief: Voltage Reference Selection
 */
typedef enum
{
    ADC_VOLTAGEREF_VREF = 0U,                 /* Default voltage reference pin pair, that is, external pins VREFH and VREFL */
    ADC_VOLTAGEREF_VALT = 1U                  /* Alternate reference voltage, that is, VALTH */
} ADC_Voltage_REF_t;


/*
 * @brief: Hardware average selection
 */
typedef enum
{
    ADC_AVERAGE_4        = 0U,                /* Hardware average of 4 samples */
    ADC_AVERAGE_8        = 1U,                /* Hardware average of 8 samples */
    ADC_AVERAGE_16       = 2U,                /* Hardware average of 16 samples */
    ADC_AVERAGE_32       = 3U,                /* Hardware average of 32 samples */
    ADC_AVERAGE_DISABLED = 4U                 /* Hardware average function disabled */
} ADC_Average_t;


/*
 * @brief: Input channel selection
 */
typedef enum
{
    ADC_INPUTCHANNEL_DISABLED  = 0x1FU,                /* Module is disabled */
    /* External input channels  */
    ADC_INPUTCHANNEL_EXT0      = 0x00U,                /* External input channel 0 */
    ADC_INPUTCHANNEL_EXT1      = 0x01U,                /* External input channel 1 */
    ADC_INPUTCHANNEL_EXT2      = 0x02U,                /* External input channel 2 */
    ADC_INPUTCHANNEL_EXT3      = 0x03U,                /* External input channel 3 */
    ADC_INPUTCHANNEL_EXT4      = 0x04U,                /* External input channel 4 */
    ADC_INPUTCHANNEL_EXT5      = 0x05U,                /* External input channel 5 */
    ADC_INPUTCHANNEL_EXT6      = 0x06U,                /* External input channel 6 */
    ADC_INPUTCHANNEL_EXT7      = 0x07U,                /* External input channel 7 */
    ADC_INPUTCHANNEL_EXT8      = 0x08U,                /* External input channel 8 */
    ADC_INPUTCHANNEL_EXT9      = 0x09U,                /* External input channel 9 */
    ADC_INPUTCHANNEL_EXT10     = 0x0AU,                /* External input channel 10 */
    ADC_INPUTCHANNEL_EXT11     = 0x0BU,                /* External input channel 11 */
    ADC_INPUTCHANNEL_EXT12     = 0x0CU,                /* External input channel 12 */
    ADC_INPUTCHANNEL_EXT13     = 0x0DU,                /* External input channel 13 */
    ADC_INPUTCHANNEL_EXT14     = 0x0EU,                /* External input channel 14 */
    ADC_INPUTCHANNEL_EXT15     = 0x0FU,                /* External input channel 15 */
    ADC_INPUTCHANNEL_EXT16     = 0x20U,                /* External input channel 16 */
    ADC_INPUTCHANNEL_EXT17     = 0x21U,                /* External input channel 17 */
    ADC_INPUTCHANNEL_EXT18     = 0x22U,                /* External input channel 18 */
    ADC_INPUTCHANNEL_EXT19     = 0x23U,                /* External input channel 19 */
    ADC_INPUTCHANNEL_EXT20     = 0x24U,                /* External input channel 20 */
    ADC_INPUTCHANNEL_EXT21     = 0x25U,                /* External input channel 21 */
    ADC_INPUTCHANNEL_EXT22     = 0x26U,                /* External input channel 22 */
    ADC_INPUTCHANNEL_EXT23     = 0x27U,                /* External input channel 23 */
    ADC_INPUTCHANNEL_EXT24     = 0x28U,                /* External input channel 24 */
    ADC_INPUTCHANNEL_EXT25     = 0x29U,                /* External input channel 25 */
    ADC_INPUTCHANNEL_EXT26     = 0x2AU,                /* External input channel 26 */
    ADC_INPUTCHANNEL_EXT27     = 0x2BU,                /* External input channel 27 */
    ADC_INPUTCHANNEL_EXT28     = 0x2CU,                /* External input channel 28 */
    ADC_INPUTCHANNEL_EXT29     = 0x2DU,                /* External input channel 29 */
    ADC_INPUTCHANNEL_EXT30     = 0x2EU,                /* External input channel 30 */
    ADC_INPUTCHANNEL_EXT31     = 0x2FU,                /* External input channel 31 */
    /* Internal input channels */
    ADC_INPUTCHANNEL_INT0      = 0x15,                 /* Internal input channel 0  */
    ADC_INPUTCHANNEL_INT1      = 0x16,                 /* Internal input channel 1  */
    ADC_INPUTCHANNEL_INT2      = 0x17,                 /* Internal input channel 2  */
    ADC_INPUTCHANNEL_INT3      = 0x1C,                 /* Internal input channel 3  */

    ADC_INPUTCHANNEL_TEMP      = 0x1A,                 /* Temperature Sensor */
    ADC_INPUTCHANNEL_BANDGAP   = 0x1B,                 /* Band Gap */
    ADC_INPUTCHANNEL_VREFSH    = 0x1D,                 /* Voltage Reference Select High */
    ADC_INPUTCHANNEL_VREFSL    = 0x1E,                 /* Voltage Reference Select Low  */

    ADC_INPUTCHANNEL_SUPPLY_VDD            = 0xF00U,   /* Monitor internal supply 5 V input VDD supply.              */
    ADC_INPUTCHANNEL_SUPPLY_VDDA           = 0xF01U,   /* Monitor internal supply 5 V input analog supply.           */
    ADC_INPUTCHANNEL_SUPPLY_VREFH          = 0xF02U,   /* Monitor internal supply ADC reference supply.              */
    ADC_INPUTCHANNEL_SUPPLY_VDD_3V         = 0xF03U,   /* Monitor internal supply 3.3 V oscillator regulator output. */
    ADC_INPUTCHANNEL_SUPPLY_VDD_FLASH_3V   = 0xF04U,   /* Monitor internal supply 3.3 V flash regulator output.      */
    ADC_INPUTCHANNEL_SUPPLY_VDD_LV         = 0xF05U    /* Monitor internal supply 1.2 V core regulator output.       */
} ADC_Input_Channel_t;

/*******************************************************************************
 * Typedef structs
 ******************************************************************************/

/*
 * @brief: Defines the control channel configuration
 */
typedef struct
{
    ADC_Input_Channel_t channel;              /* Selection of input channel */
    uint8_t             interruptEnable;      /* Enable interrupts for the channel */
} ADC_Channel_Config_t;


/*
 * @brief: ADC Init structure definition
 */
typedef struct
{
    uint8_t                 sampleTime;       /* Sample time in AD Clocks */
    uint8_t                 continuousEnable; /* Enable Continuous conversions */
    ADC_CLK_Divider_t       clockDivide;      /* Divider of the input clock for the ADC */
    ADC_Resolution_t        resolution;       /* ADC resolution (8,10,12-bit) */
    ADC_CLK_Input_t         inputClock;       /* Input clock source */
    ADC_Trigger_Type_t      trigger;          /* ADC trigger type (software, hardware) */
    ADC_Pretrigger_SEL_t    pretriggerSel;
    ADC_Trigger_SEL_t       triggerSel;
    ADC_Voltage_REF_t       voltageRef;       /* Voltage reference used */
} ADC_InitTypeDef;

/*******************************************************************************
 * APIs
 ******************************************************************************/

/*
 * @name: DRI_ADC_Init
 * ---------------------------------
 * @brief:     Initialize the ADC module
 * @param[out] ADCx: ADC peripheral base address
 * @param[in]  config: Pointer to configuration structure
 */
void DRI_ADC_Init(ADC_Type *const ADCx, const ADC_InitTypeDef *const ADC_Init);


/*
 * @name: DRI_ADC_ConfigHwAverage
 * ---------------------------------
 * @brief:     Set the hardware average mode
 * @param[out] ADCx: ADC peripheral base address
 * @param[in]  mode: Setting hardware average mode
 */
void DRI_ADC_ConfigHwAverage(ADC_Type *const ADCx, const ADC_Average_t config);


/*
 * @name: DRI_ADC_ConfigChannel
 * --------------------------------------------
 * @brief: Configure the conversion channel
 * @param[out] ADCx: ADC peripheral base address
 * @param[in]  channelGroup: Channel group index
 * @param[in]  config: Pointer to ADC_Channel_Config_t structure
 */
void DRI_ADC_ConfigChannel(ADC_Type *const ADCx, const uint8_t channelGroup,
        const ADC_Channel_Config_t *const config);


/*
 * @name: DRI_ADC_GetConversionValue
 * --------------------------------------------
 * @brief:    Get the conversion value
 * @param[in] ADCx: ADC peripheral base address
 * @param[in] channelGroup: Channel group index
 * @return:   Conversion value
 */
uint16_t DRI_ADC_GetConversionValue(const ADC_Type *const ADCx,
        const uint8_t channelGroup);


/*
 * @name: DRI_ADC_GetConvCompleteFlag
 * --------------------------------------------
 * @brief: Get the Conversion Complete Flag
 * @param[in] ADCx: ADC peripheral base address
 * @param[in] channelGroup: Channel group index
 */
uint8_t DRI_ADC_GetConvCompleteFlag(const ADC_Type *const ADCx,
        const uint8_t channelGroup);

#endif /* _INC_DRI_ADC_H_ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
