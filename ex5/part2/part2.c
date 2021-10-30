#include <mega16.h>
char stepper []={0x09 , 0x05 , 0x06 , 0x0a};
unsigned char i=1;
bit direction = 0;

interrupt [TIM0_OVF] void tim0_ovf_isr (){
    TCCR0 = 0x00;
    if(direction == 0){ 
        i++;
        if(i == 4) i =0;
    }
    else {
        if(i == 0) i =4;
        else i--;
    }
    PORTB = stepper[i]; 
    TCNT0 = 0;
    TCCR0 = 0x05;
}
void main(void)
{
    DDRB = 0xff;
    PORTB = stepper[i];
    DDRC = 0x00;
    PORTC = 0xff;
    
    TIMSK = 0x01;
    #asm("sei")
    TCNT0 = 0;
    TCCR0 = 0x05;
    while (1)
    {
        if(PINC.2==0){
            while(PINC.2==0);
            direction = ~direction; 
        }
                
    }
}
