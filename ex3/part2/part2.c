#include <mega16.h>
char seg[4] = {0xfe , 0xfd , 0xfb , 0xf7};
char display[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//common cathode
char segmux[];
char i;
int counter;

interrupt [TIM0_OVF] void tim0_ovf_isr (){
    TCCR0 = 0x00;
    i++;
    if(i==4)i = 0;
    PORTC = seg[i];
    PORTD = segmux[i];
    TCNT0 = -50;
    TCCR0 = 0x04;//clock devision 256
}
interrupt [TIM1_OVF] void tim1_ovf_isr (){
    TCCR1B = 0x00;
    counter++;
    if(counter == 10000) counter = 0;
    segmux[3] = display[counter%10];
    segmux[2] = display[counter/10%10];
    segmux[1] = display[counter/100%10];
    segmux[0] = display[counter/1000];
    TCNT1 = -1000;
    TCCR1B = 0x05;//clock devision 1024
}
void main(void)
{
    DDRC = 0xff;
    DDRD = 0xff;
    PORTD = 0x00;
    PORTC = 0xff;
    TCCR0 = 0x04;
    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCNT1 = -1000;
    TIMSK = 0x05;
    TCNT0 = -50;
    #asm("sei")
    i = 0;
    counter = 0;
    segmux[3] = display[counter%10];
    segmux[2] = display[counter/10%10];
    segmux[1] = display[counter/100%10];
    segmux[0] = display[counter/1000];
    PORTC = seg[i];
    PORTD = segmux[i];
    while (1);
}

