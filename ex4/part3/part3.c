#include <mega32.h>
#include <stdio.h>
#include <alcd.h>
 int s;
 int h;
 int m;
 int m1 , s1, h1;
 int m2 , s2, h2;
 bit AlarmEnable =0;
 char TimeBuffer[17];
 char AlarmBuffer[17];
interrupt [EXT_INT0] void ei0(){
    if(m1<59) m1++;
    else m1=0;
    lcd_gotoxy(0,1);
    sprintf(AlarmBuffer,"%d:%d:%d", h1,m1,s1);
    lcd_puts(AlarmBuffer);
    
}
interrupt [EXT_INT1] void ei1(){
    if(h1<23) h1++;
    else h1=0;
    lcd_gotoxy(0,1);
    sprintf(AlarmBuffer,"%d:%d:%d", h1,m1,s1);
    lcd_puts(AlarmBuffer);
    
}
interrupt [EXT_INT2] void ei2(){
    if(s1<60) s1++;
    else s1=0;
    lcd_gotoxy(0,1);
    sprintf(AlarmBuffer,"%d:%d:%d", h1,m1,s1);
    lcd_puts(AlarmBuffer);
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
            
            }
        }
    }
    lcd_gotoxy(0,0);        
    sprintf(TimeBuffer,"%d:%d:%d", h,m,s);
    lcd_puts(TimeBuffer);
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
    m = 50;
    h = 10;
    lcd_init(16);
    lcd_clear();
    DDRC.0=0;
    DDRC.1=0;
    PORTC.0=0;
    PORTC.1=0;
    DDRD.0=1;
    PORTD.0=0;
    s1=0;
    m1=0;
    h1=0;
    while (1)
    {
        if(PINC.0==1){
            while (PINC.0==1);
            AlarmEnable = 1;
            lcd_gotoxy(0,1);
            lcd_puts("AlarmEnabled");
            s2 = s;
            m2 = m;
            h2 = h;
            s2 = s1 + s2;
            if(s2>59){
                s2 -= 60;
                m2++;
            }
            m2 = m2+m1;
            if(m2>59){
                m2 -= 60;
                h2++;
            } 
            h2 = h2+h1;
            if(h2>23){
                h2 -= 24;
            }
            
        }
        if(h==h2 && m==m2 && s==s2 && AlarmEnable ==1){
            AlarmEnable = 0; 
            PORTD.0 = 1; 
            lcd_clear();
            sprintf(TimeBuffer,"%d:%d:%d", h,m,s);
            lcd_puts(TimeBuffer);
            lcd_gotoxy(0,1);
            lcd_puts("The timer is up");
        }
    }
}
