#include <stm32f10x.h>



template<class...>
void configure() {
    // Configure clocks.
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_HPRE) | RCC_CFGR_HPRE_0 | RCC_CFGR_HPRE_1;
	RCC->APB2ENR |= RCC_APB2ENR_IOPDEN | RCC_APB2ENR_AFIOEN;
	AFIO->MAPR |= AFIO_MAPR_PD01_REMAP;
	GPIOD->CRL = (GPIOD->CRL & ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1)) | GPIO_CRL_MODE1_1;
	GPIOD->BSRR = GPIO_BSRR_BR1;
    
    // Configure UART.
    transmitter_t::configure();
    // Configure FLASH.
    flash_t::configure();
}