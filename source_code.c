#include <lpc214x.h>
#include <stdio.h>
#include <stdlib.h>

// -------- LCD PINS --------
#define RS (1UL<<16)
#define RW (1UL<<17)
#define EN (1UL<<18)
#define D4 (1UL<<19)
#define D5 (1UL<<20)
#define D6 (1UL<<21)
#define D7 (1UL<<22)

// -------- LED PORT --------
#define LED_ALL 0x00FF0000   // P1.16–P1.23

// -------- KEYPAD --------
#define r1 (1UL<<24)
#define r2 (1UL<<25)
#define r3 (1UL<<26)
#define r4 (1UL<<27)
#define c1 (1UL<<28)
#define c2 (1UL<<29)
#define c3 (1UL<<30)
#define c4 (1UL<<31)

void delay(unsigned int n) {
    unsigned int i,j;
    for(i=0;i<n;i++) for(j=0;j<6000;j++);
}

// -------- LCD --------
void LCD4_Convert(unsigned char c) {
    IOCLR0 = D4|D5|D6|D7;
    IOSET0 = ((c>>4)&0x0F)<<19;
    IOSET0 = EN; delay(2); IOCLR0 = EN;

    IOCLR0 = D4|D5|D6|D7;
    IOSET0 = (c&0x0F)<<19;
    IOSET0 = EN; delay(2); IOCLR0 = EN;
}

void lcd_cmd(unsigned char data) {
    IOCLR0 = RS|RW;
    LCD4_Convert(data);
}

void lcd_data(unsigned char data) {
    IOSET0 = RS;
    IOCLR0 = RW;
    LCD4_Convert(data);
}

void lcd_initialize(void) {
    IODIR0 |= RS|RW|EN|D4|D5|D6|D7;
    delay(20);
    lcd_cmd(0x02);
    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}

void lcd_string(char *str) {
    while(*str) lcd_data(*str++);
}

// -------- KEYPAD --------
unsigned char keypad(void) {

    IOCLR1 = c1; IOSET1 = (c2|c3|c4);
    if(!(IOPIN1 & r1)) return '1';
    if(!(IOPIN1 & r2)) return '4';
    if(!(IOPIN1 & r3)) return '7';

    IOCLR1 = c2; IOSET1 = (c1|c3|c4);
    if(!(IOPIN1 & r1)) return '2';
    if(!(IOPIN1 & r2)) return '5';
    if(!(IOPIN1 & r3)) return '8';
    if(!(IOPIN1 & r4)) return '0';

    IOCLR1 = c3; IOSET1 = (c1|c2|c4);
    if(!(IOPIN1 & r1)) return '3';
    if(!(IOPIN1 & r2)) return '6';
    if(!(IOPIN1 & r3)) return '9';

    return 0;
}

// -------- ADC --------
void ADC_Init() {
    PINSEL1 |= (1UL<<24);   // P0.28 -> AD0.1
    AD0CR = (1<<1) | (4<<8) | (1<<21);
}

unsigned int ADC_Read() {
    AD0CR |= (1<<24);
    while(!(AD0DR1 & (1<<31)));
    return (AD0DR1 >> 6) & 0x3FF;
}

// -------- MAIN --------
int main() {

    char input[3] = {0};
    int temp_val = 0, bpm = 0, key_count = 0;
    unsigned int adc_val;
    char buffer[20];
    unsigned char key;

    lcd_initialize();
    ADC_Init();

    // -------- LED CONFIG --------
    PINSEL2 = 0x00000000;
    IODIR1 |= LED_ALL;
    IOSET1 = LED_ALL;   // OFF (active LOW)

    IODIR1 |= (0xFUL<<28); // keypad

    while(1) {

        // -------- BPM --------
        adc_val = ADC_Read();
        bpm = (adc_val * 120) / 1023;

        lcd_cmd(0x80);

        if(bpm < 60)
            sprintf(buffer,"BPM:%d LOW   ",bpm);
        else if(bpm <= 100)
            sprintf(buffer,"BPM:%d NORMAL",bpm);
        else
            sprintf(buffer,"BPM:%d HIGH  ",bpm);

        lcd_string(buffer);

        // -------- LED ALERT (REAL-TIME) --------
        if(bpm > 100 || temp_val > 37) {

            IOCLR1 = LED_ALL;   // ON
            delay(500);

            IOSET1 = LED_ALL;   // OFF
            delay(500);
        }
        else {
            IOSET1 = LED_ALL;   // OFF
        }

        // -------- TEMP INPUT --------
        lcd_cmd(0xC0);

        if(key_count == 0)
            lcd_string("Temp: __");

        key = keypad();

        if(key >= '0' && key <= '9') {

            input[key_count] = key;
            lcd_cmd(0xC0 + 6 + key_count);
            lcd_data(key);

            key_count++;
            delay(300);

            if(key_count == 2) {

                input[2] = '\0';
                temp_val = atoi(input);

                lcd_cmd(0xC0);

                if(temp_val < 36)
                    sprintf(buffer,"T:%s LOW   ",input);
                else if(temp_val <= 37)
                    sprintf(buffer,"T:%s NORMAL",input);
                else
                    sprintf(buffer,"T:%s HIGH  ",input);

                lcd_string(buffer);

                delay(2000);
                key_count = 0;
            }
        }

        delay(100);
    }
}