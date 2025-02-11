#pragma once

#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>

#define MY_SET_BIT(num, pos, value) { \
        (num) &= ~(1 << (pos)); \
        (num) |= ((value) & 1) << (pos); \
    }

#define MY_SET_TWO_BITS(num, pos, value) { \
        (num) &= ~(0b11 << ((pos) * 2)); \
        (num) |= ((value) & 0b11) << ((pos) * 2); \
    }


#define My_HAL_RCC_GPIOA_CLK_ENABLE() RCC->AHBENR |= RCC_AHBENR_GPIOAEN
#define My_HAL_RCC_GPIOC_CLK_ENABLE() RCC->AHBENR |= RCC_AHBENR_GPIOCEN

void My_HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void My_HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);
GPIO_PinState My_HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void My_HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void My_HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
