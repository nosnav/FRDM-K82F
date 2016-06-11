#include "main.h"

int main(void)
{
    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockHSRUN();
    BOARD_InitDebugConsole();
	Delay_Init();
	
    /* Print a note to terminal. */
    PRINTF("\r\n GPIO Driver example\r\n");
    PRINTF("\r\n The LED is taking turns to shine.\r\n");

    /* Init output LED GPIO. */
    //LED_RED_INIT(1U);
	LED_BLUE_INIT(1U);
	LED_GREEN_INIT(0U);
	
    while (1)
    {
        delay_ms(1000U);
		//LED_RED_TOGGLE();
		LED_BLUE_TOGGLE();
		LED_GREEN_TOGGLE();
    }
}
