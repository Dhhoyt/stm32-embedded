#include <stm32f0xx_hal.h>
#include <main.h>
#include <assert.h>

#include "hal_gpio.h"

int lab2_main(void) {
    HAL_Init();
    SystemClock_Config();
    My_HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitTypeDef initStr = {GPIO_PIN_6 | GPIO_PIN_9 | GPIO_PIN_7,
        GPIO_MODE_OUTPUT_PP,
        GPIO_NOPULL,
        GPIO_SPEED_FREQ_LOW
    };
    HAL_GPIO_Init(GPIOC, &initStr);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6 | GPIO_PIN_9 | GPIO_PIN_7, GPIO_PIN_SET);
    assert(EXTI->EMR == 0x0UL);
    assert(EXTI->RTSR == 0x0UL);
    assert(EXTI->FTSR == 0x0UL);
    unmask_exti(0, RISING);
    assert(EXTI->EMR == 0x1UL);
    assert(EXTI->RTSR == 0x1UL);
    assert(EXTI->FTSR == 0x0UL);
    My_HAL_RCC_SYSCFG_CLK_ENABLE();
    initStr = (GPIO_InitTypeDef){GPIO_PIN_0,
        GPIO_MODE_INPUT,
        GPIO_PULLDOWN,
        GPIO_SPEED_FREQ_LOW
    };
    My_HAL_GPIO_Init(GPIOA, &initStr);
    while (1) {
        HAL_Delay(400);
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
    }
}