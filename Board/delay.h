#ifndef _DELAY_H_
#define _DELAY_H_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "main.h"
	
#define DWT_CYCCNT  ((volatile uint32_t *)0xE0001004)
         
void Delay_Init(void);
void delay_us(__IO uint32_t us);
void delay_ms(__IO uint32_t ms);
void delay_sec(__IO uint32_t sec);
uint32_t micros(void);
uint32_t millis(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _DELAY_H_ */
