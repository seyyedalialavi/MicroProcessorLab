#include <mega16.h>
char stepper []={0x09 , 0x05 , 0x06 , 0x0a};
unsigned char i=1;
bit wait;

interrupt [TIM0_OVF] void tim0_ovf_isr (){
    TCCR0 = 0x00; 
    i++;
    if(i == 4) i =0;
    PORTB = stepper[i];
}
void main(void)
{
    DDRB = 0xff;
    PORTB = stepper[i];
    DDRC = 0x00;
    PORTC = 0xff;
    
    TIMSK = 0x01;
    #asm("sei")
    wait = 0;
    while (1)
    {
        if(PINC.2==0){
            TCNT0 = -15;
            TCCR0 = 0x05;
        }
    }
}
