/**
  ******************************************************************************
  * @file    main.c
  * @author  Auto-generated by STM32CubeIDE
  * @version V1.0
  * @brief   Default main function.
  ******************************************************************************
*/

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include<stdio.h>
#include<stdint.h>

/* This function executes in THREAD MODE of the processor */
void generate_interrupt()
{
	uint32_t *pSTIR  = (uint32_t*)0xE000EF00;
	uint32_t *pISER0 = (uint32_t*)0xE000E100;

	//enable IRQ3 interrupt
	*pISER0 |= ( 1 << 3);

	//generate an interrupt from software for IRQ3
	*pSTIR = (3 & 0x1FF);

}

void change_access_level_unpriv(void)
{
	//read
	__asm volatile("MRS R0,CONTROL");
	//modify
	// We can use the ORR assembly instruction to do an OR
	__asm volatile("ORR R0,R0,#0x01");
	//write
	__asm volatile("MSR CONTROL,R0");
}



/* This function executes in THREAD MODE of the processor */
int main(void)
{
	void (*fun_ptr)(void);

	printf("In thread mode : before interrupt\n");

	fun_ptr = change_access_level_unpriv;

	//fun_ptr = (void *)0x80001d4;

	fun_ptr();

	printf("In thread mode : after interrupt\n");

	for(;;);
}

/* This function(ISR) executes in HANDLER MODE of the processor */
void RTC_WKUP_IRQHandler(void)
{
	printf("In handler mode : ISR\n");
}

void HardFault_Handler(void)
{
	printf("Hard fault detected\n");
	while(1);
}
