void TurnX(void)
{
    GPIO_PORTF_DATA_R |=(1<<1);
    GPIO_PORTF_DATA_R &= ~(1<<2);
}
