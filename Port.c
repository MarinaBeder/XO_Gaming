
#include "TExaS.h"

void EnableInterrupts(void);  // Enable interrupts
void PortE_Init(void)
{
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= 0x00000010;     // 1) E clock
    delay = SYSCTL_RCGC2_R;           // delay
    GPIO_PORTE_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PE0
    GPIO_PORTE_CR_R = 0x1E;           // allow changes to PE4-0
    GPIO_PORTE_AMSEL_R = 0x00;        // 3) disable analog function
    GPIO_PORTE_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL
    GPIO_PORTE_DIR_R = 0x02;          // 5) PE1 inpuT
    GPIO_PORTE_AFSEL_R = 0x00;        // 6) no alternate function
    GPIO_PORTE_PUR_R = 0x00;          // enable pullup resistors on PE1,PE0
    GPIO_PORTE_DEN_R = 0xFF;
    GPIO_PORTE_IS_R &=~(1<<0);	// (d) PE0 is edge-sensitive
    GPIO_PORTE_IS_R &=~(1<<2);// (d) PE2 is edge-sensitive
    GPIO_PORTE_IS_R &=~(1<<4);//(d) PE4 is edge-sensitive
    GPIO_PORTE_IBE_R &= ~(1<<0);    //     PE0 is not both edges
    GPIO_PORTE_IBE_R &= ~(1<<2);    //     PE2 is not both edges
    GPIO_PORTE_IBE_R &= ~(1<<4);    //     PE4 is not both edges
    GPIO_PORTE_IEV_R &= ~(1<<0);    //     PE0 falling edge event
    GPIO_PORTE_IEV_R &= ~(1<<2);    //     PE2 falling edge event
    GPIO_PORTE_IEV_R &= ~(1<<4);    //     PE4 falling edge event
    GPIO_PORTE_ICR_R = (1<<0);      // (e) clear flag0
    GPIO_PORTE_ICR_R = (1<<2);      // (e) clear flag2
    GPIO_PORTE_ICR_R = (1<<4);      // (e) clear flag4
    GPIO_PORTE_IM_R |= (1<<0);      // (f) arm interrupt on PF0
    GPIO_PORTE_IM_R |= (1<<2);      // (f) arm interrupt on PF2
    GPIO_PORTE_IM_R |= (1<<4);      // (f) arm interrupt on PF4
    NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
    NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
    EnableInterrupts();           // (i) Clears the I bit
}
void TurnX(void)
{
    GPIO_PORTF_DATA_R |=(1<<1);
    GPIO_PORTF_DATA_R &= ~(1<<2);
}
