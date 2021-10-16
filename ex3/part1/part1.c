#include <mega16.h>
char display[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//common cathode
int counter;

interrupt [TIM1_OVF] void tim1_ovf_isr (){
    TCCR1B = 0x00;
    counter++;
    if(counter == 10) counter = 0;
    PORTD = display[counter];
    TCNT1 = -1000;
    TCCR1B = 0x05;//clock devision 1024
}
void main(void)
{
    DDRD = 0xff;
    PORTD = 0x00;
    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCNT1 = -1000;
    TIMSK = 0x05;
    #asm("sei")
    counter = 0;
    PORTD = display[counter];
    while (1);
}

