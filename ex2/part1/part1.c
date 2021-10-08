#include <mega16.h>
bit i;
interrupt [TIM0_OVF] void tim0_ovf_isr (){
    TCCR0 = 0x00;
    i = ~i;;
    if(i ==0){
        PORTA.0 = ~PORTA.0;
    }
    TCNT0 = -250;
    TCCR0 = 0x05;//clock devision 1024
}

void main(void)
{
    DDRA = 0xff;
    PORTA = 0x00;
    TCCR0 = 0x05;
    TIMSK = 0x01;
    #asm("sei")
    i = 0;
    while (1){
    }
}
