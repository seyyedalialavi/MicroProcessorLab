#include <mega16.h>
char stepper []={0x09 , 0x05 , 0x06 , 0x0a};
unsigned char i=1;
bit start = 0;
unsigned char x;
bit direction = 0;
bit speed=0;

interrupt [TIM0_OVF] void tim0_ovf_isr (){
    TCCR0 = 0x00;
    if(direction == 0){ 
        i++;
        if(i == 4) i =0;
        if(speed ==0)x +=15;
        else x-=15;
        if(x == 255)speed = 1;
        if(x==0){
            speed = 0;
            direction = ~direction;
        }
    }
    else {
        if(i == 0) i =4;
        else i--;
        if(speed ==0)x +=15;
        else x-=15;
        if(x == 255)speed = 1;
        if(x==0){
            speed = 0;
            direction = ~direction;
        }
    }
    PORTB = stepper[i]; 
    TCNT0 = x;
    TCCR0 = 0x05;
}
void main(void)
{
    DDRB = 0xff;
    PORTB = stepper[i];
    DDRC = 0x00;
    PORTC = 0xff;
    x  = 0;
    TIMSK = 0x01;
    #asm("sei")
    
    while (1)
    {
        if(PINC.2==0){
            while(PINC.2==0);
            start = ~start; 
        }
        if (start == 0){
            x = 0;
            TCCR0 = 0x00;
            TCNT0 = 0;
        }
        else {
            TCCR0 = 0x05;
            TCNT0 = x;
        }
                
    }
}
