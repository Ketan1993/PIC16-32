#include "delay.h"

void delay_ms(int delay_count) {
    int i = 0;
    for (i = 0; i < delay_count; i++) {
        __delay_ms(1);
    }
}

void delay_us(int delay_count) {
    int i = 0;
    for (i = 0; i < delay_count; i++) {
        __delay_us(1);
    }
}
void delay_sec(int delay_count) {
    int i = 0;
    for (i = 0; i < delay_count; i++) {
        delay_ms(1000);
    }
}
