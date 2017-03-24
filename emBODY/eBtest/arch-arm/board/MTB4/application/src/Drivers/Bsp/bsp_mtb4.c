/*
 * Copyright (C) 2017 iCub Facility - Istituto Italiano di Tecnologia
 * Author:  Valentina Gaggero
 * email:   valentina.gaggero@iit.it
 * website: www.robotcub.org
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/


// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------




#include "string.h"

#include "main.h"
#include "stm32l4xx_hal.h"
#include "adc.h"
#include "can.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern public interface
// --------------------------------------------------------------------------------------------------------------------

#include "bsp.h"

// --------------------------------------------------------------------------------------------------------------------
// - #define with internal scope
// --------------------------------------------------------------------------------------------------------------------

#define ST32HAL_REMOVE_CODE

// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of extern variables, but better using _get(), _set() 
// --------------------------------------------------------------------------------------------------------------------

#define BSP_FAKE_JUMP



// --------------------------------------------------------------------------------------------------------------------
// - typedef with internal scope
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - declaration of static functions
// --------------------------------------------------------------------------------------------------------------------

extern int8_t bsp_led_global_init(void);

// functions generated by cubemx and typically placed into main.c. VERY IMPORTANT: remove HAL_SYSTICK_Config()
void Error_Handler(void);
void SystemClock_Config(void);


// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of static variables
// --------------------------------------------------------------------------------------------------------------------

//static uint32_t s_bsp_led_onmask = 0;


// --------------------------------------------------------------------------------------------------------------------
// - definition of extern public functions
// --------------------------------------------------------------------------------------------------------------------

#if defined(ST32HAL_REMOVE_CODE)

#include "osal.h"

// redefinition of the HAL_* function which we want to behave differently.
// 1. all the sys-tick funtions which we use w/ rtos

HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
//  /*Configure the SysTick to have interrupt in 1ms time basis*/
//  HAL_SYSTICK_Config(SystemCoreClock/1000);
//
//  /*Configure the SysTick IRQ priority */
//  HAL_NVIC_SetPriority(SysTick_IRQn, TickPriority ,0);
//
//  /* Return function status */
  return HAL_OK;
}

void HAL_IncTick(void)
{
//  uwTick++;
}

uint32_t HAL_GetTick(void)
{
    osal_abstime_t t = osal_system_ticks_abstime_get() / 1000; // now t is expressed in millisec
    return (uint32_t)t;
//  return uwTick;
}

// exactly as implemented in stm32l4xx_hal.c
void HAL_Delay(uint32_t Delay)
{
  uint32_t tickstart = 0;
  tickstart = HAL_GetTick();
  while((HAL_GetTick() - tickstart) < Delay)
  {
  }
}

void HAL_SuspendTick(void)
{
 // /* Disable SysTick Interrupt */
//  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}


void HAL_ResumeTick(void)
{
//  /* Enable SysTick Interrupt */
//  SysTick->CTRL  |= SysTick_CTRL_TICKINT_Msk;
}

#endif


extern int8_t bsp_init(void)
{
    // in here we get the code generated by cube-mx and present in main.c and we keep just what we need
    
    // reset of all peripherals, Initializes the Flash interface (BUT NOT SYSTICK)
    HAL_Init();
    // configure the system clock
    SystemClock_Config();
    
    // initialize all configured peripherals 
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_TIM6_Init();
    MX_CAN1_Init();
    MX_USART1_UART_Init();
    MX_I2C1_Init();
    MX_I2C2_Init();
    MX_USART2_UART_Init();
    MX_ADC1_Init();

    
    //init other device
    //Si705x_init();
    //BNO055_init();
    return 0;

       
//  /* USER CODE BEGIN 1 */
// 
//  /* USER CODE END 1 */
// 
//  /* MCU Configuration----------------------------------------------------------*/
// 
//  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
//  HAL_Init();
// 
//  /* Configure the system clock */
//  SystemClock_Config();
// 
//  /* Initialize all configured peripherals */
//  MX_GPIO_Init();
//  MX_USART2_UART_Init();
// 
//  /* USER CODE BEGIN 2 */
// 
//  /* USER CODE END 2 */
// 
//  /* Infinite loop */
//  /* USER CODE BEGIN WHILE */
//  while (1)
//  {
//  /* USER CODE END WHILE */
// 
//  /* USER CODE BEGIN 3 */
// 
//  }
//  /* USER CODE END 3 */
//    
//    return 0;

}

extern uint32_t bsp_sys_get_clock(void)
{
    return(SystemCoreClock);
}


extern void bsp_sys_reset(void)
{
    NVIC_SystemReset();
}

extern bool bsp_sys_jump2address(uint32_t address)
{
#if defined(BSP_FAKE_JUMP)
    return 0;
#else
    volatile uint32_t jumpaddr;
    void (*app_fn)(void) = NULL;

//    if(hl_res_NOK_generic == hl_sys_canjump(addr))
//    {
//        return(hl_res_NOK_generic);
//    }

    // prepare jump address 
    jumpaddr = *(volatile uint32_t*) (addr + 4);
    // prepare jumping function
    app_fn = (void (*)(void)) jumpaddr;
    // initialize user application's stack pointer 
    __set_MSP(*(volatile uint32_t*) addr);
    // jump.
    app_fn(); 
    
    // never in here.
    return(0); 
#endif     
}


extern int8_t bsp_led_init(uint8_t led, const void *dummyparam)
{
    if(led > bsp_led_maxnum)
    {
        return -1;
    }
    
   // bsp_led_global_init();
   // fake; I should check if bsp has been already initted
    return 0;
}    

extern int8_t bsp_led_global_init(void) 
{
    static uint8_t initted = 0;
    
    if(1 == initted)
    {
        return 0;
    }
    
    initted = 1;
    
    
    //MX_GPIO_Init(); VALE: removed because we alreday have init GPIO in bps_init
    
//    s_bsp_led_onmask = 0;
        
    return 0;
}


extern int8_t bsp_led_on(uint8_t led)
{
    if(led > bsp_led_maxnum)
    {
        return -1;
    }
    switch(led)
    {
        case bsp_ledblue:
            HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
            break;
        case bsp_ledred:
            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
            break;
    };
    
    return 0;
}


extern int8_t bsp_led_off(uint8_t led) 
{    
    if(led > bsp_led_maxnum)
    {
        return -1;
    }
    switch(led)
    {
        case bsp_ledblue:
            HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
            break;
        case bsp_ledred:
            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
            break;
    };
    
    return 0;
}

extern int8_t bsp_led_toggle(uint8_t led)
{
    if(led > bsp_led_maxnum)
    {
        return -1;
    }
    switch(led)
    {
        case bsp_ledblue:
            HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
            break;
        case bsp_ledred:
            HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
            break;
    };
    
    return 0;
    
}

extern int8_t bsp_button_pressed(uint8_t btn)
{
    
    return -1; //not present on this board
}



// flashstorage

static bool s_flashstorage_initted = false;
static uint64_t s_flashstorage_buffer[128] = {0};

static const uint32_t s_flashstorage_start = 0x08040000; // 256k, page #128
static const uint32_t s_flashstorage_size = 1024;

extern bool bsp_flashstorage_init(void)
{
    s_flashstorage_initted = true;
    
    HAL_FLASH_Unlock();
    //HAL_FLASH_OB_Unlock();
    
    return(s_flashstorage_initted);
}


extern bool bsp_flashstorage_isinitted(void)
{
    return(s_flashstorage_initted);     
}


extern bool bsp_flashstorage_isaddressvalid(uint32_t adr)
{
    if((adr < s_flashstorage_start) || (adr > s_flashstorage_start+s_flashstorage_size) )
    {
        return false;
    }
    return true;
}


extern uint32_t bsp_flashstorage_getbaseaddress(void)
{   
    return s_flashstorage_start;
}


extern uint32_t bsp_flashstorage_getsize(void)
{ 
    return s_flashstorage_size;
}


extern bool bsp_flashstorage_fullerase(void)
{
    // erase page
    FLASH_EraseInitTypeDef erase = {0};
    erase.TypeErase = FLASH_TYPEERASE_PAGES;
    erase.Banks = FLASH_BANK_1;
    erase.Page = 128;
    erase.NbPages = 1;
    uint32_t pagenum = 0;
    HAL_FLASH_Unlock();
    int a = HAL_FLASHEx_Erase(&erase, &pagenum);
    a = a;
    HAL_FLASH_Lock();
    return true;
}


extern bool bsp_flashstorage_erase(uint32_t addr, uint32_t size)
{
    if(0 == bsp_flashstorage_isaddressvalid(addr))
    {
        return false;
    }
    if(0 == bsp_flashstorage_isaddressvalid(addr+size))
    {
        return false;
    }
    
    
    return false;
    
    // not supported yet.
    
//    // copy everything in ram,
//    bsp_flashstorage_read(s_flashstorage_start, s_flashstorage_size, s_flashstorage_buffer);
//    // erase fully
//    bsp_flashstorage_fullerase();
//    // copy pieces outsize of [addr, addr+size]
//    #warning TOBEDONE
//    
//    return 1;
}


extern bool bsp_flashstorage_read(uint32_t addr, uint32_t size, void *data)
{
    if(0 == bsp_flashstorage_isaddressvalid(addr))
    {
        return false;
    }
    if(0 == bsp_flashstorage_isaddressvalid(addr+size))
    {
        return false;
    }
    if(NULL == data)
    {
        return false;
    }
    
    // can read directly from flash
    void *st = (void*) addr;
    memcpy(data, st, size); 
    
    return true;
}


extern bool bsp_flashstorage_write(uint32_t addr, uint32_t size, const void *data)
{
    if(0 == bsp_flashstorage_isaddressvalid(addr))
    {
        return false;
    }
    if(0 == bsp_flashstorage_isaddressvalid(addr+size))
    {
        return false;
    }
    if(NULL == data)
    {
        return false;
    }
    
    // read all flash with buffer.  
    bsp_flashstorage_read(s_flashstorage_start, s_flashstorage_size, s_flashstorage_buffer);
    // change the buffer
    uint32_t reducedaddress = addr - s_flashstorage_start;
    memcpy(&s_flashstorage_buffer[reducedaddress/8], data, size);
    // erase page
    bsp_flashstorage_fullerase();
    
    HAL_FLASH_Unlock();
    
#if 0
    // write the whole buffer into the page
    uint32_t tmpadr = addr;
    uint64_t tmpdataadr = (uint64_t) &s_flashstorage_buffer[0];
    uint16_t iterations = 3; // 1024/256 - 1;
    for(uint8_t i=0; i<iterations; i++)
    {   
        // writing 256 bytes
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST, tmpadr, tmpdataadr);        
        tmpadr += 256;
        tmpdataadr += 256;
    }
    // writing the last 256 bytes
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST_AND_LAST, tmpadr, tmpdataadr);
#else
    uint32_t tmpadr = addr;
    for(uint16_t i=0; i<128; i++)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, tmpadr, s_flashstorage_buffer[i]);
        tmpadr += 8;
    }
#endif
//FLASH_TYPEPROGRAM_DOUBLEWORD
    
    volatile uint32_t xx =  HAL_FLASH_GetError();
    
    xx= xx;
    
    HAL_FLASH_Lock();
    
    return true;
}

#if 0


HAL_FLASH_Unlock()

HAL_FLASH_Program()


#endif


// --------------------------------------------------------------------------------------------------------------------
// - definition of static functions 
// --------------------------------------------------------------------------------------------------------------------



/** System Clock Configuration
*/
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_I2C2
                              |RCC_PERIPHCLK_ADC;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
  PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_PLLSAI1;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_HSI;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 8;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_ADC1CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the main internal regulator output voltage 
    */
    if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
    {
        Error_Handler();
    }

#if defined(ST32HAL_REMOVE_CODE) 
#else  
    /**Configure the Systick interrupt time 
    */
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
#endif
    /**Configure the Systick 
    */

    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}


// --------------------------------------------------------------------------------------------------------------------
// - end-of-file (leave a blank line after)
// --------------------------------------------------------------------------------------------------------------------



