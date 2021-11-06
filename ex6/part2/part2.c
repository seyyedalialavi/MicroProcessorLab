#include <mega32.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>
#define ADC_VREF_TYPE ((1<<REFS1) | (1<<REFS0) | (1<<ADLAR))
char sens1BUFF[16];
char settingBUFF[16];
int adc0 = 0 ;
unsigned char HighTemp;
unsigned char LowTemp;
unsigned char read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
delay_us(10);
ADCSRA|=(1<<ADSC);
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCH;
}
interrupt [TIM1_OVF] void tim1_ovf_isr (){
    TCCR1B = 0x00;
    lcd_clear();
    sprintf(sens1BUFF,"Temp=%d  C",adc0);
}
interrupt [EXT_INT2] void ext_int2_isr(){
    if(PINB.0==0){
        LowTemp++;
        sprintf(settingBUFF,"Low Temp = %d",LowTemp);
        lcd_gotoxy(0,1);
        lcd_puts(settingBUFF);
        TCCR1B = 0x05;
        TCNT1 = -16000;
        
    }
    if(PINB.1==0){
        LowTemp--;
        sprintf(settingBUFF,"Low Temp = %d",LowTemp);
        lcd_gotoxy(0,1);
        lcd_puts(settingBUFF);
        TCCR1B = 0x05;
        TCNT1 = -16000;
    }
    if(PINB.3==0){
        HighTemp++;
        sprintf(settingBUFF,"High Temp = %d",HighTemp);
        lcd_gotoxy(0,1);
        lcd_puts(settingBUFF);
        TCCR1B = 0x05;
        TCNT1 = -16000;
    }
    if(PINB.4==0){
        HighTemp--;
        sprintf(settingBUFF,"High Temp = %d",HighTemp);
        lcd_gotoxy(0,1);
        lcd_puts(settingBUFF); 
        TCCR1B = 0x05;
        TCNT1 =-16000;
    }        
    
}



void main(void)
{
DDRB=0x00;
PORTB=0xff;
DDRC.0 = 1;
PORTC.1 = 0;
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);
lcd_init(16);
#asm("sei")
GICR = (1<<INT2);
MCUCSR=(0<<ISC2);
HighTemp = 35;
LowTemp = 30;
TCCR1A = 0x00;
TIMSK = 0x05;
while (1){
      
      
    adc0 = read_adc(0);
    sprintf(sens1BUFF,"Temp=%d  C",adc0);
    lcd_gotoxy(0,0);
    lcd_puts(sens1BUFF); 
    delay_ms(150);
    if (adc0>HighTemp)
        PORTC.0 = 1;
    if(adc0<LowTemp)
        PORTC.0 = 0;
    }
}
