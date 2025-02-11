#include "hal_gpio.h"\

#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>
#include <assert.h>

void My_HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    uint32_t pins = GPIO_Init->Pin;
    uint32_t gpio_mode = (GPIO_Init->Mode >> GPIO_MODE_Pos) & 0b11;
    uint32_t output_type = (GPIO_Init->Mode >> OUTPUT_TYPE_Pos) & 0b1;
    uint32_t gpio_pull = GPIO_Init->Pull & 0b11;
    uint32_t ospeed_r = GPIO_Init->Speed & 0b11;
    for (int i = 0; i < 16; i++) {
        if ((pins & (1 << i)) == 0) {
            continue;
        }

        //uint32_t exit_mode = (GPIO_Init->Mode >> EXTI_MODE_Pos) & 0b11;
        //uint32_t trigger_mode = (GPIO_Init->Mode >> TRIGGER_MODE_Pos) & 0b111;
        MY_SET_TWO_BITS(GPIOx->MODER, i, gpio_mode);
        MY_SET_BIT(GPIOx->OTYPER, i, output_type);
        MY_SET_TWO_BITS(GPIOx->OSPEEDR, i, ospeed_r);
        MY_SET_TWO_BITS(GPIOx->PUPDR, i, gpio_pull);
    }
}   


/*
void My_HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
}
*/

GPIO_PinState My_HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    if (GPIOx->IDR & GPIO_Pin != 0) {
        return GPIO_PIN_SET;
    } else {
        return GPIO_PIN_RESET;
    }
}

void My_HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
    if (PinState == GPIO_PIN_SET){
        GPIOx->BSRR = GPIO_Pin;
    }
    else {
        GPIOx->BSRR = GPIO_Pin << 16;
    }
}

void My_HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint32_t current_value = GPIOx->ODR;
    uint32_t set = (current_value & GPIO_Pin) << 16;
    uint32_t reset = ~current_value & GPIO_Pin;
    GPIOx->BSRR = set | reset;
}

void My_HAL_Route_EXTI(uint16_t id, enum GPIOBank bank) {
    assert(bank < 16);
    volatile uint32_t* reg = &SYSCFG->EXTICR[id >> 2];
    uint8_t shift = (id % 4) << 2;
    *reg = (*reg & ~(0xF << shift)) | (bank << shift);
}