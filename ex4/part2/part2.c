#include <mega32.h>
#include <stdio.h>
#include <alcd.h>
#include <delay.h>
 int s;
 int h;
 int m;
 int day , month;

 int year = 1400 ;
 char TimeBuffer[17];
 char DateBuffer[17];
interrupt [EXT_INT0] void ei0(){
    if(m<59) m++;
    else m=0;
    
}
interrupt [EXT_INT1] void ei1(){
    if(h<23) h++;
    else m=0;
    
}
interrupt [EXT_INT2] void ei2(){
    if(h<30) day++;
    else m=0;
    
}
interrupt[TIM2_OVF]void t2(){
s++;
if(s==60){
    s=0;
    m++;
    if(m==60){
        m=0;
        h++;
        if(h==24){
            h=0;
            day++;
            if(day==30){
                day=0;
                month++;
                if(month==30){
                month =0;
                year++;
                }
            }
        }
    }
}
        lcd_clear();
        sprintf(TimeBuffer,"%d:%d:%d", h,m,s);
        lcd_puts(TimeBuffer);
    
        sprintf(DateBuffer,"%d/%d/%d ", year,month,day);
        lcd_gotoxy(0,1);
        lcd_puts(DateBuffer);
}

void main(void)
{
    #asm ("sei");
    GICR |= 0b11100000;
    MCUCR|=0x0f;
    MCUCSR|=0b01000000;
    ASSR=0x08;
    TCCR2=0x05;
    TIMSK=0x40;
    TCNT2=0x00;
    
    
    s = 0;
    m = 18;
    h = 10;
    day = 1;
    month = 8;
    lcd_init(16);
    lcd_clear();
    DDRC.0=0;
    DDRC.1=0;
    PORTC.0=0;
    PORTC.1=0;
    while (1)
    {
        if(PINC.0==1){
            while (PINC.0==1);
            if(month < 30) month++;
            else month =0;
        }
        if(PINC.1==1){
            while (PINC.1==1);
            year++;
        }   
        
        

    }
}
