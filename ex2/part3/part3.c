#include <mega16.h>
bit i;
bit mode ;
interrupt [TIM0_OVF] void tim0_ovf_isr (){
    TCCR0 = 0x00;
    i = ~i;
    if(i ==0){
        if(mode)
            PORTB = PORTB>>1;
        else{
            PORTB = PORTB<<1;
                if(PORTB == 0x80)
                mode = 1;
        }
    }
    TCNT0 = -250;
    TCCR0 = 0x05;//clock devision 1024
}

void main(void)
{
    DDRB = 0xff;
    PORTB = 0x00;
    DDRA = 0x00;
    PORTA = 0xff;
    TIMSK = 0x01;
    #asm("sei")
    i = 0;
    mode = 0;
    while (1){
        if(PINA.0 == 0){
            while(PINA.0 == 0);
            TCNT0 = -250;
            TCCR0 = 0x05;
            PORTB = 0x01;
            mode = 0;
            i = 0;
        }
    }
}
