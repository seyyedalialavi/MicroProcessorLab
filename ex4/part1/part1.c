#include <mega16.h>
#include <alcd.h>
void main(void)
{
    lcd_init(16);
    lcd_clear();
    lcd_gotoxy(2,0);
    lcd_puts("Hello World!");
    while (1);
}
