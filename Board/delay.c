#include "delay.h"

__IO uint32_t msTime = 0;
__IO uint32_t usTicks = 0;
__IO uint32_t CycleCounter = 0;

void Delay_Init(void)
{
	usTicks = (CLOCK_GetFreq(kCLOCK_CoreSysClk) / 1000000U);
    /* Enable TRC */
    CoreDebug->DEMCR &= ~0x01000000;
    CoreDebug->DEMCR |=  0x01000000;

    /* Enable counter */
    DWT->CTRL &= ~0x00000001;
    DWT->CTRL |=  0x00000001;

    /* Reset counter */
    DWT->CYCCNT = 0;
	
	SysTick_Config(CLOCK_GetFreq(kCLOCK_CoreSysClk) / 1000U);
}

void SysTick_Handler(void)
{
	/* Increase system time */
    CycleCounter = *DWT_CYCCNT;
	msTime++;
}

void delay_us(__IO uint32_t us)
{
    uint32_t start = DWT->CYCCNT;

    /* Go to number of cycles for system */
    us *= (CLOCK_GetFreq(kCLOCK_CoreSysClk) / 1000000U);

    /* Delay till end */
    while ((DWT->CYCCNT - start) < us);
}

void delay_ms(__IO uint32_t ms)
{
	/* Delay for amount of milliseconds */
    /* Check if we are called from ISR */
    if (__get_IPSR() == 0)
    {
        /* Called from thread mode */
        uint32_t tickstart = millis();

        /* Count interrupts */
        while ((millis() - tickstart) < ms);
    }
    else
    {
        /* Called from interrupt mode */
        while (ms)
        {
            /* Check if timer reached zero after we last checked COUNTFLAG bit*/
            if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
            {
                ms--;
            }
        }
    }
}

void delay_sec(__IO uint32_t sec)
{
	delay_ms(1000*sec);
}

uint32_t micros(void)
{
    register uint32_t OldCycle, Cycle, TimeMs;

    do
    {
        TimeMs = __LDREXW(&msTime);
        Cycle = *DWT_CYCCNT;
        OldCycle = CycleCounter;
    }
    while ( __STREXW( TimeMs , &msTime) );

    return (TimeMs * 1000) + (Cycle - OldCycle) / usTicks;
}

uint32_t millis(void)
{
    return msTime;
}
