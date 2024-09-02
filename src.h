#include <stdio.h>
#include <stdint.h>

 typedef struct 
	 {
		volatile uint32_t CR;
		volatile uint32_t CFGR;
		volatile uint32_t CIR;
		volatile uint32_t APB2RSTR;
		volatile uint32_t APB1RSTR;
		volatile uint32_t AHBENR;
		volatile uint32_t APB2ENR;
		volatile uint32_t APB1ENR;
		volatile uint32_t BDCR;
		volatile uint32_t CSR;
		volatile uint32_t AHBRSTR;
		volatile uint32_t CFGR2;
	 }RCC_TYPE;
	 
	typedef struct 
	{
		volatile	uint32_t GPIO_CRL;
		volatile	uint32_t GPIO_CRH;
		volatile	uint32_t GPIO_IDR;
		volatile	uint32_t GPIO_ODR;
		volatile	uint32_t GPIO_BSRR;
		volatile	uint32_t GPIO_BRR;
		volatile	uint32_t GPIO_LCKR;
	}GPIO_TYPE;
	
	typedef struct
	{
		volatile uint32_t EXTI_IMR;
		volatile uint32_t EXTI_EMR;
		volatile uint32_t EXTI_RTSR;
		volatile uint32_t EXTI_FTSR;
		volatile uint32_t EXTI_SWIER;
		volatile uint32_t EXTI_PR;
	}EXTI_TYPE;
	
	typedef struct {
		volatile uint32_t AFIO_EVCR;
		volatile uint32_t AFIO_MAPR;
		volatile uint32_t AFIO_EXTICR1;
		volatile uint32_t AFIO_EXTICR2;
		volatile uint32_t AFIO_EXTICR3;
		volatile uint32_t AFIO_EXTICR4;
		volatile uint32_t AFIO_MAPR2;
	}AFIO_TYPE;
	
//clock	
#define BASE_RCC ((RCC_TYPE*)0x40021000)
	
	//PORT_DEFINE
#define GPIO_PORTA ((GPIO_TYPE*)0x40010800)
#define GPIO_PORTB ((GPIO_TYPE*)0x40010C00)
#define GPIO_PORTC ((GPIO_TYPE*)0x40011000)
#define GPIO_PORTD ((GPIO_TYPE*)0x40011400)
#define GPIO_PORTE ((GPIO_TYPE*)0x40011800)
#define GPIO_PORTF ((GPIO_TYPE*)0x40011C00)
#define GPIO_PORTG ((GPIO_TYPE*)0x40012000)
	// Interrupt exti
#define BASE_EXTI  ((EXTI_TYPE*)0x40010400)
	// AFIO
#define AFIO_BASE ((AFIO_TYPE*)0x40010000)
	// NVIC ADDRESS
	//EXTI0 PLACE AT 6TH BIT IN ISER REGISTER
	//EXTI1 PLACE AT 7TH BIT IN ISER REGISTER
	//EXTI2 PLACE AT 8TH BIT IN ISER REGISTER
	//EXTI3 PLACE AT 9TH BIT IN ISER REGISTER
	//EXTI4 PLACE AT 10TH BIT IN ISER REGISTER
	//...
#define NVIC_ISER_BASE    ((volatile uint32_t *)0xE000E100) //set enable Register
#define NVIC_ICER_BASE		((volatile uint32_t *)0xE000E180) // clear enable Register
#define NVIC_IPR_BASE     ((volatile uint32_t *)0xE000E400) // Interrupt Priority Register
#define NVIC_ISPR_BASE  	((volatile uint32_t *)0xE000E200)  //Interrupt Set-Pending Registers
#define NVIC_IABR_BASE	((volatile uint32_t *)0xE000E300) //Interrupt Active Bit Register
#define NVIC_ICPR_BASE		((volatile uint32_t *)0xE000E280) //Interrupt Clear-Pending Registers

