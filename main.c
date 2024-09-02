#include <stdio.h>
#include <stdint.h>
#include "src.h"

void GPIO_PC(void);
void GPIO_INPUT(void);
void EXTI_CON(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
void NVIC_Config(void);

int main() {
    GPIO_PC();
    GPIO_INPUT();
    EXTI_CON();
    NVIC_Config();

    GPIO_PORTC->GPIO_ODR |= (1 << 14); // YELLOW LED (PC14)
    GPIO_PORTB->GPIO_ODR |= (1 << 8);  // RED LED (PB8)
    GPIO_PORTC->GPIO_ODR |= (1 << 13); // GREEN LED (PC13)

    while (1) {
        // Main loop
    }
    return 0;
}

void GPIO_INPUT(void) {
    // Enable clock for Port A, Port B, and Port C
    BASE_RCC->APB2ENR |= (1 << 2); // Enable clock for Port A
    BASE_RCC->APB2ENR |= (1 << 3); // Enable clock for Port B
    BASE_RCC->APB2ENR |= (1 << 4); // Enable clock for Port C

    // Configure PA1 as input
    GPIO_PORTA->GPIO_CRL &= ~(0xF << 4); // Clear configuration bits for PA1
    GPIO_PORTA->GPIO_CRL |= (0x8 << 4);  // Set PA1 as input pull-up/pull-down
    GPIO_PORTA->GPIO_ODR |= (1 << 1);    // Enable pull-up on PA1

    // Configure PA2 as input
    GPIO_PORTA->GPIO_CRL &= ~(0xF << 8); // Clear configuration bits for PA2
    GPIO_PORTA->GPIO_CRL |= (0x8 << 8);  // Set PA2 as input pull-up/pull-down
    GPIO_PORTA->GPIO_ODR |= (1 << 2);    // Enable pull-up on PA2

    // Configure PC15 as input
    GPIO_PORTC->GPIO_CRH &= ~(0xF << 28); // Clear configuration bits for PC15
    GPIO_PORTC->GPIO_CRH |= (0x8 << 28);  // Set PC15 as input pull-up/pull-down
    GPIO_PORTC->GPIO_ODR |= (1 << 15);    // Enable pull-up on PC15
}

void GPIO_PC(void) {
    // Enable clock for Port B and Port C
    BASE_RCC->APB2ENR |= (1 << 4); // Enable clock for Port C
    BASE_RCC->APB2ENR |= (1 << 3); // Enable clock for Port B

    // Configure PC13 (Green LED) as output
    GPIO_PORTC->GPIO_CRH &= ~(0xF << 20); // Clear configuration bits for PC13
    GPIO_PORTC->GPIO_CRH |= (0x3 << 20);  // Set PC13 as output at 50 MHz

    // Configure PC14 (Yellow LED) as output
    GPIO_PORTC->GPIO_CRH &= ~(0xF << 24); // Clear configuration bits for PC14
    GPIO_PORTC->GPIO_CRH |= (0x3 << 24);  // Set PC14 as output at 50 MHz

    // Configure PB8 (Red LED) as output
    GPIO_PORTB->GPIO_CRH &= ~(0xF << 0);  // Clear configuration bits for PB8
    GPIO_PORTB->GPIO_CRH |= (0x3 << 0);   // Set PB8 as output at 50 MHz
}

void EXTI_CON(void) {
    // Enable clock for AFIO
    BASE_RCC->APB2ENR |= (1 << 0);

    // Configure EXTI line 1 for PA1
    AFIO_BASE->AFIO_EXTICR1 &= ~(0xF << 4); // Clear EXTI1 configuration
    AFIO_BASE->AFIO_EXTICR1 |= (0 << 4);    // Set EXTI1 to PA1

    // Configure EXTI line 1 to trigger on falling edge
    BASE_EXTI->EXTI_IMR |= (1 << 1);   // Unmask EXTI line 1
    BASE_EXTI->EXTI_RTSR &= ~(1 << 1); // Disable rising edge trigger
    BASE_EXTI->EXTI_FTSR |= (1 << 1);  // Enable falling edge trigger

    // Configure EXTI line 2 for PA2
    AFIO_BASE->AFIO_EXTICR1 &= ~(0xF << 8); // Clear EXTI2 configuration
    AFIO_BASE->AFIO_EXTICR1 |= (0 << 8);    // Set EXTI2 to PA2

    // Configure EXTI line 2 to trigger on falling edge
    BASE_EXTI->EXTI_IMR |= (1 << 2);   // Unmask EXTI line 2
    BASE_EXTI->EXTI_RTSR &= ~(1 << 2); // Disable rising edge trigger
    BASE_EXTI->EXTI_FTSR |= (1 << 2);  // Enable falling edge trigger

    // Configure EXTI line 15 for PC15
    AFIO_BASE->AFIO_EXTICR4 &= ~(0xF << 12); // Clear EXTI15 configuration
    AFIO_BASE->AFIO_EXTICR4 |= (0x2 << 12);  // Set EXTI15 to PC15

    // Configure EXTI line 15 to trigger on falling edge
    BASE_EXTI->EXTI_IMR |= (1 << 15);   // Unmask EXTI line 15
    BASE_EXTI->EXTI_RTSR &= ~(1 << 15); // Disable rising edge trigger
    BASE_EXTI->EXTI_FTSR |= (1 << 15);  // Enable falling edge trigger
}

void EXTI1_IRQHandler(void) {
    if (BASE_EXTI->EXTI_PR & (1 << 1)) {
        GPIO_PORTC->GPIO_ODR ^= (1 << 14); // Toggle LED on PC13
        BASE_EXTI->EXTI_PR |= (1 << 1);    // Clear pending bit
    }
}

void EXTI2_IRQHandler(void) {
    if (BASE_EXTI->EXTI_PR & (1 << 2)) {
        GPIO_PORTC->GPIO_ODR ^= (1 << 13); // Toggle LED on PC14
        BASE_EXTI->EXTI_PR |= (1 << 2);    // Clear pending bit
    }
}

void EXTI15_10_IRQHandler(void) {
    if (BASE_EXTI->EXTI_PR & (1 << 15)) {
        GPIO_PORTB->GPIO_ODR ^= (1 << 8); // Toggle LED on PB8
        BASE_EXTI->EXTI_PR |= (1 << 15);  // Clear pending bit
    }
}

void NVIC_Config(void) {
    uint32_t priority = 1; // Set priority to 1

    // Set priority for EXTI1
    NVIC_IPR_BASE[1] &= ~(0xFF << 8); // Clear previous priority
    NVIC_IPR_BASE[1] |= (priority << 8); // Set new priority

    // Enable interrupt for EXTI1
    NVIC_ISER_BASE[0] |= (1 << 7); // EXTI1 is bit 7 in ISER0

    // Set priority for EXTI2
    NVIC_IPR_BASE[1] &= ~(0xFF << 16); // Clear previous priority
    NVIC_IPR_BASE[1] |= (priority << 16); // Set new priority

    // Enable interrupt for EXTI2
    NVIC_ISER_BASE[0] |= (1 << 8); // EXTI2 is bit 8 in ISER0

    // Set priority for EXTI15_10
    NVIC_IPR_BASE[3] &= ~(0xFF << 24); // Clear previous priority
    NVIC_IPR_BASE[3] |= (priority << 24); // Set new priority

    // Enable interrupt for EXTI15_10
    NVIC_ISER_BASE[1] |= (1 << 8); // EXTI15_10 is bit 8 in ISER1 (32 + 8 = 40)
}
